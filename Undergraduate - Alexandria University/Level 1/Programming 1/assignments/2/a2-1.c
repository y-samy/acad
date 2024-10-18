/*
 * Assignment 2
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a2-1.c /std:c11		# produces a2-1.exe
 * gcc: gcc ./a2-1.c -std=c89		# produces a.out or a.exe
 * clang: clang ./a2-1.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

int Calculate(int num1, int num2, char op);

int main()
{
    int n1 = 0, n2 = 0;
    char op = 0;
    printf("First number: ");
    scanf("%d", &n1);
    do
    { /* operator validation */
        printf("Operator (+, -, *, /, %%): ");
        scanf("%c", &op);
        if (op == '\n') /* scanf shenanegans */
            scanf("%c", &op);
        if (op != '+' && op != '-' && op != '*' && op != '/' && op != '%')
        {
            printf("INVALID OPERATOR\n");
            op = 0;
        }
    } while (!op);

    while (1)
    { /* zero-division protection */
        printf("Second number: ");
        scanf("%d", &n2);
        if (n2 || op != '/')
            break;
        printf("CANNOT DIVIDE BY ZERO\n");
    }
    printf("Result: %d", Calculate(n1, n2, op));
    return 0;
}

int Calculate(int num1, int num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 - num2;
    case '/':
        return num1 / num2;
    case '%':
        return num1 % num2;
    }
}