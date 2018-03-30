#include <stdio.h>
#include <stdlib.h>
#include "semiorder.h"

int main()
{
	int x, y, i, j;
	scanf("%d %d", &x, &y);
	int **mat = (int **)malloc(sizeof(int *) * x);
	for (i = 0; i < x; i++)
	{
		mat[i] = (int *)malloc(sizeof(int) * y);
		for (j = 0; j < y; j++)
		{
			scanf(" %d", &mat[i][j]);
		}
	}
	int key;
	scanf("%d", &key);
	SubMatrix corners = (SubMatrix)calloc(1, sizeof(submatrix));
	corners->tox = x - 1;
	corners->toy = y - 1;
	Pos answer = search(mat, corners, key);
	if (answer)
	{
		printf("\n%d %d\n", answer->x, answer->y);
	}
	else
	{
		printf("\n FAILED\n");
	}
	return 0;
}

Pos search(int **mat, SubMatrix corners, int key)
{
	Pos middle = (Pos)malloc(sizeof(pos));
	Pos answer;
	middle->x = (corners->fromx + corners->tox) / 2;
	middle->y = (corners->fromy + corners->toy) / 2;
	if (mat[middle->x][middle->y] == key)
	{
		return middle;
	}
	else if (corners->fromx >= corners->tox && corners->fromy >= corners->toy)
	{
		return NULL;
	}
	else if (mat[middle->x][middle->y] < key)
	{
		SubMatrix quadrant1 = makecopy(corners);
		quadrant1->tox = middle->x;
		quadrant1->fromy = middle->y + 1;
		if (quadrant1->fromy <= corners->toy)
		{
			answer = search(mat, quadrant1, key);
			if (answer)
			{
				free(quadrant1);
				return answer;
			}
		}
		free(quadrant1);

		SubMatrix quadrant3 = makecopy(corners);
		quadrant3->fromx = middle->x + 1;
		quadrant3->toy = middle->y;
		if (quadrant3->fromx <= corners->tox)
		{
			answer = search(mat, quadrant3, key);
			if (answer)
			{
				free(quadrant3);
				return answer;
			}
		}
		free(quadrant3);

		SubMatrix quadrant4 = makecopy(corners);
		quadrant4->fromx = middle->x + 1;
		quadrant4->fromy = middle->y + 1;
		if (quadrant4->fromy <= corners->toy && quadrant4->fromx <= corners->tox)
		{
			answer = search(mat, quadrant4, key);
			if (answer)
			{
				free(quadrant4);
				return answer;
			}
		}
		free(quadrant4);

		return NULL;
	}
	else
	{
		SubMatrix quadrant1 = makecopy(corners);
		quadrant1->tox = middle->x - 1;
		quadrant1->fromy = middle->y;
		if (quadrant1->tox >= corners->fromx)
		{
			answer = search(mat, quadrant1, key);
			if (answer)
			{
				free(quadrant1);
				return answer;
			}
		}
		free(quadrant1);

		SubMatrix quadrant3 = makecopy(corners);
		quadrant3->fromx = middle->x;
		quadrant3->toy = middle->y - 1;
		if (quadrant3->toy >= corners->fromy)
		{
			answer = search(mat, quadrant3, key);
			if (answer)
			{
				free(quadrant3);
				return answer;
			}
		}
		free(quadrant3);

		SubMatrix quadrant2 = makecopy(corners);
		quadrant2->tox = middle->x - 1;
		quadrant2->toy = middle->y + 1;
		if (quadrant2->toy >= corners->fromy && quadrant2->tox >= corners->fromx)
		{
			answer = search(mat, quadrant2, key);
			if (answer)
			{
				free(quadrant2);
				return answer;
			}
		}
		free(quadrant2);

		return NULL;
	}
	return NULL;
}

SubMatrix makecopy(SubMatrix m)
{
	SubMatrix n = (SubMatrix)malloc(sizeof(submatrix));
	n->fromx = m->fromx;
	n->tox = m->tox;
	n->fromy = m->fromy;
	n->toy = m->toy;
	return n;
}