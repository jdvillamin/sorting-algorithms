#!/bin/sh

gcc -o $1.elf $1.c
./$1.elf $2
rm $1.elf

