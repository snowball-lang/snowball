#!/usr/env python3
# usage: python3 utils/mangle.py NAME "ARG1,ARG2,ARG3,..."

import sys

def mangle(name: str, args: list):
    result = "_M"
    for part in name.split("."):
        result += f"N{len(part)}{part}"

    for arg in args:
        if arg.strip() == '':
            continue

        result += f"A{len(arg)}{arg}"

    return result

def main(argv):
    if len(argv) < 2:
        raise Exception("Invalid number of arguments passed to mangler")

    name = argv[1]
    _args = ""
    if len(argv) > 2:
        _args = argv[2]

    args = _args.split(",")
    print("Mangled name: " + mangle(name, args))


if __name__ == "__main__":
    main(sys.argv)
