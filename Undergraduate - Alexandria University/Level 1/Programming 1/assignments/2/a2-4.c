/*
 * Assignment 2
 * Solution to Problem 4
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-4.c /std:c11		# produces a2-4.exe
 * gcc: gcc ./a2-4.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-4.c -w --std=c89	# produces a.out or a.exe
 */
#include <stdio.h>
int isPrime(int n);
int CheckTwoPrime(int num);

int main()
{
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    if (CheckTwoPrime(n))
        printf("%d is a sum of two primes.", n);
    else
        printf("%d cannot be expressed as a sum of two primes.", n);
    return 0;
}

int CheckPrime(int n)
{
    if (n == 2)
        return 1;
    if (n < 2)
        return 0;
    if (!(n % 2))
        return 0;
    int i;
    for (i = 3; i * i < n; i += 2)
        if (!(n % i))
            return 0;
    return 1;
    return 0;
}

int CheckTwoPrime(int num)
{
    if (num % 2)
    {
        /* odd numbers can not be a sum of two odd numbers */
        /* only even prime number is 2 */
        /* therefore, an odd number that is a sum of two primes is n = 2 + p where p = n - 2 */
        return CheckPrime(num);
    }
    /* no need for an else, all previous outcomes return a value directly */
    int a;
    for (a = 3; a < num; a += 2)
        if (CheckPrime(a) * CheckPrime(num - a))
            return 1;
    return 0;
}
