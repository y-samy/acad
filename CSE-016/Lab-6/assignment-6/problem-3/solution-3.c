#include <stdio.h>
#include <string.h>
int palindrome(char str[], int len);
char input[] = {};
int main()
{
	printf("Enter statement:\n");
	gets(input);
	int length = strlen(input), i, j;
	for (i = 0; i < length;)
	{
		if (input[i] == ' ')
		{
			for (j = i; j < length; j++)
			{
				input[j] = input[j + 1];
			}
			length--;
		}
		else
		{
			i++;
		}
	}
printf("%s : is %s palindrome.\n",input, (palindrome(input, length) ? "a" : "not a"));
	return 0;
}

int palindrome(char str[], int len)
{
	int i;
	len--;
	for (i = 0; i < len; i++)
	{
		if (str[i] != str[len - i])
			return 0;
	}
	return 1;
}