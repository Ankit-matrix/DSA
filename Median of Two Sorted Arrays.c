#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int bin_search_2(int n, int *a, int m, int *b) {
    if (n > m) {
        return bin_search_2(m, b, n, a);
    }
    
    int left = 0, right = n;
    int combined_left_count = (n + m + 1) / 2;
    
    while (left <= right) {
        int i = left + (right - left) / 2;
        int j = combined_left_count - i;

        if (i > 0 && a[i - 1] > b[j]) {
            right = i - 1;
        } else if (j > 0 && b[j - 1] > a[i]) {
            left = i + 1;
        } else {
            int max_left_of_partition;
            if (i == 0) {
                max_left_of_partition = b[j - 1];
            } else if (j == 0) {
                max_left_of_partition = a[i - 1];
            } else {
                max_left_of_partition = (a[i - 1] > b[j - 1]) ? a[i - 1] : b[j - 1];
            }

            if ((n + m) % 2 == 1) {
                return (int)max_left_of_partition;
            } else {
                int min_right_of_partition;
                if (i == n) {
                    min_right_of_partition = b[j];
                } else if (j == m) {
                    min_right_of_partition = a[i];
                } else {
                    min_right_of_partition = (a[i] < b[j]) ? a[i] : b[j];
                }
                return (int)(max_left_of_partition + min_right_of_partition) / 2;
            }
        }
    }
    return 0;
}

int main(void) {
    int n, m;
    
    // FIX: Corrected scanf format string for safer input.
    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }
    
    int *A = (int *)malloc(n * sizeof(int));
    int *B = (int *)malloc(m * sizeof(int));
    
    if (A == NULL) {
        free(B);
        return 1;
    }
    if (B == NULL) {
        free(A);
        return 1;
    }
    
    // FIX: Corrected scanf format string and added memory free on failure.
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1) {
            free(A);
            free(B);
            return 1;
        }
    }
    
    // FIX: Corrected scanf format string and added memory free on failure.
    for (size_t i = 0; i < m; i++) {
        if (scanf("%d", &B[i]) != 1) {
            free(A);
            free(B);
            return 1;
        }
    }

    int median = bin_search_2(n, A, m, B);
    printf("%d\n", median);
    
    free(A);
    free(B);
    
    return 0;
}