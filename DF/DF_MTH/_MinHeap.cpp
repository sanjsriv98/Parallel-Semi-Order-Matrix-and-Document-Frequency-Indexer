#include "_MinHeap.h"

HeapHead InitialiseHead(int k)
{
    HeapHead heap = (HeapHead)malloc(sizeof(heaphead));
    heap->size = k;
    heap->arr = (heapnode *)calloc(k, sizeof(heapnode));
    conf = 0;
}

void minHeapify(HeapHead heap, int last, int t)
{
    int L = 2 * t + 1;
    int R = 2 * t + 2;
    int mlx;
    if (L <= last)
    {
        mlx = minIndex(heap, L, t);
        if (R <= last)
        {
            mlx = minIndex(heap, mlx, R);
        }
    }
    else
    {
        mlx = t;
    }
    if (mlx != t)
    {
        swap(heap, mlx, t);
        minHeapify(heap, last, mlx);
    }
}

int minIndex(HeapHead heap, int a, int b)
{
    return (heap->arr[a].count < heap->arr[b].count) ? a : b;
}

void swap(HeapHead heap, int a, int b)
{
    heapnode temp;
    if (heap->arr[a].triePtr)
    {
        // heap->arr[a].triePtr->index = b;
        temp.triePtr = heap->arr[a].triePtr;
        temp.count = heap->arr[a].count;
        temp.word = heap->arr[a].word;//(char*)malloc(sizeof(char)*(1+strlen(heap->arr[a].word)));
        // strcpy(temp.word ,heap->arr[a].word);
    }
    else
    {
        temp.triePtr = NULL;
        temp.count = 0;
        temp.word=NULL;

        // strcpy(temp.word,"");
        // if (temp.word)
        //     free(temp.word);
    }
    if (heap->arr[b].triePtr)
    {
        // heap->arr[b].triePtr->index = a;
        heap->arr[a].triePtr = heap->arr[b].triePtr;
        heap->arr[a].count = heap->arr[b].count;
        // if(!heap->arr[a].word)
            heap->arr[a].word = heap->arr[b].word;//(char*)malloc((1+strlen(heap->arr[b].word))*sizeof(char));
        // strcpy(heap->arr[a].word, heap->arr[b].word);
    }
    else
    {
        heap->arr[a].triePtr = NULL;
        heap->arr[a].count = 0;
        heap->arr[a].word=NULL;
        // strcpy(heap->arr[a].word,"");
        // if (heap->arr[a].word)
        //     free(heap->arr[a].word);
    }
    if (temp.triePtr)
    {
        heap->arr[b].triePtr = temp.triePtr;
        heap->arr[b].count = temp.count;
        //  if(!heap->arr[b].word)
            // heap->arr[b].word = (char*)malloc((1+strlen(temp.word))*sizeof(char));
        // strcpy(heap->arr[b].word, temp.word);
        heap->arr[b].word = temp.word;
    }
    else
    {
        heap->arr[b].triePtr = NULL;
        heap->arr[b].count = 0;
        // strcpy(heap->arr[b].word,"");
        heap->arr[b].word=NULL;
        //     free(heap->arr[b].word);
    }
}

void heapSort(HeapHead heap)
{
    int size = heap->size;
    int j = size - 1;
    for (; j > 0; j--)
    {
        swap(heap, 0, j);
        size--;
        minHeapify(heap, size - 1, 0);
    }
    // for (j = 0; j < heap->size; j++)
    // {
    //     cout << heap->arr[j].word << "\t" << heap->arr[j].count << "\n";
    // }
}

void lock(char *token)
{
    if (strlen(token) == 0)
    {
        return;
    }
    else if (strlen(token) == 1)
    {
        omp_set_lock(&letterlocks[0][CHAR_TO_INDEX(token[0])]);
    }
    else
    {
        omp_set_lock(&letterlocks[1 + CHAR_TO_INDEX(token[0])][CHAR_TO_INDEX(token[1])]);
    }
    return;
}

void unlock(char *token)
{
    if (strlen(token) == 0)
    {
        return;
    }
    else if (strlen(token) == 1)
    {
        omp_unset_lock(&letterlocks[0][CHAR_TO_INDEX(token[0])]);
    }
    else
    {
        omp_unset_lock(&letterlocks[1 + CHAR_TO_INDEX(token[0])][CHAR_TO_INDEX(token[1])]);
    }
    return;
}
