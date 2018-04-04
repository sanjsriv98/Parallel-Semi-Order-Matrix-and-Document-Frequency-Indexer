//2015A7PS0102P 2015A7PS0127P
#include "semiorder.h"

//global shared variables
int answerflg;

Pos answer;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <num_workers>" << endl;
		exit(-1);
	}
	int nwork = atoi(argv[1]);
	omp_set_num_threads(nwork);
	answerflg = 0;
	int x, y, i, j, k;
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
	printf("READING COMPLETE\n");
	int itr = x;
	int *key = (int *)malloc(itr * sizeof(int)); // = mat[99][99];
	srand(time(0));
	int upperbound = x * y;
	// #pragma omp parallel for
	for (i = 0; i < itr; i++)
		key[i] = (rand()) % (upperbound);
	double start = omp_get_wtime();
	for (k = 0; k < itr; k++)
	{
		answerflg = 0;
		int num = 0, temp = x;
		while (temp > 1 && temp % 2 == 0)
		{
			num++;
			temp = temp / 2;
		}
		unsigned int width = 1;
		width = width << num;
		// printf("width %d \n", width);
		int size = temp;
		int i, j;
#pragma omp parallel num_threads(nwork)
#pragma omp for schedule(dynamic, 1) collapse(2) private(i, j)
		for (i = 0; i < width; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (answerflg == 1)
				{
#pragma omp cancel for
					// continue;
				}
				else
				{
					int fromx = i * size, fromy = j * size, tox = (1 + i) * size - 1, toy = (1 + j) * size - 1;
					// printf("%d %d %d %d\n", fromx, tox, fromy, toy);
					if (mat[fromx][fromy] > key[k] || mat[tox][toy] < key[k])
					{
						continue;
					}
					else
					{
						SubMatrix corners = (SubMatrix)malloc(sizeof(submatrix));
						corners->fromx = fromx;
						corners->tox = tox;
						corners->fromy = fromy;
						corners->toy = toy;
						search(mat, corners, key[k]);
						free(corners);
					}
				}
			}
			//IMPORTANT: no code in here
		}
		if (answerflg == 1)
		{
			answerflg = 0;
			// if (key[k] != mat[answer->x][answer->y])
			// printf("%d %d\n",answer->x,answer->y);
		}
		else
		{
			printf("FAILED %d\n", key[k]);
		}
		free(answer);
	}
	double end = omp_get_wtime();
	for (i = 0; i < x; i++)
	{
		free(mat[i]);
	}
	free(mat);
	printf("Time : %f\n\n", end - start);
	return 0;
}

void search(int **mat, SubMatrix corners, int key)
{
	int i = corners->fromx, j = corners->toy;
	while (i <= corners->tox && j >= corners->fromy)
	{
		if (mat[i][j] == key)
		{
			answerflg = 1;
			answer = (Pos)malloc(sizeof(pos));
			answer->x = i;
			answer->y = j;
			return;
		}
		if (mat[i][j] > key)
			j--;
		else
			i++;
	}
	return;
}