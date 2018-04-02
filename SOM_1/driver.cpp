
#include "semiorder.h"

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
	int itr = 600;
	int key[itr]; // = mat[99][99];
	srand(time(0));
	int upperbound = x * y;
	for (i = 0; i < itr; i++)
		key[i] = (rand()) % (upperbound);
	// printf("key: %d\n", key);
	// key = 100;
	// SubMatrix corners = (SubMatrix)calloc(1, sizeof(submatrix));
	// corners->tox = x - 1;
	// corners->toy = y - 1;
	printf("FOR STARTING\n");
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
		// printf("num %d \n", num);
		unsigned int width = 1;
		width = width << num;
		// printf("width %d \n", width);
		int size = temp;
#pragma omp parallel for schedule(dynamic, 1) collapse(2)
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
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
				//parallelize this code here
			}
			//IMPORTANT: no code in here
		}
		// if (answerflg == 1)
		// {
		// 	printf("X-Index: %d\t Y-Index: %d\n", answer->x, answer->y);
		if (key[k] != mat[answer->x][answer->y])
			printf("%d %d\n", key[k], mat[answer->x][answer->y]);
		// }
		// else
		// {
		// 	printf("FAILED \n");
		// }
		free(answer);
	}
	double end = omp_get_wtime();
	// free(corners);
	for (i = 0; i < x; i++)
	{
		free(mat[i]);
	}
	free(mat);

	printf("Time : %f\n\n", end - start);
	// if (answerflg == 1)
	// {
	// 	printf("X-Index: %d\t Y-Index: %d\n", answer->x, answer->y);
	// 	printf("%d %d\n", key, mat[answer->x][answer->y]);
	// }
	// else
	// {
	// 	printf("FAILED \n");
	// }
	return 0;
}

void search(int **mat, SubMatrix corners, int key)
{
	int i = corners->fromx, j = corners->toy;
	while (i <= corners->tox && j >= corners->fromy)
	{
		if (mat[i][j] == key)
		{
			// printf("key Found at %d, %d", i, j);
			answerflg = 1;
			answer = (Pos)malloc(sizeof(pos));
			answer->x = i;
			answer->y = j;
			return;
		}
		if (mat[i][j] > key)
			j--;
		else //  if mat[i][j] < x
			i++;
	}
	return;
}

// SubMatrix makecopy(SubMatrix m)
// {
// 	SubMatrix n = (SubMatrix)malloc(sizeof(submatrix));
// 	n->fromx = m->fromx;
// 	n->tox = m->tox;
// 	n->fromy = m->fromy;
// 	n->toy = m->toy;
// 	return n;
// }