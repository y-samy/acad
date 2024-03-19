#include <stdio.h>
int main()
{
  float score;
  char grade[] = {'F', 'D', 'C', 'B', 'A'};
  printf("Please enter your score (0-100): ");
  scanf("%f",&score);
  printf("The grade for score %.1f is %c.\n", score, grade[(score>=90)+(score>=80)+(score>=70)+(score>=60)]);
  return 0;
}
