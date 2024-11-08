/*
 * Assignment 4
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a4-1.c /std:c11           # produces a4-1.exe
 * gcc: gcc ./a4-1.c -std=c11           # produces a.out or a.exe
 * clang: clang ./a4-1.c -w --std=c11   # produces a.out or a.exe
 * DISCALIMER: THIS PROGRAM IS NOT SUPPORTED BY C STANDARDS EARLER THAN C99
 */


#include <stdio.h>

void reverse(int arr[], int arr_size)
{
    int i, temp;
    for (i = 0; i < arr_size/2; ++i){
        temp = arr[i];
        arr[i] = arr[arr_size-i-1];
        arr[arr_size-i-1] = temp;
    }

}

int main()
{
    int size, i;
    printf("Enter array size: ");
    scanf("%d", &size);
    int array[size] = {};
    printf("Enter a new-line or space seperated list of %d numbers: ", size);
    for (i = 0; i < size; ++i)
        scanf("%d", &array[i]);
    reverse(array, size);
    for (i = 0; i < size; ++i)
        printf("%d ", array[i]);

    return 0;

}