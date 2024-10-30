/*
 * Assignment 3
 * Solution to Problem 5
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a3-5.c /std:c11		# produces a3-5.exe
 * gcc: gcc ./a3-5.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a3-5.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

void Count_Grades(int* countA, int* countB, int* countC, int* countD, int* countF)
{
    char grade;
    while(1){
        grade = getchar();
        if (grade == ' ' || grade == '\n') /* in case stdin is not flushed */
            continue;
        switch (grade)
        {
            case 'a':
            case 'A':
                ++*countA;
                break;
            case 'b':
            case 'B':
                ++*countB;
                break;
            case 'c':
            case 'C':
                ++*countC;
                break;
            case 'D':
            case 'd':
                ++*countD;
                break;
            case 'f':
            case 'F':
                ++*countF;
                break;
            case 'z':
            case 'Z':
                return;
            default:
                continue;
        }
    }
}

int main()
{
    int A, B, C, D, F;
    A = B = C = D = F = 0;
    printf("Enter your grades: \n");
    Count_Grades(&A, &B, &C, &D, &F);
    printf("Grades:\n");
    printf("A: %d\nB: %d\nC: %d\nD: %d\nF: %d", A, B, C, D, F);
    return 0;
}