from __future__ import annotations

import argparse
import json
from pathlib import Path

from .extract import write_inventory
from .generation_data import write_generation
from .teams import reconstruct


def main() -> None:
    parser = argparse.ArgumentParser(description="Emerald source and emulated-battle research tools; tournament readiness gated")
    parser.add_argument("--project", type=Path, default=Path.cwd())
    parser.add_argument("--upstream", type=Path, default=Path("pokeemerald"))
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("extract")
    commands.add_parser("doctor")
    trainers = commands.add_parser("trainers").add_subparsers(dest="action", required=True)
    trainers.add_parser("list")
    show = trainers.add_parser("show")
    show.add_argument("id")
    show.add_argument("--reconstruct", action="store_true")
    args = parser.parse_args()
    if args.command == "doctor":
        from .doctor import diagnose
        report = diagnose(args.project.resolve())
        print(json.dumps(report, indent=2))
        raise SystemExit(0 if report["build_prerequisites_ready"] else 1)
    if args.command == "extract":
        result = write_inventory(args.upstream, args.project)
        write_generation(args.upstream, args.project)
        print(f"Extracted {len(result['trainers'])} entries at {result['pokeemerald_commit']}")
        return
    data = json.loads((args.project / "data/generated/trainers.json").read_text())
    if args.action == "list":
        for trainer in data["trainers"]:
            print(trainer["id"], trainer["constant"], trainer["category"])
    else:
        found = next((t for t in data["trainers"] if args.id in (str(t["id"]), t["constant"])), None)
        if found is None:
            parser.error(f"Unknown trainer: {args.id}")
        if args.reconstruct:
            generation = json.loads((args.project / "data/generated/generation.json").read_text())
            if generation["pokeemerald_commit"] != data["pokeemerald_commit"]:
                parser.error("Trainer and generation source commits differ; rerun extract")
            found = reconstruct(found, generation)
        print(json.dumps(found, indent=2))


if __name__ == "__main__":
    main()
