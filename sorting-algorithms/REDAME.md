# Sorting Algorithms

## Project Description
This project implements and compares five sorting algorithms in C:

1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort

## Project Objectives
- Implement five sorting algorithms.
- Measure execution time.
- Measure memory usage.
- Compare algorithm performance using different array sizes.

## Array Sizes
The program tests the following array sizes:

- 1,000
- 5,000
- 10,000
- 50,000
- 100,000

Bubble Sort, Selection Sort, and Insertion Sort are skipped for sizes greater than 10,000 to reduce execution time.

## Project Files
- main.c: Main program and menu.
- sorting.c: Sorting algorithms implementation.
- sorting.h: Sorting functions declarations.
- benchmark.c: Performance measurement and comparison.
- benchmark.h: Benchmark functions declarations.

## Compilation

Compile the project using GCC:

gcc main.c sorting.c benchmark.c -o sorting.exe -lpsapi

## Execution

Run the program:

./sorting.exe

On Windows PowerShell:

.\sorting.exe

## Features
- Interactive menu.
- Individual algorithm execution.
- Comparison of all algorithms.
- Execution time measurement.
- Memory usage measurement.
- Verification that the array is sorted correctly.

## Author
Student Project
*Note:* Memory usage represents the process's peak memory usage and is not an isolated measurement for each algorithm.
