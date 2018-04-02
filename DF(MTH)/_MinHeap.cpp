#include "_MinHeap.h"

// int conf;

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
    // temp.triePtr = heap->arr[a].triePtr;
    if (heap->arr[a].triePtr)
    {
        heap->arr[a].triePtr->index = b;
        temp.triePtr = heap->arr[a].triePtr;
        temp.count = heap->arr[a].count;
        temp.word = heap->arr[a].word;
        // heap->arr[a].triePtr->index = b;
        // temp.word = heap->arr[a].word;
        // heap->arr[b].word = temp.word;
    }
    else
    {
        temp.triePtr = NULL;
        temp.count = 0;
        temp.word = "";
    }
    if (heap->arr[b].triePtr)
    {
        heap->arr[b].triePtr->index = a;
        heap->arr[a].triePtr = heap->arr[b].triePtr;
        heap->arr[a].count = heap->arr[b].count;
        heap->arr[a].word = heap->arr[b].word;

        // heap->arr[b].triePtr->index = a;
        // heap->arr[a].word = heap->arr[b].word;
        // heap->arr[a].count = heap->arr[b].count;
    }
    else
    {
        heap->arr[a].triePtr = NULL;
        heap->arr[a].count = 0;
        heap->arr[a].word = "";
    }
    if (temp.triePtr)
    {
        heap->arr[b].triePtr = temp.triePtr;
        heap->arr[b].count = temp.count;
        heap->arr[b].word = temp.word;
    }
    else
    {
        heap->arr[b].triePtr = NULL;
        heap->arr[b].count = 0;
        heap->arr[b].word = "";
    }
    // temp.count = heap->arr[a].count;
    // heap->arr[b].count = temp.count;
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
    for (j = 0; j < heap->size; j++)
    {
        cout << heap->arr[j].word << "\t" << heap->arr[j].count << "\n";
    }
}

// int main()
// {
//     conf = 0;
//     HeapHead heap = InitialiseHead(10);
//     int i;
//     string s = "Hadbaudadasodnasioi";
//     for (i = 0; i < 10; i++)
//     {
//         heap->arr[0].count = 1000 % (i + 5) + 1;
//         heap->arr[0].word = s[i % 5];
//         cout << heap->arr[0].word << heap->arr[0].count << '\n';
//         minHeapify(heap, 9, 0);
//     }

//     heapSort(heap);
//     return 0;
// }