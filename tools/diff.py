#!/usr/bin/env python3

import argparse
import elftools.elf.elffile
import iced_x86
import itertools
import re
import subprocess
import sys


class Elf:
    def __init__(self, stream):
        self.bytes = stream.read()

        elftools_elf = elftools.elf.elffile.ELFFile(stream)

        self.sections = [ElfSection(s) for s in elftools_elf.iter_sections()]

        self.symbols = []
        for elftools_symbol in elftools_elf.get_section_by_name(
            ".symtab"
        ).iter_symbols():
            self.symbols.append(ElfSymbol(self, elftools_symbol))

        elftools_elf.close()


class ElfSection:
    def __init__(self, elftools_section):
        self.address = elftools_section.header["sh_addr"]
        self.offset = elftools_section.header["sh_offset"]


class ElfSymbol:
    def __init__(self, elf: Elf, elftools_symbol):
        self.name = elftools_symbol.name
        self.address = elftools_symbol.entry["st_value"]
        self.size = elftools_symbol.entry["st_size"]

        section_index = elftools_symbol.entry["st_shndx"]
        if section_index == "SHN_UNDEF":
            self.section = None
            self.absolute = False
        elif section_index == "SHN_ABS":
            self.section = None
            self.absolute = True
        else:
            self.section = elf.sections[int(section_index)]
            self.absolute = False

    def offset(self):
        if self.section is None:
            if self.absolute:
                return self.address
            else:
                return None

        return self.address - self.section.address + self.section.offset

    def __repr__(self):
        return f"{self.name}"


def assert_equal(left, right, message):
    assert left == right, f"{message}\n{left} != {right}"


def main():
    parser = argparse.ArgumentParser(prog="diff")
    parser.add_argument("-c", "--compiled")
    parser.add_argument("-o", "--original")
    arguments = parser.parse_args()

    compiled_binary = Elf(open(arguments.compiled, "rb"))
    original_binary = Elf(open(arguments.original, "rb"))

    for compiled_symbol in sorted(compiled_binary.symbols, key=lambda s: s.address):
        if compiled_symbol.offset() is None:
            continue

        if any(
            re.fullmatch(pattern, compiled_symbol.name)
            for pattern in [
                r"__.*",
                r"_dl_relocate_static_pie",
                r"_fini",
                r"_init",
                r"_IO_stdin_used",
                r"_start",
                r"completed.\d+",
                r"dtor_idx.\d+",
                r"frame_dummy",
                r".*@GLIBC_2.2.5",
            ]
        ):
            continue

        try:
            original_symbol = next(
                s for s in original_binary.symbols if s.name == compiled_symbol.name
            )
        except StopIteration:
            demangled_name = (
                subprocess.run(
                    ["c++filt", compiled_symbol.name], check=True, capture_output=True
                )
                .stdout.decode("utf-8")
                .strip()
            )
            print(
                f"symbol {compiled_symbol.name} ({demangled_name}) not found in original binary"
            )
            sys.exit(1)

        if compiled_symbol.address != original_symbol.address:
            print(f"address mismatch for symbol {original_symbol.name}")
            print(f"compiled symbol address: {compiled_symbol.address:x}")
            print(f"original symbol address: {original_symbol.address:x}")
            sys.exit(1)

        compiled_symbol_bytes = compiled_binary.bytes[
            compiled_symbol.offset() : compiled_symbol.offset() + compiled_symbol.size
        ]
        original_symbol_bytes = original_binary.bytes[
            original_symbol.offset() : original_symbol.offset() + original_symbol.size
        ]

        if compiled_symbol_bytes != original_symbol_bytes:
            print(f"data mismatch for symbol {original_symbol.name}")

            formatter = iced_x86.Formatter(iced_x86.FormatterSyntax.NASM)

            print(f"{'compiled:': <30} original:")
            for compiled_instruction, original_instruction in itertools.zip_longest(
                iced_x86.Decoder(64, compiled_symbol_bytes, ip=compiled_symbol.address),
                iced_x86.Decoder(64, original_symbol_bytes, ip=original_symbol.address),
            ):
                left = (
                    formatter.format(compiled_instruction)
                    if compiled_instruction is not None
                    else ""
                )
                right = (
                    formatter.format(original_instruction)
                    if original_instruction is not None
                    else ""
                )

                print(f"{left: <30} {right: <30}")

            sys.exit(1)


if __name__ == "__main__":
    main()
