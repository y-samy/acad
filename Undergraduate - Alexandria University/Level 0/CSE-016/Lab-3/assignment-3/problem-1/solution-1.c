#include <stdio.h>

int main()
{
  int n1, n2, n3, b, s;
  printf("Input three numbers: ");
  scanf("%d %d %d", &n1, &n2, &n3);
  // Only one comparison will evaluate to 1, the other two evaluate to 0
  b = n1*(n1 > n2 && n1 > n3);
  b += n2*(n2 > n1 && n2 > n3);
  b += n3*(n3 > n1 && n3 > n2);

  s = n1*(n1 < n2 && n1 < n3);
  s += n2*(n2 < n1 && n2 < n3);
  s += n3*(n3 < n1 && n3 < n2);

  printf("%d is the largest, %d is the Smallest.\n", b, s);
  
  return 0;
}
