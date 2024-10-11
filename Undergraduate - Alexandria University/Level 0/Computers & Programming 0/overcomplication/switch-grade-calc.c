#include <stdio.h>
// I was told a switch would take many more lines than if-elses.
// > no
int main()
{
  float score;
  int scale;
  char grade;
  printf("Please enter your score (0-100): ");
  scanf("%f",&score);
  scale = (score >= 90) + (score >= 80) + (score >= 70) + (score >= 60);
  switch(scale)
  {
    case 4:
      grade = 'A';
      break;
    case 3:
      grade = 'B';
      break;
    case 2:
      grade = 'C';
      break;
    case 1:
      grade = 'D';
      break;
    case 0:
      grade = 'F';
      break;
  }
  
  printf("The grade for score %.1f is %c \n", score, grade);
  return 0;
}