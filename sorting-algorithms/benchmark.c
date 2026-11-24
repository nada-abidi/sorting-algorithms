#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sorting.h"
#include "benchmark.h"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#elif defined(_unix_) || defined(_APPLE_)
#include <sys/resource.h>
#endif

#define RUNS 5

typedef void (*SortFunction)(int[], int);

/* Wrappers for Merge Sort and Quick Sort */

void runMerge(int arr[], int n)
{
    mergeSort(arr, 0, n - 1);
}

void runQuick(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}

/* Get peak process memory in MB */

double getPeakMemoryMB(void)
{
#ifdef _WIN32

    PROCESS_MEMORY_COUNTERS pmc;

    if (GetProcessMemoryInfo(
        GetCurrentProcess(),
        &pmc,
        sizeof(pmc)))
        {
        return (double)pmc.PeakWorkingSetSize
               / (1024.0 * 1024.0);
    }

#elif defined(_unix_) || defined(_APPLE_)

    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
#ifdef _APPLE_
        return (double)usage.ru_maxrss
               / (1024.0 * 1024.0);
#else
        return (double)usage.ru_maxrss / 1024.0;
#endif
    }

#endif

    return -1.0;
}

/* Check if array is sorted */

int isSorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return 0;
    }

    return 1;
}

/* Measure one algorithm */

void measureAlgorithm(
    const char *name,
    SortFunction sort,
    int original[],
    int n)
{
    double totalTime = 0;
    double peakMemory = -1;

    for (int r = 0; r < RUNS; r++)
    {
        int *copy = malloc(n * sizeof(int));

        if (copy == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }

        memcpy(copy, original, n * sizeof(int));

        clock_t start = clock();

        sort(copy, n);

        clock_t end = clock();

        if (start != (clock_t)-1 &&
            end != (clock_t)-1)
        {
            double elapsed =
                ((double)(end - start) * 1000.0)
                / CLOCKS_PER_SEC;

            totalTime += elapsed;
        }

        double memory = getPeakMemoryMB();

        if (memory > peakMemory)
            peakMemory = memory;

        if (!isSorted(copy, n))
        {
            printf("Sorting error in %s!\n", name);
            free(copy);
            return;
        }

        free(copy);
    }

    printf("%-15s | %12.3f ms | %10.2f MB\n",
           name,
           totalTime / RUNS,
           peakMemory);
}

/* Execute one selected algorithm */

void executeAlgorithm(int choice, int arr[], int n)
{
    printf("\n========== BENCHMARK ==========\n");

    switch (choice)
    {
        case 1:
            measureAlgorithm(
                "Bubble Sort",
                bubbleSort,
                arr, n);
            break;

        case 2:
            measureAlgorithm(
                "Selection Sort",
                selectionSort,
                arr, n);
            break;

        case 3:
            measureAlgorithm(
                "Insertion Sort",
                insertionSort,
                arr, n);
            break;

        case 4:
            measureAlgorithm(
                "Merge Sort",
                runMerge,
                arr, n);
            break;

        case 5:
            measureAlgorithm(
                "Quick Sort",
                runQuick,
                arr, n);
            break;

        default:
            printf("Invalid algorithm choice!\n");
    }

    printf("===============================\n");
}

/* Compare all algorithms */

void compareAll(int arr[], int n)
{
    const char *names[] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort"
    };

    SortFunction algorithms[] = {
        bubbleSort,
        selectionSort,
        insertionSort,
        runMerge,
        runQuick
    };

    int standardSizes[] = {
        1000, 5000, 10000, 50000, 100000
    };

    int sizes[6];
    int count = 0;

    for (int i = 0; i < 5; i++)
    {
        if (standardSizes[i] <= n)
            sizes[count++] = standardSizes[i];
    }

    if (count == 0 || sizes[count - 1] != n)
        sizes[count++] = n;

    printf("\n========== ALGORITHMS COMPARISON ==========\n");

    for (int s = 0; s < count; s++)
    {
        int currentSize = sizes[s];

        printf("\nArray Size: %d\n", currentSize);

        printf("%-15s | %12s | %12s\n",
               "Algorithm",
               "Time",
               "Memory");

        printf("---------------------------------------------\n");

        for (int a = 0; a < 5; a++)
        {
            /*
              Quadratic algorithms are limited
              to 10000 elements to avoid very
              long execution times.
            */

            if (a < 3 && currentSize > 10000)
            {
                printf("%-15s | %12s | %12s\n",
                       names[a], "Skipped", "N/A");
                continue;
            }

            measureAlgorithm(
                names[a],
                algorithms[a],
                arr,
                currentSize);
        }
    }

    printf("\n============================================\n");
}
