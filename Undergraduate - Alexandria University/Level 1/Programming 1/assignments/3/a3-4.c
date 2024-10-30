/*
 * Assignment 3
 * Solution to Problem 4
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a3-4.c /std:c11		# produces a3-4.exe
 * gcc: gcc ./a3-4.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a3-4.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

void markCalc(int* s1, int* s2, int* s3, float* av, int* passed, int* failed)
{
    int tot = *s1 + *s2 + *s3;
    *passed = (*s1>=50) + (*s2>=50) + (*s3>=50);
    *failed = 3 - *passed;
    *av = (float) tot / 3;
}

int main()
{
    int c1, c2, c3, pass, fail;
    float avg;
    printf("Enter your three courses marks (grade1 grade2 grade3): ");
    scanf("%d %d %d", &c1, &c2, &c3);
    markCalc(&c1, &c2, &c3, &avg, &pass, &fail);
    printf("Average: %f, Courses Passed: %d, Courses Failed: %d", avg, pass, fail);
}