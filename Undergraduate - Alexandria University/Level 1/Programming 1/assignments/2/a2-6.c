/*
 * Assignment 2
 * Solution to Problem 6
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-6.c /std:c11		# produces a2-6.exe
 * gcc: gcc ./a2-6.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-6.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>
int Leap(int year)
{
    if (!(year % 400))
        return 1;
    if (!(year % 100))
        return 0;
    if (!(year % 4))
        return 1;
}

int main()
{
    int yr;
    printf("Enter year: ");
    scanf("%d", &yr);
    if (Leap(yr))
        printf("%d is a leap year.", yr);
    else
        printf("%d is not a leap year.", yr);
    return 0;
}