
#include "semiorder2.h"

int answerflg, indexflg, setflg;

double start;

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
	setflg = 1;
	indexflg = 0;
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
	printf("READING COMPLETE\n");
	int itr = 10;
	int key[itr]; // = mat[99][99];
	scanf("%d", &key[0]);
	srand(time(0));
	int upperbound = x * y;
	for (i = 0; i < itr; i++)
	{
		key[i] = (rand()) % (upperbound);
	}
	SubMatrix corners;
	// SubMatrix *arr[2];
	int size = 1;
	// arr[0] = (SubMatrix *)calloc(size, sizeof(SubMatrix));
	// arr[1] = (SubMatrix *)calloc(size, sizeof(SubMatrix));
	// arr[0][0] = corners;
	start = omp_get_wtime();
	for (i = 0; i < itr; i++)
	{
		corners = (SubMatrix)calloc(1, sizeof(submatrix));
		corners->tox = x - 1;
		corners->toy = y - 1;
#pragma omp parallel shared(answerflg, answer)
#pragma omp single
		search(mat, corners, key[i]);
		if (answerflg == 1)
		{
			// printf("X-Index: %d\t Y-Index: %d\n", answer->x, answer->y);
			int answerkey = mat[answer->x][answer->y];
			printf(" %d %d\n", key[i], answerkey);
			answerflg = 0;
		}
		else
		{
			printf("FAILED \n");
		}
	}

	// 	while (setflg != 0 && answerflg != 1)
	// 	{
	// 		setflg = 0;
	// 		// free(arr[1 - indexflg]);
	// 		// arr[1 - indexflg] = (SubMatrix *)calloc(size * 3, sizeof(SubMatrix));
	// // #pragma omp parallel num_threads(nwork) shared(answerflg, indexflg, setflg, answer)
	// 		{
	// // #pragma omp for private(i)
	// 			// for (i = 0; i < size; i++)
	// 			{
	// 				// int id1 = omp_get_thread_num();
	// 				// printf("TID:%d\n", id1);
	// 				// if (!arr[indexflg][i])
	// 				// {
	// 				// 	continue;
	// 				// }
	// 				// search(mat, arr, key);
	// // 				if (answerflg == 1)
	// // 				{
	// // // #pragma omp cancel for
	// // 				}
	// 			}
	// // 			if (answerflg == 1)
	// // 			{
	// // // #pragma omp cancel parallel
	// // 			}
	// 		}
	// 		// size = 3 * size;
	// 		// indexflg = 1 - indexflg;
	// 		// search(mat, corners, key);
	// 	}
	double end = omp_get_wtime();
	// free(arr[1]);
	// free(arr[0]);
	// int answerkey = mat[answer->x][answer->y];
	free(corners);
	for (i = 0; i < x; i++)
	{
		free(mat[i]);
	}
	free(mat);

	// }
	printf("Time : %f\n\n", end - start);
	// if (answerflg == 1)
	// {
	// 	printf("X-Index: %d\t Y-Index: %d\n", answer->x, answer->y);
	// 	printf(" %d %d\n",key, answerkey);
	// }
	// else
	// {
	// 	printf("FAILED %d\n", size);
	// }
	return 0;
}

