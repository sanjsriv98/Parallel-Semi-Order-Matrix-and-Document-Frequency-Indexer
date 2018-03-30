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

Pos search(int **mat, SubMatrix corners, int key);
SubMatrix makecopy(SubMatrix m);

#endif