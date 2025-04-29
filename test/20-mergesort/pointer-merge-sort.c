#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the mergesort implementation here or in a separate header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Corrected comparison function for integers
int compare_ints(const void *a, const void *b) {
    // a and b are pointers to elements in our array, which are already pointers to integers
    int *int_a = *(int **)a;
    int *int_b = *(int **)b;

    // Now safely dereference the pointers
    return (*int_a > *int_b) - (*int_a < *int_b);
}

typedef int (*cmp_t)(const void *, const void *);

// Merge two sorted subarrays into one sorted array
void merge(void **arr, void **temp, int left, int mid, int right, cmp_t compare) {
    int i, j, k;

    // Copy data to temp array
    for (i = left; i <= right; i++) {
        temp[i] = arr[i];
    }

    i = left;     // Starting index for left subarray
    j = mid + 1;  // Starting index for right subarray
    k = left;     // Starting index for merged array

    // Merge the two subarrays back into arr[left..right]
    while (i <= mid && j <= right) {
        if (compare( &temp[i], &temp[j]) <= 0) {
            arr[k] = temp[i];
            i++;
        } else {
            arr[k] = temp[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid) {
        arr[k] = temp[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right subarray, if any
    // (not needed as they're already in place)
}

// Main mergesort function
void mergesort_internal(void **arr, void **temp, int left, int right, cmp_t compare) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Find the middle point

        // Sort first and second halves
        mergesort_internal(arr, temp, left, mid, compare);
        mergesort_internal(arr, temp, mid + 1, right, compare);

        // Merge the sorted halves
        merge(arr, temp, left, mid, right, compare);
    }
}

// Public mergesort function
void mergesort(void **arr, int size, cmp_t compare) {
    if (arr == NULL || size <= 1) {
        return;  // Already sorted
    }

    // Allocate temporary array
    void **temp = (void **)malloc(size * sizeof(void *));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Perform the merge sort
    mergesort_internal(arr, temp, 0, size - 1, compare);

    // Free temporary array
    free(temp);
}




int main() {
    // Create an array of pointers to integers
    int values[] = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    int n = sizeof(values) / sizeof(values[0]);
    
    // Create an array of pointers to the values
    int **array = (int **)malloc(n * sizeof(int *));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        array[i] = &values[i];
    }
    
    // Sort the array using mergesort
    mergesort((void **)array, n, compare_ints);
    
    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", *array[i]);
    }
    printf("\n");
    
    // Clean up
    free(array);
    
    return 0;
}
