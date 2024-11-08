/*
 * Assignment 4
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a4-2.c /std:c11           # produces a4-2.exe
 * gcc: gcc ./a4-2.c -std=c11           # produces a.out or a.exe
 * clang: clang ./a4-2.c -w --std=c11   # produces a.out or a.exe
 * DISCALIMER: THIS PROGRAM IS NOT SUPPORTED BY C STANDARDS EARLER THAN C99
 */

#include <stdio.h>

void driver(int arr[], int arr_size, int *prime_count, int *perfect_count);
int isPrime(int x);
int isPerfect(int x);

int main()
{

    int number_of_primes, number_of_perfects, size, i;
    printf("Enter array size: ");
    scanf("%d", &size);
    int array[size] = {};
    printf("Enter a new-line or space separated list of %d numbers: ", size);
    for (i = 0; i < size; ++i)
        scanf("%d", &array[i]);
    driver(array, size, &number_of_primes, &number_of_perfects);
    printf("Number of prime numbers: %d\n", number_of_primes);
    printf("Number of perfect numbers: %d", number_of_perfects);
    return 0;
}

void driver(int arr[], int arr_size, int *prime_count, int *perfect_count)
{
    int i;
    *prime_count = *perfect_count = 0;
    for (i = 0; i < arr_size; ++i)
    {
        *prime_count += isPrime(arr[i]);
        *perfect_count += isPerfect(arr[i]);
    }
}

int isPrime(int x)
{
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (!(x%2)) return 0;
    int i;
    for (i = 3; i*i <= x; i+=2)
        if (!(x%i)) return 0;
    return 1;
}

int isPerfect(int x)
{
    /* Uses the Euclid–Euler theorem */
    if (x%2) return 0; /* unproven assumption: no non-even perfect numbers exist */
    int copy = x;
    int even_pair = 1;
    while (copy){
        if (copy%2) break;
        copy/=2;
        even_pair *= 2;
    }
    if (2*even_pair-1 == copy && isPrime(copy)) return 1;
    return 0;
}