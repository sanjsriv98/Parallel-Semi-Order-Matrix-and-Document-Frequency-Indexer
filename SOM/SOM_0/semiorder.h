#ifndef SO_H
#define SO_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <functional>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
using namespace std;
typedef struct submatrix
{
    int fromx;
    int tox;
    int fromy;
    int toy;
} submatrix;

typedef submatrix *SubMatrix;

typedef struct pos
{
    int x;
    int y;
} pos;
typedef pos *Pos;

void search(int **mat, SubMatrix **arr, int key, int index);
// void search(int **mat, SubMatrix arr, int key);

SubMatrix makecopy(SubMatrix m);

#endif