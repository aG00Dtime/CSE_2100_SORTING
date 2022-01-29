//David Henry 1007604
//c11
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned int rand_time(int i);

void bubble_sort(int a[], int n);
void insertion_sort(int a[], int n);
void selection_sort(int a[], int n);
void merge_sort(int a[], int start, int end);
void quick_sort(int a[], int start, int end);

void print_array(int a[], int n);

// main
int main() {


    FILE *unsorted = fopen("unsorted_array.txt", "w");
    FILE *sorted = fopen("sorted_array.txt", "w");
    // array size
    int arr_size;


    // seed rand
    srand(rand_time(0));


    // get array size
    printf("Enter Array Size :");
    scanf("%d", &arr_size);

    printf("Creating Array...\n");



    // create array on heap to avoid stack overflow
    int *heap_array = malloc(arr_size * sizeof(heap_array));

    for (int i = 0; i < arr_size; i++) {
        //generate rand num in range arr_size
        heap_array[i] = rand() % arr_size;
    }

    // write unsorted array to file
    for (int k = 0; k < arr_size; ++k) {

        fprintf(unsorted, "%d\n", heap_array[k]);

    }

    fclose(unsorted);

    // sort menu
    int run = 1;

    while (run) {

        int choice;

        printf("\n---Choose Sorting Method---\n");
        printf("\n");
        printf("1.Bubble Sort\n");
        printf("2.Insertion Sort\n");
        printf("3.Selection Sort\n");
        printf("4.Merge Sort\n");
        printf("5.Quick Sort\n");
        printf("0.EXIT\n");


        printf("Choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                bubble_sort(heap_array, arr_size);
                run = 0;
                break;

            case 2:
                insertion_sort(heap_array, arr_size);
                run = 0;
                break;

            case 3:
                selection_sort(heap_array, arr_size);
                run = 0;
                break;

            case 4:
                printf("Sorting...\n");
                clock_t start = clock();
                merge_sort(heap_array, 0, arr_size - 1);
                clock_t end = clock();

                printf("Merge Sort elapsed time: %f seconds\n", (double) (start - end) / CLOCKS_PER_SEC);
                run = 0;
                break;

            case 5:
//
                printf("Sorting...\n");

                clock_t beg = clock();

                quick_sort(heap_array, 0, arr_size - 1);

                clock_t stop = clock();

                printf("Quick Sort elapsed time: %f seconds\n", (double) (beg - stop) / CLOCKS_PER_SEC);

                run = 0;
                break;


            default:
                run = 0;
                break;


        }

        // write sorted array to file
        for (int k = 0; k < arr_size; ++k) {

            fprintf(sorted, "%d\n", heap_array[k]);

        }
        fclose(sorted);
        printf("\nArray state saved to file...");

    }

    printf("\n...Exiting");

    return 0;
}

// print array func
void print_array(int a[], int n) {
    printf("Array :: [");

    for (int k = 0; k < n; ++k) {
        printf(" %d ", a[k]);
    }

    printf("]\n");

}

// from // from https://www.geeksforgeeks.org/c-program-for-time-complexity-plot-of-bubble-insertion-and-selection-sort-using-gnuplot/
// bubble sort
void bubble_sort(int a[], int n) {
    printf("\nSorting...\n");
    clock_t start = clock();

    int i = 0, j = 0, tmp;
    for (i = 0; i < n; i++) {   // loop n times - 1 per element
        for (j = 0; j < n - i - 1; j++) { // last i elements are sorted already
            if (a[j] > a[j + 1]) {  // swap if order is broken
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    clock_t end = clock();
    printf("Bubble Sort elapsed time: %f seconds\n", (double) (start - end) / CLOCKS_PER_SEC);
}

// Insertion sort
void insertion_sort(int a[], int n) {
    printf("\nSorting\n");
    clock_t start = clock();

    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
    clock_t end = clock();

    printf("Insertion Sort elapsed time: %f seconds\n", (double) (start - end) / CLOCKS_PER_SEC);

}

// from thecrazyprogrammer.com
int quick_sort_part(int a[], int start, int end) {


    // the pivot is set to the last element of the given array
    int pivot;

    int i = start - 1; // start point
    pivot = a[end];

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

// selection_sort
void selection_sort(int a[], int n) {
    printf("Sorting...\n");

    clock_t start = clock();

    int temp;
    // loop over array elements
    for (int i = 0; i < n; ++i) {

        for (int j = i + 1; j < n; ++j) {

            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;

            }

        }

    }

    clock_t end = clock();
    printf("Selection Sort elapsed time: %f seconds\n", (double) (start - end) / CLOCKS_PER_SEC);

}

// merge sort merge array func with my fix to prevent the stack from overflowing
void merge_sub_arrays(int a[], int start, int mid, int end) {

    int left = mid - start + 1;
    int right = end - mid;
	
    // heap arrays to prevent the stack from overflowing
    int *heap_left = malloc(left * sizeof(heap_left));
    int *heap_right = malloc(right * sizeof(heap_right));

    // allocate to sub lists
    for (int j = 0; j < right; ++j) {
        heap_right[j] = a[mid + 1 + j];
    }

    for (int i = 0; i < left; ++i) {
        heap_left[i] = a[start + i];
    }

    int i = 0, j = 0, k = start;

    while (i < left && j < right) {

        if (heap_left[i] <= heap_right[j]) {
            a[k] = heap_left[i];
            i++;

        } else {
            a[k] = heap_right[j];
            j++;

        }
        k++;

    }


    while (i < left) {
        a[k] = heap_left[i];
        i++;
        k++;

    }

    while (j < right) {
        a[k] =  heap_right[j];
        j++;
        k++;

    }

}

// merge sort
void merge_sort(int a[], int start, int end) {

    if (start < end) {

        int mid = (start + end) / 2;

        merge_sort(a, start, mid);

        merge_sort(a, mid + 1, end);

        merge_sub_arrays(a, start, mid, end);

    }
}

// seed gen
unsigned int rand_time(int i) {
    return 0;
};
