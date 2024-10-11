/*
 * Assignment 1
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\main.c /std:c11		# produces main.exe
 * gcc: gcc ./main.c -std=c89		# produces a.out or a.exe
 * clang: clang ./main.c -w --std=c89	# produces a.out or a.exe
 */

#include <stdio.h>

int digits(int n)
{
	int l = 1;
	while (n/=10)
		++l;
	return l;
}

int ipow(int n, int p)
{
	/* Limited checks for this program's purposes */
	if (n == 0 || n == 1)
		return n;
	int r=1;
	while (p--)
		r*=n;
	return r;
}

int main()
{
	int n;
	printf("Please enter the number: ");
	scanf("%d", &n);
	int d = digits(n);
	int i, s = 0, temp = n;
	for (i = 0; i < d; ++i) {
		s += ipow(temp%10, d);
		temp/=10;
	}
	if (s == n)
		printf("This number is Armstrong's number");
	else
		printf("This number is not an Armstrong number");
	return 0;
}
