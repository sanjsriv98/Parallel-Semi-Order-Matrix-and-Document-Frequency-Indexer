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
#endif
