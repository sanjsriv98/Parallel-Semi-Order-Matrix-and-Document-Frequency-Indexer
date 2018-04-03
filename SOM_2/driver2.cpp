
#include "semiorder.h"

int answerflg;

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
	int itr = x*10;
	int key[itr];//[itr]; // = mat[99][99];
	scanf("%d", &key[0]);
	srand(time(0));	
	// key =(rand()) % (x*y);
	int upperbound = x * y;
	for (i = 0; i < itr; i++)
	{
		key[i] = (rand()) % (upperbound);
	}
	// key[0]=799;
	SubMatrix corners;
	int size = 1;
	start = omp_get_wtime();
	for (i = 0; i < itr; i++)
	{
		corners = (SubMatrix)calloc(1, sizeof(submatrix));
		corners->tox = x - 1;
		corners->toy = y - 1;
#pragma omp parallel
#pragma omp single
		search(mat, corners, key[i]);
		if (answerflg == 1)
		{
			// printf("X-Index: %d\t Y-Index: %d\n", answer->x, answer->y);
			// int answerkey = mat[answer->x][answer->y];
			// printf(" %d %d\n", key[i], answerkey);
			free(answer);
			answerflg = 0;
		}
		else
		{
			printf("FAILED key %d\n",key[i]);
		}
		// free(corners);
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

int binarySearch(int* arr,int lo,int hi,int x){
	int i,mid=(lo+hi)/2;
	while(lo<=mid&&lo<hi){
		if(arr[mid]==x){
			return mid;
		}
		else if(arr[mid]>x){
			hi=mid;
		}
		else{
			lo=mid+1;
		}
		mid = (lo+hi)/2;
	}
	return lo;
}

void search(int **mat, SubMatrix corners, int key)
{
	// if(corners->fromx <= 94 && corners->tox >= 94 && corners->fromy<=4 && corners->toy>=4){
	// 	printf("DEBUGING\n%d %d \t %d %d\n",corners->fromx,corners->tox,corners->fromy,corners->toy);
	// }
	Pos middle = (Pos)malloc(sizeof(pos));
	middle->x = (corners->fromx + corners->tox) / 2;
	middle->y = binarySearch(mat[middle->x],corners->fromy,corners->toy,key);
	if(mat[middle->x][middle->y] == key){
		answerflg = 1;
		answer = middle;
		double answertime = omp_get_wtime();
		// printf("answertime : %f\n", answertime - start);
		// printf("%d %d\n", middle->x, middle->y);
		free(corners);
		return;
	}else if (((corners->tox - corners->fromx) <4) || ((corners->toy - corners->fromy)<4)){
		if(key<mat[corners->fromx][corners->fromy]||key>mat[corners->tox][corners->toy])free(middle);
		else 
		{
			search2(mat,corners,key);
			free(middle);
			free(corners);
		}
	}
	else if(middle->y == corners->fromy&&key<mat[middle->x][middle->y]){
		SubMatrix quadrant1 = makecopy(corners);
		free(corners);
		quadrant1->tox = middle->x;
		#pragma omp task
		{
			if(!answerflg){
				search(mat,quadrant1,key);
			}
			else{
				free(quadrant1);
			}
		}
		free(middle);
	}
	else if(middle->y == corners->toy&&key>mat[middle->x][middle->y]){
		SubMatrix quadrant2 = makecopy(corners);
		quadrant2->fromx = middle->x;
		free(corners);
		#pragma omp task
		{
			if(!answerflg){
				search(mat,quadrant2,key);
			}
			else{
				free(quadrant2);
			}
		}
		free(middle);
	}
	else{
		SubMatrix quadrant3 = makecopy(corners);
		quadrant3->fromx=middle->x+1;
		quadrant3->toy = middle->y;
		#pragma omp task
		{
			if(!answerflg){
				search(mat,quadrant3,key);
			}
			else{
				free(quadrant3);
			}
		}
		SubMatrix quadrant4 = makecopy(corners);
		quadrant4->tox = middle->x;
		quadrant4->fromy = middle->y;
		free(corners);
		#pragma omp task
		{
			if(!answerflg){
				search(mat,quadrant4,key);
			}
			else{
				free(quadrant4);
			}
		}
		free(middle);
	}
	return;
	// printf("%d %d\n", middle->x, middle->y);
//==========================-------------------------------------------
	
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

void search2(int **mat, SubMatrix corners, int key)
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