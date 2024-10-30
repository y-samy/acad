/*
 * Assignment 3
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a3-1.c /std:c11		# produces a3-1.exe
 * gcc: gcc ./a3-1.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a3-1.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

int sum(int n)
{
    if (n > 1)
        return n*(!(n%2) || !(n%3)) + sum(n-1);
    if (n < 1)
        return n*(!(n%2) || !(n%3)) - sum(-n-1);
    if (n == 1)
        return 0;

}

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Sum: %d", sum(n));
    return 0;
}