#!/bin/bash

nasm -f elf -g -F dwarf test/$1.nasm -o $1.o

ld -m elf_i386 -o $1 $1.o

./$1
