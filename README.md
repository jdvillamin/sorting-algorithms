# Sorting Algorithms in C

This project contains various sorting algorithms implemented in C. Each are tested in terms clocks and with an ascending, descending, and random permutation of integers from `1` to `n`. 

## Files

The project contains bash scripts to automatically compile and execute the sorting algorithms.

- `run.sh`: Script to compile and run the given sorting algorithm C program.
- `run3x.sh`: Script to compile and run the given sorting algorithm C program thrice.
- `runall.sh`: Script to compile and run all sorting algorithm C programs.
- `runall3x.sh`: Script to compile and run all sorting algorithm C programs thrice.

## How to Use

**Compilation and Execution:**

To compile and run the program, use the scripts as follows:

```bash
./run.sh <filename> <arraysize> asc # ascending permutation
./run.sh <filename> <arraysize> desc # descending permutation
./run.sh <filename> <arraysize> rand <seed> # random permutation
./run3x.sh <filename> <arraysize> asc # ascending permutation 3x
./run3x.sh <filename> <arraysize> desc # descending permutation 3x
./run3x.sh <filename> <arraysize> rand <seed> # random permutation 3x
./runall.sh <arraysize> asc # ascending permutation
./runall.sh <arraysize> desc # descending permutation
./runall.sh <arraysize> rand <seed> # random permutation
./runall3x.sh <arraysize> asc # ascending permutation 3x
./runall3x.sh <arraysize> desc # descending permutation 3x
./runall3x.sh <arraysize> rand <seed> # random permutation 3x
```

Make sure to give executable permission using:

```bash
chmod +x <scriptfile>
```

**Example:**

To run insertion sort in the C program `isort.c` with a random array using `seed = 7` and an array size of `n = 10000`, use the scripts as follows:

```bash
./run.sh isort 10000 rand 7
```
