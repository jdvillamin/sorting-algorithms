#!/bin/bash

if [[ $1 == gen* ]]; then
    gcc -o $1.elf lib/brute.c lib/utils.c gen-algos/$1.c
else
    gcc -o $1.elf lib/brute.c lib/utils.c algos/$1.c
fi

./$1.elf $2 $3 $4
rm $1.elf

