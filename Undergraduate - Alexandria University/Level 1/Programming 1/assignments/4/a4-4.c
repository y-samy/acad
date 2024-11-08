/*
 * Assignment 4
 * Solution to Problem 4
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a4-4.c /std:c11           # produces a4-4.exe
 * gcc: gcc ./a4-4.c -std=c11           # produces a.out or a.exe
 * clang: clang ./a4-4.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int Occurrence (int* x, int n, int y);

int main()
{
    int arr_size, occ_size, i, j, k, found;
    printf("Enter number of elements: ");
    scanf("%d", &arr_size);
    occ_size = 2 * (arr_size+1);
    /*
     * malloc is optional, but I want to train myself on it
     * can be replaced by arr[size] = {}
     * and occurrence_matrix[size+1][2] = {}
     * the first subarray in occurrence_matrix is reserved for the occurrence of zeroes
     */
    int* arr = malloc(sizeof(arr_size) * arr_size);
    int* occurrence_matrix = malloc(sizeof(occ_size) * occ_size);

    printf("Enter %d elements: ", arr_size);
    for (i = 0; i<arr_size; ++i)
        scanf("%d", (arr+i));
    
    /* calloc alternative */
    for (i = 0; i < occ_size; ++i)
        *(occurrence_matrix+i) = 0;

    for (i = 0, j = 2; i<arr_size; ++i){
        if (*(arr+i) == 0){
            if (*(occurrence_matrix+1)) continue;
            *(occurrence_matrix+1) = Occurrence(arr, arr_size, 0);
        } else {
            found = 0;
            for (k = 2; k < occ_size; k += 2)
                if (*(occurrence_matrix+k) == *(arr+i)){
                    found = 1;
                    break;
                }
            if (found) continue;
            *(occurrence_matrix+j) = *(arr+i);
            *(occurrence_matrix+j+1) = Occurrence(arr, arr_size, *(arr+i));
            j += 2;
        }
    }
    printf("Occurrence of numbers:\n");
    if (*(occurrence_matrix+1)) printf("0\t %d times\n", *(occurrence_matrix+1));
    for (i = 2; i < occ_size; i+=2)
        if (!(*(occurrence_matrix+i))) break;
        else printf("%d\t %d times\n", *(occurrence_matrix+i), *(occurrence_matrix+i+1));

    free(arr);
    free(occurrence_matrix);
    return 0;
}

int Occurrence (int* x, int n, int y)
{
    int i, count = 0;
    for (i = 0; i < n; ++i){
        if (*(x+i) == y) ++count;
    }
    return count;
}