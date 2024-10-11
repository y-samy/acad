#include <stdio.h>
#include <math.h>

int getlen(int number)
{
  if (number == 0) return 1;
  return (floor(log10(number)) + 1);
}

int digitloop(int length, int number)
{
  if (length == 1) return 1;

  int b = 1;
  int rd,ld;
  do
  {
    ld = (number / ((int)pow(10,(length - b)))) - (number / ((int)pow(10,(length + 1 - b)))) * 10;
    rd = (number % ((int)pow(10, b)))/((int) pow(10, b-1));
    if (ld != rd) return 0; 
  }
  while(++b<=(length/2));
  return 1;
}
int main()
{
  int num;
  printf("Enter the integer to check if it is a palindrome: ");
  scanf("%d", &num);
  int len = getlen(num);
  int ispalindrome = digitloop(len, num);
  if (ispalindrome) printf("The number %d is a palindrome.\n", num);
  else printf("The number %d is NOT a palindrome.\n", num);
  return 0;
}


