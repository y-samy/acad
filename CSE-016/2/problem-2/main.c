#include <math.h>
#include <stdio.h>

int main() {
  printf("Number\tSquare\tCube\tRoot\tExponent\n");
  printf("0\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(0, 2)), ((int) pow(0, 3)), sqrt(0), exp(0));
  printf("1\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(1, 2)), ((int) pow(1, 3)), sqrt(1), exp(1));
  printf("2\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(2, 2)), ((int) pow(2, 3)), sqrt(2), exp(2));
  printf("3\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(3, 2)), ((int) pow(3, 3)), sqrt(3), exp(3));
  printf("4\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(4, 2)), ((int) pow(4, 3)), sqrt(4), exp(4));
  printf("5\t%d\t%d\t%.1f\t%.1f\n", ((int) pow(5, 2)), ((int) pow(5, 3)), sqrt(5), exp(5));
  return 0;
}

