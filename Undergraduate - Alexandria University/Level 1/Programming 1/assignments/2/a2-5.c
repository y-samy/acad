/*
 * Assignment 2
 * Solution to Problem 5
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-5.c /std:c11		# produces a2-5.exe
 * gcc: gcc ./a2-5.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-5.c -w --std=c89	# produces a.out or a.exe
 */
#include <stdio.h>
long double factorial(int n)
{
    long double result = 1;
    while (n)
    {
        result *= n;
        --n;
    }
    return result;
}
int main()
{
    int n, i, j;
    long double sum = 0;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 1, j = 1; i <= n; ++i, j+=2)
    {
        sum += ((long double) j * j) / factorial(j - 1);
    }
    printf("Sum: %.7Lf", sum);
    return 0;
}