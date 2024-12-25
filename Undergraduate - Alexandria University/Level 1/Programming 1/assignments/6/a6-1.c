/*
* Assignment 6
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a6-1.c /std:c11           # produces a6-1.exe
 * gcc: gcc ./a6-1.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a6-1.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>

typedef struct {
    int Num;
    int Denom;
} FRAC;

int lcm(int a, int b) {
    if (a == b) return a;
    int max, min;
    max = (a > b) ? a : b;
    min = (a > b) ? b : a;
    if (max % min) return max * min;
    return max;
}

FRAC Multiply_fractions (FRAC n, FRAC m) {
    FRAC ans;
    ans.Num = n.Num * m.Num;
    ans.Denom = n.Denom * m.Denom;
    return ans;
}

FRAC Divide_fractions (FRAC n, FRAC m) {
    FRAC reciprocal;
    reciprocal.Num = m.Denom;
    reciprocal.Denom = m.Num;
    return Multiply_fractions(n, reciprocal);
}

FRAC Add_fractions (FRAC n, FRAC m) {
    FRAC ans;
    ans.Denom = lcm(n.Denom, m.Denom);
    ans.Num = (n.Num * (ans.Denom / n.Denom)) + (m.Num * (ans.Denom / m.Denom));
    return ans;
}

int main() {
    FRAC frac1, frac2, result;
    char op;
    printf("Enter fraction 1 [n/d]> ");
    scanf("%d/%d", &frac1.Num, &frac1.Denom);
    printf("Enter fraction 2 [n/d]> ");
    scanf("%d/%d", &frac2.Num, &frac2.Denom);
    printf("Choose operation: (+, *, /)> ");
    scanf(" %c", &op);
    switch (op) {
        case '+':
            result = Add_fractions(frac1, frac2);
            printf("%d/%d\n", result.Num, result.Denom);
            break;
        case '*':
            result = Multiply_fractions(frac1, frac2);
            printf("%d/%d\n", result.Num, result.Denom);
            break;
        case '/':
            result = Divide_fractions(frac1, frac2);
            printf("%d/%d\n", result.Num, result.Denom);
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
    return 0;
}