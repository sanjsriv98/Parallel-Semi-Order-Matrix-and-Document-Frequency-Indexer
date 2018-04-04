#include "_MinHeap.h"

HeapHead InitialiseHead(int k)
{
    HeapHead heap = (HeapHead)malloc(sizeof(heaphead));
    heap->size = k;
    heap->arr = (wordcount *)calloc(k, sizeof(wordcount));
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
    wordcount temp;
    if (heap->arr[a].wordName != NULL)
    {
        // heap->arr[a].triePtr->index = b;
        // temp.triePtr = heap->arr[a].triePtr;
        temp.count = heap->arr[a].count;
        temp.wordName = heap->arr[a].wordName;
    }
    else
    {
        temp.count = 0;
        if (temp.wordName != NULL)
            temp.wordName = NULL;
    }
    if (heap->arr[b].wordName != NULL)
    {
        // heap->arr[b].triePtr->index = a;
        // heap->arr[a].triePtr = heap->arr[b].triePtr;
        heap->arr[a].count = heap->arr[b].count;
        heap->arr[a].wordName = heap->arr[b].wordName;
    }
    else
    {
        // heap->arr[a].triePtr = NULL;
        heap->arr[a].count = 0;
        if (heap->arr[a].wordName != NULL)
            heap->arr[a].wordName = NULL;
    }
    if (temp.wordName != NULL)
    {
        // heap->arr[b].triePtr = temp.triePtr;
        heap->arr[b].count = temp.count;
        heap->arr[b].wordName = temp.wordName;
    }
    else
    {
        // heap->arr[b].triePtr = NULL;
        heap->arr[b].count = 0;
        if (heap->arr[b].wordName != NULL)
            heap->arr[b].wordName = NULL;
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
    //     cout << heap->arr[j].wordName << "\t" << heap->arr[j].count << "\n";
    // }
}

void fillheap(int k)
{
    heap = InitialiseHead(k);
    int i;
    wordList temp;
#pragma omp parallel for schedule(dynamic) private(temp)
    for (i = 0; i < M; i++)
    {
        temp = ht[i].head;
        // int j;
        while (temp != NULL)
        {
            if (temp->wc->count > conf)
            {
                // LOCK
                omp_set_lock(&heaplock);
                // #pragma omp critical(heap)
                if (temp->wc->count > heap->arr[0].count)
                {
                    // if (heap->arr[0].count == 0)
                    // {
                    // free(heap->arr[0].wordName);
                    // }
                    heap->arr[0].count = temp->wc->count;
                    heap->arr[0].wordName = (char *)malloc(sizeof(char) * (1 + strlen(temp->wc->wordName)));
                    strcpy(heap->arr[0].wordName, temp->wc->wordName);
                    minHeapify(heap, heap->size, 0);
                }
                // UNLOCK
                conf = heap->arr[0].count;

                omp_unset_lock(&heaplock);
            }
            temp = temp->next;
        }
    }
}

// void omp_init_lock(omp_lock_t *lock) { return; }
// void omp_set_lock(omp_lock_t *lock) { return; }
// void omp_unset_lock(omp_lock_t *lock) { return; }
