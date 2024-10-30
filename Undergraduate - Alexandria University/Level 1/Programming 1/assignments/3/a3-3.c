/*
 * Assignment 3
 * Solution to Problem 3
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a3-3.c /std:c11		# produces a3-3.exe
 * gcc: gcc ./a3-3.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a3-3.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

void sadCounter(int n)
{
    if (n == 1){
        printf("1");
        return;
    }
    sadCounter(n-1);
    printf(" %d", n);
}

int main()
{
    int i;
    printf("Enter n: ");
    scanf("%d", &i);
    sadCounter(i);
}