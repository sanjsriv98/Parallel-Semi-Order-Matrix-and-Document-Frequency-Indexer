// #include "_Dict.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
// #include <math.h>
#include <string.h>
#include <ctype.h>
using namespace std;

typedef struct heapnode
{
    string word;
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