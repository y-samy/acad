/*
 * Assignment 1
 * Solution to Problem 3
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
	int n, i, sig = 1;
	long long fac = 1;
	double x, sum = 0;
	printf("Enter x: ");
	scanf("%lf", &x);
	printf("Enter n: ");
	scanf("%d", &n);
	for (i = 1; i <= n; i+=2, sig*=-1, fac*=(fac+1)*(fac+2), x*=x*x)
		sum += (sig * x) / fac;
	printf("Approximation: %lf", sum);
	return 0;
}
