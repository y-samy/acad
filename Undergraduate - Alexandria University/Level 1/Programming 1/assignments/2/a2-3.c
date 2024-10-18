/*
 * Assignment 2
 * Solution to Problem 3
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-3.c /std:c11		# produces a2-3.exe
 * gcc: gcc ./a2-3.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-3.c -w --std=c89	# produces a.out or a.exe
 */
#include <stdio.h>
int isPalindrome(int x)
{
    int temp = x, exponent = 1, digits = 1, temp_right, left, right = 0;
    while (temp /= 10) /* number of digits */
        ++digits;
    if (digits == 1)
        return 1;
    int i;
    for (i = 0; i < digits / 2; ++i)
        exponent *= 10;
    left = x / exponent;
    if (digits % 2)
        left /= 10; /* dropping extra digit */
    temp_right = x % exponent;
    for (i = 0; i < digits / 2; ++i)
    { /* reversing the right side */
        right *= 10;
        right += temp_right % 10;
        temp_right /= 10;
    }
    if (left == right)
        return 1;
    else
        return 0;
}

int main()
{
    int n;
    printf("Please enter a number: ");
    scanf("%d", &n);
    if (isPalindrome(n))
        printf("%d is a palindrome.", n);
    else
        printf("%d is not a palindrome.", n);
    return 0;
}