// #include "_Dict.h"
#ifndef _MINHEAP_H
#define _MINHEAP_H
#include <iostream>
#include <string>
#include <map>
#include <omp.h>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
// #include <math.h>
#include <string.h>
#include <ctype.h>

#include <functional>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
using namespace std;
#define CUTOFF 2000
#define MAX_NUM 99999.9
#include "_Hash.h"
using namespace std;

typedef struct heaphead
{
    wordcount *arr;
    int size;
} heaphead;

typedef heaphead *HeapHead;

HeapHead InitialiseHead(int k);

void minHeapify(HeapHead heap, int last, int t);

int minIndex(HeapHead heap, int a, int b);

void swap(HeapHead heap, int a, int b);

void heapSort(HeapHead heap);
void lock(char *token);
void unlock(char *token);

extern HeapHead heap;
extern int conf;
extern omp_lock_t heaplock;
// void omp_init_lock(omp_lock_t *lock);
// void omp_set_lock(omp_lock_t *lock);
// void omp_unset_lock(omp_lock_t *lock);
void fillheap(int k);
#endif
