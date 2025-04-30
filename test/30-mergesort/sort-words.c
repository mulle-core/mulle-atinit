#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Function prototype for our mergesort */
int mulle_mergesort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *));

/* Case-insensitive string comparison function */
int compare_strings_case_insensitive(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcasecmp(str_a, str_b);
}

/* comparison function for qsort */
int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

/* Reverse comparison function for qsort */
int compare_strings_reverse(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return -strcmp(str_a, str_b);
}


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


/* Helper function to print array and run mergesort */
void test_mergesort(const char **strings, size_t count, const char *description) {
    printf("\n=== %s ===\n", description);
    
    /* Print original array */
    printf("Before sorting:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    
    /* Run mergesort */
    mergesort( (void **) strings, count, compare_strings_case_insensitive);
    
    /* Print result */
    printf("\nAfter mergesort:\n");
     for (size_t i = 0; i < count; i++) {
         printf("%s\n", strings[i]);
    }
    
    printf("-------------------------------\n");
}

int main() {
    /* Create an array of strings in non-sorted order */
    const char *original_strings[] = {
        "jungle", "Elephant", "Fig", "apple", 
        "dinosaur", "Banana",
        "hello", "Cherry",
        "grape", "igloo", "Dinosaur", "banana",
        "Apple", "Hello", "elephant", "Igloo",
        "cherry", "Jungle", "Grape", "fig"
    };
    size_t count = sizeof(original_strings) / sizeof(original_strings[0]);
    
    /* Create copies for each test */
    const char **unsorted_copy = malloc(count * sizeof(const char *));
    const char **qsorted_copy  = malloc(count * sizeof(const char *));
    const char **reverse_copy  = malloc(count * sizeof(const char *));
    
    if (!unsorted_copy || !qsorted_copy || !reverse_copy) {
        printf("Memory allocation failed\n");
        free(unsorted_copy);
        free(qsorted_copy);
        free(reverse_copy);
        return 1;
    }
    
    /* Initialize all arrays with original strings */
    for (size_t i = 0; i < count; i++) {
        unsorted_copy[i] = original_strings[i];
        qsorted_copy[i] = original_strings[i];
        reverse_copy[i] = original_strings[i];
    }
    
    /* Pre-sort the second array with qsort */
    qsort(qsorted_copy, count, sizeof(const char *), compare_strings);
    
    /* Pre-sort the third array in reverse order */
    qsort(reverse_copy, count, sizeof(const char *), compare_strings_reverse);
    
    /* Run tests */
    test_mergesort(unsorted_copy, count, "Test 1: Unsorted Array");
    test_mergesort(qsorted_copy, count, "Test 2: Already Sorted Array (qsort)");
    test_mergesort(reverse_copy, count, "Test 3: Reverse Sorted Array");
    
    /* Clean up */
    free(unsorted_copy);
    free(qsorted_copy);
    free(reverse_copy);
    
    return 0;
}
