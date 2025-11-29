#include <stdio.h>
#include <stdlib.h>

// Function to print a single partition in the specified format
void print_partition(int **subsets, int k, int *subset_sizes) {
    for (int i = 0; i < k; ++i) {
        printf("{");
        for (int j = 0; j < subset_sizes[i]; ++j) {
            printf("%d", subsets[i][j]);
            if (j + 1 < subset_sizes[i]) {
                printf(", ");
            }
        }
        printf("}");
        if (i + 1 < k) {
            printf(", ");
        }
    }
    printf("\n");
}

/**
 * @brief Recursively generates all partitions of an array into k non-empty subsets.
 *
 * @param arr The input array of elements.
 * @param n The total number of elements.
 * @param k The desired number of subsets.
 * @param idx The current element from arr to be placed into a subset.
 * @param subsets A 2D array to store the current partition.
 * @param subset_sizes An array tracking the current size of each subset.
 * @param filled_subsets The number of subsets that are currently non-empty.
 */
void generate_partitions(int *arr, int n, int k, int idx, int **subsets, int *subset_sizes, int filled_subsets) {
    // Base case: If all elements have been placed
    if (idx == n) {
        // If exactly k subsets are non-empty, print the partition
        if (filled_subsets == k) {
            print_partition(subsets, k, subset_sizes);
        }
        return;
    }

    // Try placing the current element (arr[idx]) into each of the k subsets
    for (int i = 0; i < k; ++i) {
        // If the current subset is not empty, add the element to it
        if (subset_sizes[i] > 0) {
            subsets[i][subset_sizes[i]++] = arr[idx];
            generate_partitions(arr, n, k, idx + 1, subsets, subset_sizes, filled_subsets);
            // Backtrack: remove the element to explore other possibilities
            subset_sizes[i]--;
        } else {
            // If the subset is empty, this is the first element for this subset.
            subsets[i][subset_sizes[i]++] = arr[idx];
            // Recurse with an increased count of filled subsets.
            generate_partitions(arr, n, k, idx + 1, subsets, subset_sizes, filled_subsets + 1);
            // Backtrack
            subset_sizes[i]--;
            
            // To avoid permutations of subsets (e.g., {{1},{2}} vs {{2},{1}}),
            // once we place an element in an empty subset, we don't try
            // placing it in other empty subsets.
            break;
        }
    }
}

int main() {
    int n, k;

    // Read n and k from standard input
    if (scanf("%d %d", &n, &k) != 2 || n < k || k <= 0) {
        printf("Invalid input. Ensure n >= k and k > 0.\n");
        return 1;
    }

    // Create an array {1, 2, ..., n}
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    // Allocate memory for subsets and their sizes
    int **subsets = malloc(k * sizeof(int*));
    for (int i = 0; i < k; ++i) {
        subsets[i] = malloc(n * sizeof(int));
    }
    int *subset_sizes = calloc(k, sizeof(int));

    // Start the recursive generation of partitions
    generate_partitions(arr, n, k, 0, subsets, subset_sizes, 0);

    // Free all dynamically allocated memory
    for (int i = 0; i < k; ++i) {
        free(subsets[i]);
    }
    free(subsets);
    free(subset_sizes);

    return 0;
}
