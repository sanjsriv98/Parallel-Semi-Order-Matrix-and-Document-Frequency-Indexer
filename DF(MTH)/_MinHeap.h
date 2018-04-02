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
#include "_Trie.h"
extern trieNode root;
extern omp_lock_t heaplock;
extern omp_lock_t letterlocks[27][26];
#include <functional>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
using namespace std;
#define CUTOFF 2000
#define MAX_NUM 99999.9

using namespace std;
typedef struct heapnode
{
    string word;
    trieNode triePtr;
    int count;
} heapnode;

typedef struct heaphead
{
    heapnode *arr;
    int size;
} heaphead;
typedef struct countindex
{
    int count;
    int index;
} countindex;
typedef heaphead *HeapHead;

extern map<string, countindex> global_dict;
extern HeapHead global_heap;
extern int conf;

HeapHead InitialiseHead(int k);

void minHeapify(HeapHead heap, int last, int t);

int minIndex(HeapHead heap, int a, int b);

void swap(HeapHead heap, int a, int b);

void heapSort(HeapHead heap);
void lock(char *token);
void unlock(char *token);

// void omp_init_lock(omp_lock_t *lock);
// void omp_set_lock(omp_lock_t *lock);
// void omp_unset_lock(omp_lock_t *lock);

#endif
