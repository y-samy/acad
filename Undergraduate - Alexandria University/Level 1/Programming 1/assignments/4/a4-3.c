/*
 * Assignment 4
 * Solution to Problem 3
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a4-3.c /std:c11           # produces a4-3.exe
 * gcc: gcc ./a4-3.c -std=c11           # produces a.out or a.exe
 * clang: clang ./a4-3.c -w --std=c11   # produces a.out or a.exe
 * DISCALIMER: THIS PROGRAM IS NOT SUPPORTED BY C STANDARDS EARLER THAN C99
 */

#include <stdio.h>

int main()
{
    int s1, s2, s3, i, s1_offset, s2_offset;
    printf("Enter first array's size: ");
    scanf("%d", &s1);
    int arr1[s1] = {};
    printf("Enter %d space or new-line separated, sorted elements: ", s1);
    for (i = 0; i<s1; ++i)
        scanf("%d", &arr1[i]);
    printf("Enter second array's size: ");
    scanf("%d", &s2);
    int arr2[s2] = {};
    printf("Enter %d space or new-line separated, sorted elements: ", s2);
    for (i = 0; i<s2; ++i)
        scanf("%d", &arr2[i]);
    s3 = s1+s2;
    s1_offset = s1;
    s2_offset = s2;
    int arr3[s3] = {};
    for (i = 0; i < s3; ++i)
    {
        if (s1_offset && s2_offset){
            arr3[i] = (arr1[s1-s1_offset]>arr2[s2-s2_offset])?arr2[s2-s2_offset]:arr1[s1-s1_offset];
            if (arr1[s1-s1_offset]>arr2[s2-s2_offset]) --s2_offset;
            else --s1_offset;
        }
        else if (s1_offset){
            arr3[i] = arr1[s1-s1_offset];
            --s1_offset;
        }
        else if (s2_offset){
            arr3[i] = arr2[s2-s2_offset];
            --s2_offset;
        }
        printf("%d ", arr3[i]);
    }
    return 0;
}