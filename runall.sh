#!/bin/bash

for file in algos/*.c; do
	filename=${file##*/}
	filename=${filename%.c}
	echo running ${filename}...
	./run.sh ${filename} $1 $2 $3
	echo ""
done

