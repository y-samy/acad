/*
* Assignment 5
 * Solution to Problem 4
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a5-4.c /std:c11           # produces a5-4.exe
 * gcc: gcc ./a5-4.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a5-4.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>

#define MAX_LEN 12

int atoi(const char *str);

int main() {
    char str[MAX_LEN] = {};
    printf("Enter a newline-terminated string: \n");
    fgets(str, MAX_LEN, stdin);
    printf("The number: %d\n", atoi(str));
    return 0;
}

int atoi(const char *str) {
    int i = 0, num = 0, sign = 1;
    while (str[i] == ' ' && i < MAX_LEN) ++i;
    if (str[i] == '-') {
        sign = -1;
        ++i;
    }
    while (i < MAX_LEN && str[i] >= '0' && str[i] <= '9') {
        num *= 10;
        num += (str[i] - '0');
        ++i;
    }
    return num * sign;
}
