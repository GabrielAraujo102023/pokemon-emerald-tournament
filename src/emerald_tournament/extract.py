"""Compile upstream C initializers; lexical scans supply provenance, not values."""
from __future__ import annotations

import hashlib
import json
import re
import subprocess
import tempfile
from collections import Counter
from pathlib import Path

SCHEMA_VERSION = 2


def command(*args: str) -> str:
    return subprocess.check_output(args, text=True)


def constants(root: Path, filename: str, prefix: str) -> dict[int, str]:
    # Discover declared identifiers lexically, but let C evaluate enums/expressions.
    source = (root / "include/constants" / filename).read_text()
    source = re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S)
    if filename == "items.h":
        # Item-use modes and range aliases share values with item IDs.
        # Only the first enum defines the canonical item namespace.
        start = source.index("enum {") + len("enum {")
        source = source[start:source.index("};", start)]
    names = sorted(set(re.findall(
        rf"^\s*(?:#define\s+)?({prefix}\w+)(?=\s|,|=|$)", source, re.M)))
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        code = '#include <stdio.h>\n#include "constants/' + filename + '"\nint main(void) {\n'
        code += "".join(f'printf("%u\\t{name}\\n", (unsigned){name});\n' for name in names)
        code += '}\n'
        (work / "names.c").write_text(code)
        command("cc", "-I", str(root / "include"), str(work / "names.c"), "-o", str(work / "names"))
        return {int(value): name for value, name in (line.split("\t") for line in command(str(work / "names")).splitlines())}



def extract(root: Path, project: Path) -> dict:
    root = root.resolve()
    declarations = (root / "include/data.h").read_text()
    limits = re.search(r"^#define MAX_TRAINER_ITEMS .+$", declarations, re.M).group(0)
    declarations = limits + "\n" + declarations[declarations.index("struct TrainerMonNoItemDefaultMoves"):declarations.index("#define TRAINER_ENCOUNTER_MUSIC(")]
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        (work / "trainer_declarations.h").write_text(declarations)
        command("cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-I", str(work),
                "-I", str(root / "include"), "-I", str(root),
                str(project / "tools/dump_trainers.c"), "-o", str(work / "dump"))
        output = command(str(work / "dump"))
    names = constants(root, "opponents.h", "TRAINER_")
    species = constants(root, "species.h", "SPECIES_")
    moves = constants(root, "moves.h", "MOVE_")
    items = constants(root, "items.h", "ITEM_")
    classes = constants(root, "trainers.h", "TRAINER_CLASS_")
    refs: dict[str, list[str]] = {}
    for path in sorted((root / "data").rglob("*.inc")):
        for line, text in enumerate(path.read_text().splitlines(), 1):
            for name in set(re.findall(r"\bTRAINER_[A-Z0-9_]+\b", text.split("@")[0])):
                refs.setdefault(name, []).append(f"{path.relative_to(root)}:{line}")
    groups = {}
    for match in re.finditer(r"\[(REMATCH_\w+)\]\s*=\s*REMATCH\(([^)]+)\)", (root / "src/battle_setup.c").read_text()):
        for index, name in enumerate(match[2].split(",")[:5]):
            groups.setdefault(name.strip(), {"group": match[1], "stage": index})
    locations = {}
    for line, text in enumerate((root / "src/data/trainers.h").read_text().splitlines(), 1):
        match = re.search(r"\[(TRAINER_\w+)\]", text)
        if match:
            locations[match[1]] = f"src/data/trainers.h:{line}"
    party_locations = {}
    for number, line in enumerate((root / "src/data/trainer_parties.h").read_text().splitlines(), 1):
        match = re.search(r"(sParty_\w+)\[\]", line)
        if match:
            party_locations[match[1]] = f"src/data/trainer_parties.h:{number}"
    party_refs = {}
    current = None
    for line in (root / "src/data/trainers.h").read_text().splitlines():
        match = re.search(r"\[(TRAINER_\w+)\]", line)
        if match:
            current = match[1]
        match = re.search(r"\((sParty_\w+)\)", line)
        if match:
            party_refs[current] = match[1]
    trainers = []
    for line in output.splitlines():
        fields = line.split("\t")
        if fields[0] == "T":
            _, ident, name, cls, gender, double, ai, flags, size, *inventory = fields
            constant = names[int(ident)]
            group = groups.get(constant)
            references = refs.get(constant, [])
            category = "standard_double" if int(double) else "standard_single"
            reason = "Nonempty gTrainers entry with script references; reachability not proven."
            if not int(size):
                category, reason = "unused", "Empty placeholder party."
            elif group and group["stage"] > 0:
                category, reason = "rematch", "Explicit later position in gRematchTable."
            elif constant.startswith(("TRAINER_BRENDAN_", "TRAINER_MAY_")):
                category, reason = "alternate_story_version", "Rival starter/story variant; identity unmerged."
            elif not references and not group:
                category, reason = "unknown", "No scanned script reference or rematch membership; not proof of being unused."
            trainer = dict(id=int(ident), constant=constant, name=name, trainer_class=classes.get(int(cls), int(cls)),
                           encounter_music_gender=int(gender), double_battle=bool(int(double)), ai_flags=int(ai),
                           party_format=int(flags), party_size=int(size), battle_items=[items.get(int(x), int(x)) for x in inventory],
                           party=[], party_symbol=party_refs.get(constant), party_source=party_locations.get(party_refs.get(constant)), source=locations[constant], script_references=references, encounter_group=group,
                           character_identity=None, normally_battleable=None, category=category, classification_reason=reason,
                           supported=False, special_behavior="Script semantics and side adaptation not yet validated")
            trainers.append(trainer)
        else:
            _, slot, iv, level, mon, held, *explicit = fields
            trainer["party"].append(dict(slot=int(slot), iv_parameter=int(iv), fixed_iv=int(iv)*31//255,
                level=int(level), species=species[int(mon)], held_item=items.get(int(held), int(held)),
                moves=[moves[int(x)] for x in explicit] if explicit else None,
                move_generation="explicit" if explicit else "level_up", evs=[0]*6))
    relevant = [root / "include/data.h", root / "src/data/trainers.h", root / "src/data/trainer_parties.h", root / "src/battle_setup.c"]
    relevant += sorted((root / "include/constants").glob("*.h"))
    relevant += sorted((root / "data").rglob("*.inc"))
    return dict(schema_version=SCHEMA_VERSION, pokeemerald_commit=command("git", "-C", str(root), "rev-parse", "HEAD").strip(),
                upstream_dirty=bool(command("git", "-C", str(root), "status", "--porcelain")),
                source_hashes={str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest() for p in relevant},
                classification="provisional structural inventory, not an eligibility guarantee", trainers=trainers)


