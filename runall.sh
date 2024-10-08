#!/bin/sh

for file in *.c; do
	filename=${file%.c}
	gcc -o $filename.elf $file
	echo running $file...
	./$filename.elf
done
rm *.elf
