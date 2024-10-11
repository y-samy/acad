/*
 * Assignment 1
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\main.c /std:c11		# produces main.exe
 * gcc: gcc ./main.c -std=c89		# produces a.out or a.exe
 * clang: clang ./main.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

int main()
{
	int n;
	printf("Enter an integer: ");
	scanf("%d", &n);
	while (n) {
		printf("%d", n%10);
		n/=10;
	}
	return 0;
}
