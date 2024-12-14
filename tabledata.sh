#!/bin/bash

for i in {1..3}; 
do
    size1=$(($2))
	./run.sh $1 $size1 asc
done

echo ""

for i in {1..3};
do
    size2=$(($2 * 2))
    ./run.sh $1 $size2 asc
done

echo ""

for i in {1..3};
do
    size4=$(($2 * 4))
    ./run.sh $1 $size4 asc
done

echo ""

for i in {1..3};
do
    size8=$(($2 * 8))
    ./run.sh $1 $size8 asc
done

echo ""

for i in {1..3}; 
do
    size1=$(($2))
	./run.sh $1 $size1 rand 7
done

echo ""

for i in {1..3};
do
    size2=$(($2 * 2))
    ./run.sh $1 $size2 rand 7
done

echo ""

for i in {1..3};
do
    size4=$(($2 * 4))
    ./run.sh $1 $size4 rand 7
done

echo ""

for i in {1..3};
do
    size8=$(($2 * 8))
    ./run.sh $1 $size8 rand 7
done

echo ""

for i in {1..3}; 
do
    size1=$(($2))
	./run.sh $1 $size1 rand 13
done

echo ""

for i in {1..3};
do
    size2=$(($2 * 2))
    ./run.sh $1 $size2 rand 13
done

echo ""

for i in {1..3};
do
    size4=$(($2 * 4))
    ./run.sh $1 $size4 rand 13
done

echo ""

for i in {1..3};
do
    size8=$(($2 * 8))
    ./run.sh $1 $size8 rand 13
done

echo ""

for i in {1..3}; 
do
    size1=$(($2))
	./run.sh $1 $size1 rand 17
done

echo ""

for i in {1..3};
do
    size2=$(($2 * 2))
    ./run.sh $1 $size2 rand 17
done

echo ""

for i in {1..3};
do
    size4=$(($2 * 4))
    ./run.sh $1 $size4 rand 17
done

echo ""

for i in {1..3};
do
    size8=$(($2 * 8))
    ./run.sh $1 $size8 rand 17
done

echo ""

for i in {1..3}; 
do
    size1=$(($2))
	./run.sh $1 $size1 desc
done

echo ""

for i in {1..3};
do
    size2=$(($2 * 2))
    ./run.sh $1 $size2 desc
done

echo ""

for i in {1..3};
do
    size4=$(($2 * 4))
    ./run.sh $1 $size4 desc
done

echo ""

for i in {1..3};
do
    size8=$(($2 * 8))
    ./run.sh $1 $size8 desc
done

echo ""
