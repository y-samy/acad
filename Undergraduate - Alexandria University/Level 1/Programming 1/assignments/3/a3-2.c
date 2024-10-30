/*
 * Assignment 3
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a3-2.c /std:c11		# produces a3-2.exe
 * gcc: gcc ./a3-2.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a3-2.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

int GCD(int x, int y)
{
    return (y==0)?x:GCD(y, x % y);
}

int main()
{
    int x, y;
    printf("Enter two numbers (x y): ");
    scanf("%d %d", &x, &y);
    printf("GCD: %d", GCD(x, y));
    return 0;
}