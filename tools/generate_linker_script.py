#!/usr/bin/env python3

import elftools.elf.elffile
import re
import argparse
import string


def main():
    parser = argparse.ArgumentParser(prog="generate_linker_script")
    parser.add_argument("-i", "--input")
    parser.add_argument("-o", "--output")
    parser.add_argument("-b", "--object-files", nargs="*")
    arguments = parser.parse_args()

    mapping_sections = set()
    for object_file_name in arguments.object_files:
        with elftools.elf.elffile.ELFFile(open(object_file_name, "rb")) as object_file:
            for section in object_file.iter_sections():
                if match := re.fullmatch(
                    r"(.text|.rodata).(0x[0-9a-f]+)(?:.ignore_in_diff)?", section.name
                ):
                    base_section_name = match.group(1)
                    address = match.group(2)
                    mapping_sections.add(
                        f"    {base_section_name}.{address} {address} : "
                        f"{{ *({base_section_name}.{address}*) }}"
                    )

    mapping = {"sections": "\n".join(mapping_sections)}

    with open(arguments.input, encoding="utf-8") as input_file:
        template = string.Template(input_file.read())
    with open(arguments.output, "w", encoding="utf-8") as output_file:
        output_file.write(template.substitute(mapping))


if __name__ == "__main__":
    main()
