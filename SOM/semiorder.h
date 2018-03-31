#ifndef SO_H
#define SO_H

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
SubMatrix makecopy(SubMatrix m);

#endif