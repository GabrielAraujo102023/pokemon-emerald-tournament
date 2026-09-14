"""Extract generation inputs with the upstream text preprocessor and host C compiler."""
from __future__ import annotations

import hashlib
import json
import tempfile
from pathlib import Path

from .extract import command, constants


def declaration(source: str, start: str, end: str) -> str:
    return source[source.index(start):source.index(end)]


def extract_generation(root: Path, project: Path) -> dict:
    root, project = root.resolve(), project.resolve()
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        preproc = work / "preproc"
        command("c++", "-std=c++11", "-O2", "-Wall", "-Wno-switch", "-Werror", *map(str, sorted((root / "tools/preproc").glob("*.cpp"))), "-o", str(preproc))
        for src, target in [("src/data/trainers.h", "encoded_trainers.h"), ("src/data/text/species_names.h", "encoded_species.h")]:
            # Upstream preproc dispatches based on .c extension.
            input_file = work / "input.c"
            input_file.write_text((root / src).read_text())
            (work / target).write_text(command(str(preproc), str(input_file), str(root / "charmap.txt")))
        data = (root / "include/data.h").read_text()
        pokemon = (root / "include/pokemon.h").read_text()
        declarations = declaration(data, "#define MAX_TRAINER_ITEMS", "struct TrainerMonNoItemDefaultMoves")
        # Only retain the limit, not unrelated graphics declarations.
        declarations = declarations.splitlines()[0] + "\n"
        declarations += declaration(data, "struct TrainerMonNoItemDefaultMoves", "#define TRAINER_ENCOUNTER_MUSIC(")
        enum_start = pokemon.index("enum {")
        declarations += pokemon[enum_start:pokemon.index("};", enum_start)+2] + "\n"
        declarations += declaration(pokemon, "struct SpeciesInfo\n", "#define SPINDA_SPOT_WIDTH")
        declarations += "\n".join(line for line in (root / "include/battle.h").read_text().splitlines() if line.startswith("#define MOVE_TARGET_")) + "\n"
        (work / "declarations.h").write_text(declarations)
        source = (root / "src/pokemon.c").read_text()
        nature = source[source.index("const s8 gNatureStatTable"):]
        (work / "nature.h").write_text(nature[:nature.index("};")+2])
        battle_main = (root / "src/battle_main.c").read_text()
        start = battle_main.index("static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum, bool8 firstTrainer)\n{")
        end = battle_main.index("\nstatic void UNUSED HBlankCB_Battle", start)
        (work / "constructor.h").write_text(battle_main[start:end])
        command("cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-I", str(work), "-I", str(root), "-I", str(root / "include"), str(project / "tools/dump_generation.c"), "-o", str(work / "dump"))
        output = command(str(work / "dump"))
    species_names = constants(root, "species.h", "SPECIES_")
    move_names = constants(root, "moves.h", "MOVE_")
    result = dict(schema_version=1, pokeemerald_commit=command("git", "-C", str(root), "rev-parse", "HEAD").strip(), constructor_calls={}, trainer_name_bytes={}, species={}, moves={}, nature_modifiers={}, experience={})
    for line in output.splitlines():
        kind, ident, *fields = line.split("\t")
        values = list(map(int, fields))
        if kind == "C":
            result["constructor_calls"].setdefault(ident, []).append(dict(species_id=values[0], level=values[1], iv=values[2], personality=values[3]))
        elif kind == "T":
            result["trainer_name_bytes"][ident] = values
        elif kind == "S":
            result["species"][ident] = dict(constant=species_names[int(ident)], base_stats=values[:6], gender_ratio=values[6], friendship=values[7], growth_rate=values[8], abilities=values[9:11], types=values[11:13])
        elif kind == "N":
            result["species"][ident]["name_bytes"] = values
        elif kind == "L":
            result["species"][ident]["learnset"] = [[x >> 9, x & 511] for x in values]
        elif kind == "M":
            result["moves"][ident] = dict(constant=move_names[int(ident)], **dict(zip(["pp", "power", "type", "accuracy", "effect", "secondary_chance", "target", "priority", "flags"], values)))
        elif kind == "A":
            result["nature_modifiers"][ident] = values
        elif kind == "E":
            result["experience"][ident] = values
    paths = [root / "charmap.txt", root / "src/pokemon.c", root / "src/battle_main.c", root / "include/pokemon.h", root / "include/battle.h", root / "include/data.h", root / "src/data/trainers.h", root / "src/data/trainer_parties.h", root / "src/data/text/species_names.h", root / "src/data/battle_moves.h"]
    paths += sorted((root / "src/data/pokemon").glob("*.h")) + sorted((root / "include/constants").glob("*.h")) + sorted((root / "tools/preproc").glob("*"))
    result["source_hashes"] = {str(p.relative_to(root)): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths if p.is_file()}
    result["extractor_sha256"] = hashlib.sha256((project / "tools/dump_generation.c").read_bytes() + Path(__file__).read_bytes()).hexdigest()
    return result


def write_generation(root: Path, project: Path) -> dict:
    result = extract_generation(root, project)
    (project / "data/generated/generation.json").write_text(json.dumps(result, indent=2) + "\n")
    return result
