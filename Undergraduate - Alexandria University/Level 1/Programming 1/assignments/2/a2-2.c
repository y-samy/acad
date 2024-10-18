/*
 * Assignment 2
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-2.c /std:c11		# produces a2-2.exe
 * gcc: gcc ./a2-2.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-2.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

void ConvSecond(int s)
{
    int hours = s / 3600;
    s %= 3600;
    int minutes = s / (60);
    s %= 60;
    int seconds = s;
    printf("%d H, %d min, %d s.\n", hours, minutes, seconds);
}

int main()
{
    int seconds = -1;
    do
    {
        printf("Enter number of seconds: ");
        scanf("%d", &seconds);
        if (seconds<0)
            printf("INVALID INPUT\n");
    } while (seconds < 0);
    ConvSecond(seconds);
    return 0;
}