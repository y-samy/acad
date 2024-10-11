/*
 * Assignment 1
 * Solution to Problem 4
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\main.c /std:c11		# produces main.exe
 * gcc: gcc ./main.c -std=c89		# produces a.out or a.exe
 * clang: clang ./main.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

float fpow(float n, int p)
{
    float r = 1;
    if (p == 0)
        return 1;
    if (n == 0 || n == 1)
	return n;
    while (p--)
	    r*=n;
    return r;
}

int main()
{
    float a; int b;
    printf("y = a^b\n");
    printf("Enter a: ");
    scanf("%f", &a);
    printf("Enter b: ");
    scanf("%d", &b);
    printf("y = %f", fpow(a,b));
    return 0;
}
