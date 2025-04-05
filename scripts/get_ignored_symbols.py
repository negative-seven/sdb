#!/usr/bin/env python3

import argparse
import elftools.elf.elffile


def main():
    parser = argparse.ArgumentParser(prog="get_ignored_symbols")
    parser.add_argument("object_files", nargs="*")
    arguments = parser.parse_args()

    for object_file_name in arguments.object_files:
        with elftools.elf.elffile.ELFFile(open(object_file_name, "rb")) as object_file:
            ignored_section_indices = {
                index
                for index, section in enumerate(object_file.iter_sections())
                if section.name.endswith(".ignore_in_diff")
            }
            for symbol in object_file.get_section_by_name(".symtab").iter_symbols():
                if symbol.name and symbol.entry["st_shndx"] in ignored_section_indices:
                    print(symbol.name)


if __name__ == "__main__":
    main()
