#!/bin/bash

./compilateur -n test/$1.l > $1.nasm

nasm -f elf -g -F dwarf $1.nasm -o $1.o

ld -m elf_i386 -o $1 $1.o

./$1
