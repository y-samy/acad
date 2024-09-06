#include <stdio.h>

int main()
{
	int i, j, k, A[4][3] = {0}, B[3][2] = {0}, R[4][2] = {0};
	printf("Instructions:\nInserting rows should be done in the format C1 C2 Cn\n");
	printf("=======Matrix A (4x3)=======\n");
	for (i = 0; i < 4; i++)
	{
		printf("[A] insert row (%d of 4) : 3 cols > ", (i+1));
		scanf("%d %d %d", &A[i][0], &A[i][1], &A[i][2]);
	}
	printf("=======Matrix B (3x2)=======\n");
	for (i = 0; i < 3; i++)
	{
		printf("[B] insert row (%d of 3) : 2 cols > ", (i+1));
		scanf("%d %d", &B[i][0], &B[i][1]);
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 4; k++)
			{
				R[k][j] += A[k][i] * B[i][j];
			}
		}
	}
	printf("The result of the multiplication of the previous two matrices:");
	for (i = 0; i < 4; i++)
	{	
		printf("\n[\t");
		for (j = 0; j < 2; j++)
		{
			printf("%d\t", R[i][j]);
		}
		printf("]");
	}
	return 0;
}
