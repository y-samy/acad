#include <stdio.h>

int main()
{
    int num, is_prime = 1, counter;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num < 2 || (num > 2 && num % 2 == 0))
    {
        is_prime = 0;
    } else {
        for (counter = 3; counter < num; counter = counter + 2)
        {
            if (num % counter == 0) { is_prime = 0; break; }
        }
    }
    if (is_prime)
    {
        printf("%d is a prime number\n", num);
    } else {
        printf("%d is not a prime number\n", num);
    }
    return 0;
}