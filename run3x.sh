#!/bin/bash

for i in {1..3}; 
do
	echo "run: ${i}"
	./run.sh $1 $2 $3 $4
	echo ""
done

