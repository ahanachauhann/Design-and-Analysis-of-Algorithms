#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge Sort Implementation
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort Implementation
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Performance comparison function
void compare_performance() {
    int n = 10000;
    int *arr_merge = (int *)malloc(n * sizeof(int));
    int *arr_quick = (int *)malloc(n * sizeof(int));

    // Fill arrays with random values
    for (int i = 0; i < n; i++) {
        arr_merge[i] = rand() % 10000;
        arr_quick[i] = arr_merge[i];  // Copy to the second array for comparison
    }

    // Measure time for Merge Sort
    clock_t start_time = clock();
    merge_sort(arr_merge, 0, n - 1);
    clock_t end_time = clock();
    double merge_sort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Merge Sort Time: %.6f seconds\n", merge_sort_time);

    // Measure time for Quick Sort
    start_time = clock();
    quick_sort(arr_quick, 0, n - 1);
    end_time = clock();
    double quick_sort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Quick Sort Time: %.6f seconds\n", quick_sort_time);

    // Free allocated memory
    free(arr_merge);
    free(arr_quick);
}

int main() {
    compare_performance();
    return 0;
}