void search(int **mat, SubMatrix corners, int key)
{

	// SubMatrix corners = arr[indexflg][index];
	Pos middle = (Pos)malloc(sizeof(pos));
	// Pos answer;
	middle->x = (corners->fromx + corners->tox) / 2;
	middle->y = (corners->fromy + corners->toy) / 2;
	// printf("%d %d\n", middle->x, middle->y);

	if (corners->fromx > corners->tox && corners->fromy > corners->toy)
	{
		free(middle);
		return;
	}
	else if (mat[middle->x][middle->y] == key)
	{
		answerflg = 1;
		answer = middle;
		double answertime = omp_get_wtime();
		// #pragma omp cancel for parallel
		printf("answertime : %f\n", answertime - start);
		printf("%d %d\n", middle->x, middle->y);
		return;
	}
	else if (corners->fromx == corners->tox && corners->fromy == corners->toy)
	{
		free(middle);
		return;
	}
	else if (mat[middle->x][middle->y] < key)
	{
		Pos middletemp = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middletemp->x = middle->x;
		middletemp->y = middle->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant1 = makecopy(corners);
			quadrant1->tox = middle->x;
			quadrant1->fromy = middle->y + 1;
			if (quadrant1->fromy <= corners->toy && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][3 * index] = quadrant1;
				search(mat, quadrant1, key);
				// if (answer)
				// {
				// free(quadrant1);
				// printf("%d %d\n", answer->x, answer->y);
				// return;// answer;
				// }
			}
			else
			{
				free(quadrant1);
			}
			free(middle);
		}
		middle = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middle->x = middletemp->x;
		middle->y = middletemp->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant3 = makecopy(corners);
			quadrant3->fromx = middle->x + 1;
			quadrant3->toy = middle->y;
			if (quadrant3->fromx <= corners->tox && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][(3 * index) + 1] = quadrant3;
				search(mat, quadrant3, key);
				// if (answer)
				// {
				// free(quadrant3);
				// printf("%d %d\n", answer->x, answer->y);
				// // return;// answer;
				// }
			}
			else
			{
				free(quadrant3);
			}
			free(middle);
			// //free(quadrant3);
		}
		middle = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middle->x = middletemp->x;
		middle->y = middletemp->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant4 = makecopy(corners);
			quadrant4->fromx = middle->x + 1;
			quadrant4->fromy = middle->y + 1;
			if (quadrant4->fromy <= corners->toy && quadrant4->fromx <= corners->tox && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][(3 * index) + 2] = quadrant4;
				search(mat, quadrant4, key);
				// if (answer)
				// {
				// free(quadrant4);
				// printf("%d %d\n", answer->x, answer->y);
				// return;// answer;
				// }
			}
			else
			{
				free(quadrant4);
			}
			free(middle);
			// //free(quadrant4);
		}
		free(middletemp);
		// #pragma omp taskwait
		// return;
	}
	else
	{
		Pos middletemp = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middletemp->x = middle->x;
		middletemp->y = middle->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant1 = makecopy(corners);
			quadrant1->tox = middle->x - 1;
			quadrant1->fromy = middle->y;
			if (quadrant1->tox >= corners->fromx && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][(3 * index)] = quadrant1;
				search(mat, quadrant1, key);
				// if (answer)
				// {
				// free(quadrant1);
				// printf("%d %d\n", answer->x, answer->y);
				// return;// answer;
				// }
			}
			else
			{
				free(quadrant1);
			}
			free(middle);
			// //free(quadrant1);
		}
		middle = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middle->x = middletemp->x;
		middle->y = middletemp->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant3 = makecopy(corners);
			quadrant3->fromx = middle->x;
			quadrant3->toy = middle->y - 1;
			if (quadrant3->toy >= corners->fromy && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][(3 * index) + 1] = quadrant3;
				search(mat, quadrant3, key);
				// if (answer)
				// {
				// free(quadrant3);
				// printf("%d %d\n", answer->x, answer->y);
				// return;// answer;
				// }
			}
			else
			{
				free(quadrant3);
			}
			free(middle);
			// //free(quadrant3);
		}
		middle = (Pos)malloc(sizeof(pos));
		// Pos answer;
		middle->x = middletemp->x;
		middle->y = middletemp->y;
#pragma omp task
		{
			// int id1 = omp_get_thread_num();
			// printf("TID:%d\n", id1);
			SubMatrix quadrant2 = makecopy(corners);
			quadrant2->tox = middle->x - 1;
			quadrant2->toy = middle->y + 1;
			if (quadrant2->toy >= corners->fromy && quadrant2->tox >= corners->fromx && answerflg == 0)
			{
				setflg = 1;
				// arr[1 - indexflg][(3 * index) + 2] = quadrant2;
				search(mat, quadrant2, key);
				// if (answer)
				// {
				// free(quadrant2);
				// printf("%d %d\n", answer->x, answer->y);
				// return;// answer;
				// }
			}
			else
			{
				free(quadrant2);
			}
			free(middle);
			// //free(quadrant2);
		}
		free(middletemp);
		// #pragma omp taskwait
		// return;
	}
	// free(corners);
	return;
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