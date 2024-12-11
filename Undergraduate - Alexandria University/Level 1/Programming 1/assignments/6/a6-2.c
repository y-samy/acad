/*
* Assignment 6
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a6-2.c /std:c11           # produces a6-2.exe
 * gcc: gcc ./a6-2.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a6-2.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>
#include <math.h>

typedef struct {
    float real;
    float img;
} Complex;

Complex add_Complex(Complex a, Complex b);
void printComplex(Complex a);
Complex read_Complex();
float magnitude(Complex a);
int Compare_Complex (Complex a, Complex b);

int main(){
    Complex x, y, z, a, b;
    printf("Entering x\n");
    x = read_Complex();
    printf("Entering y\n");
    y = read_Complex();
    printf("Entering z\n");
    z = read_Complex();
    printf("x = ");
    printComplex(x);
    printf("y = ");
    printComplex(y);
    printf("z = ");
    printComplex(z);
    a = add_Complex(x, add_Complex(y, z));
    printf("x+y+z = %f + %fi\n", a.real, a.img);
    b = x;
    if (Compare_Complex(b, y) == -1) b = y;
    if (Compare_Complex(b, z) == -1) b = z;
    printf("Maximum Magnitude Entered = %f + %fi", b.real, b.img);
    return 0;
}

Complex add_Complex(Complex a, Complex b) {
    Complex c;
    c.real = a.real + b.real;
    c.img = a.img + b.img;
    return c;
}

void printComplex(Complex a) {
    printf("%f+%fi\n", a.real, a.img);
}

float magnitude(Complex a) {
    return sqrt(pow(a.real, 2) + pow(a.img, 2));
}

int Compare_Complex (Complex a, Complex b) {
    if (magnitude(a) > magnitude(b)) return 1;
    if (magnitude(a) < magnitude(b)) return -1;
    return 0;
}

Complex read_Complex() {
    Complex c;
    printf("Enter real component: ");
    scanf("%f", &c.real);
    printf("Enter imaginary component: ");
    scanf("%f", &c.img);
    return c;
}