#include <stdio.h>
#include <math.h>

int main()
{
    long num;
    do {
	printf("Enter a positive integer: ");
        scanf("%ld", &num);
	if (num <= 0 )
	{
	    printf("Incorrect input. Please enter a positive number.\n");
	}
    } while (num <=0);
    int amountEven = 0, amountOdd = 0;
    int criteria = 2;
    int length = (floor(log10(num)) + 1);
    for (int count=1, rd;count<=length;count++)
    {
    	rd = (num % ((int)pow(10, count)))/((int) pow(10, count-1));
	if (rd%2){amountOdd++;}else{amountEven++;}
    }
    printf("Number: %ld\nOdds: %d\nEvens: %d\n", num, amountOdd, amountEven);
    return 0;
}
