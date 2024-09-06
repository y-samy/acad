#include <stdio.h> 
// This principally is computationally the same as just using comparison operators. So what even is the point?
int sgn(int number)
{
    unsigned int n = (unsigned) number;
    return n >> (sizeof(int)*8 -1);
}

int main() {
  int a, b, c;
  int ordered [3];
  printf("Enter three numbers: ");
  scanf("%d %d %d", &a, &b, &c);
  int avb = sgn(a-b);
  int avc = sgn(a-c);
  int bvc = sgn(b-c);
  int ia = avb + avc;
  int ib = 1 + bvc - avb;
  int ic = 2 - avc - bvc;
  ordered[ia] = a;
  ordered[ib] = b;
  ordered[ic] = c;
  printf("%d, %d & %d", ordered[0], ordered[1], ordered[2]);
  return 0;
}
