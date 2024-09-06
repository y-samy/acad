#include <stdio.h>

int main()
{
	int i, j, M[4][3] = {0}, max, min, pos[2][2] = {{1, 1}, {1, 1}};
	printf("Instructions:\n");
	printf("You will provide a 4x3 matrix [M]\n");
	printf("You will enter 3 numbers per input (full row) in this format:\n");
	printf("C1 C2 C3\nWhere C stands for column.\n");
	printf("====Matrix [M]====\n");
	for (i = 0; i < 4; i++)
	{
		printf("[M] insert row (%d of 4) : 3 cols > ", (i + 1));
		scanf("%d %d %d", &M[i][0], &M[i][1], &M[i][2]);
	}
	max = min = M[0][0];
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (M[i][j] > max)
			{
				max = M[i][j];
				pos[0][0] = i + 1;
				pos[0][1] = j + 1;
			}
			else if (M[i][j] < min)
			{
				min = M[i][j];
				pos[1][0] = i + 1;
				pos[1][1] = j + 1;
			}
		}
	}
	printf("Maximum number: %d. Position: Row %d, Column %d.\n", max,
	pos[0][0], pos[0][1]);
	printf("Minimum number: %d. Position: Row %d, Column %d.\n", min, pos[1][0], pos[1][1]);
	return 0;
}