def write_inventory(root: Path, project: Path) -> dict:
    result = extract(root, project)
    target = project / "data/generated/trainers.json"
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n")
    counts = Counter(t["category"] for t in result["trainers"])
    doubles = sum(t["double_battle"] for t in result["trainers"])
    report = ["# Trainer inventory", "", f"Upstream: `{result['pokeemerald_commit']}`.", "",
              f"{len(result['trainers'])} entries including the empty sentinel; {doubles} double-flagged entries across categories.", "",
              "Classification is provisional. Script references establish textual use, not reachability; rematch stages come from the source table. No numeric suffix heuristic is used. All entries are retained. No entry is certified simulation-supported yet.", ""]
    report += [f"- {key}: {value}" for key, value in sorted(counts.items())]
    report += ["", "The JSON stores numeric evaluated AI flags, party format (0 default, 1 custom moves, 2 item/default, 3 item/custom), all inventory slots, source locations and script references. Null moves means default generation remains to be resolved, not an empty moveset. Character identities remain null rather than inferring identity from shared names.", "", "Battle Frontier populations are separate and are not counted here. Paired encounters, unused entries and special scripts require further semantic auditing before eligibility is finalized.", "", "## Entries", ""]
    report += [f"- `{t['constant']}` ({t['id']}), {t['name']}: {t['category']}; levels {','.join(str(p['level']) for p in t['party']) or 'none'}; {t['source']}" for t in result["trainers"]]
    (project / "docs/trainer_inventory.md").write_text("\n".join(report) + "\n")
    return result
