//
// Created by david on 1/28/2022.
// quick sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quick_sort(int a[], int start, int end);


int main() {   // the quick sort pivot is set to the last element of the given array

    int array_size;

    printf("\nArray size::");
    scanf("%d", &array_size);

    // rand seed
    srand(time(0));

    //array malloc to prevent stack overflow
    printf("Creating array...\n");

    int *array = malloc(array_size * sizeof(array));

    // add rand nums to array
    for (int i = 0; i < array_size; ++i) {

        array[i] = rand() % array_size;
    }

    printf("Array created.\n");

    // file
    FILE *unsorted = fopen("unsorted_array.txt", "w");
    // write unsorted array to file
    for (int j = 0; j < array_size; ++j) {

        fprintf(unsorted, "%d\n", array[j]);
    }

    fclose(unsorted);

    // sort +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    clock_t start = clock();
    printf("Sorting...\n");

    quick_sort(array, 0, array_size - 1);

    clock_t end = clock();

    printf("Sorting finished in : %f seconds\n", (double) (start - end) / CLOCKS_PER_SEC);

    // sort +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



    // open file
    FILE *sorted = fopen("sorted_array.txt", "w");

    // write sorted array to file
    for (int k = 0; k < array_size; ++k) {

        fprintf(sorted, "%d\n", array[k]);
    }

    fclose(sorted);



    return 0;
}

int quick_sort_part(int a[], int start, int end) {

    // the pivot is set to the last element of the given array
    int pivot;

    int i = start - 1; // start point
    pivot = a[end]; // pivot

    for (int j = start; j <= end - 1; j++) {

        if (a[j] < pivot) {

            i++;
            int temp;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[end];
    a[end] = temp;

    return i + 1;
}

// quick sort
void quick_sort(int a[], int start, int end) {

    if (start < end) {

        int part = quick_sort_part(a, start, end);
        quick_sort(a, start, part - 1);
        quick_sort(a, part + 1, end);
    }
}
