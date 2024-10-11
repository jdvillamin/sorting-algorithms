#!/bin/bash

gcc -o $1.elf brute.c utils.c $1.c
./$1.elf $2 $3 $4
rm $1.elf

