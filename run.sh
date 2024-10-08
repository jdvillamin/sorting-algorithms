#!/bin/sh

gcc -o $1.elf $1.c
./$1.elf
rm $1.elf

