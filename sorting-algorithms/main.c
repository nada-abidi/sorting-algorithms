#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include "benchmark.h"
int main()
{
    int choice;
    int n;
    srand(42);
    while (1)
    {
        printf("\n");
        printf("====================================\n");
        printf("       SORTING ALGORITHMS PROJECT\n");
        printf("====================================\n");

        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Compare All Algorithms\n");
        printf("0. Exit\n");

        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Enter a number.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (choice == 0)
        {
            printf("Thank you for using our program!\n");
            break;
        }

        if (choice < 1 || choice > 6)
        {
            printf("Invalid choice! Try again.\n");
            continue;
        }

        printf("Enter array size: ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > 1000000)
        {
            printf("Invalid array size!\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        int *array = malloc(n * sizeof(int));

        if (array == NULL)
        {
            printf("Memory allocation failed!\n");
            continue;
        }

        for (int i = 0; i < n; i++)
        {
            array[i] = rand() % 100001;
        }

        if (choice >= 1 && choice <= 5)
        {
            executeAlgorithm(choice, array, n);
            }
        else if (choice == 6)
        {
            compareAll(array, n);
        }

        free(array);
    }

    return 0;
}
