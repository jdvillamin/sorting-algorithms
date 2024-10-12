#!/bin/bash

for i in {1..3};
do
	echo "run: ${i}"
	./runall.sh $1 $2 $3
	echo ""
done

