#include "_FTW.h"
hashTable ht;
HeapHead heap;
int conf;
stopWord *sht;
omp_lock_t heaplock;

omp_lock_t hashLocks[M];
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_elements> <num_workers> [<directory_root>]" << endl;
        return 0;
    }
    int i = 0;
    for (i = 0; i < M; i++)
    {
        omp_init_lock(&hashLocks[i]);
    }
    int num_elem = atoi(argv[1]);
    int nwork = atoi(argv[2]);
    makeStopWords("../stopwords");
    double start = omp_get_wtime();
    createEmptyHT();

#pragma omp parallel
    {
#pragma omp single
        {
            if (argc == 3)
            {
                filetreewalk(".");
            }
            else
            {
                filetreewalk(argv[3]);
            }
        }
    }
#pragma omp barrier

#pragma omp parallel num_threads(nwork)
#pragma omp single
    fillheap(num_elem);

    double end = omp_get_wtime();
    heapSort(heap);
    for (int j = 0; j < heap->size; j++)
    {
        printf("%s \t %d \n", heap->arr[j].wordName, heap->arr[j].count);
    }

    cout << "Time: " << (end - start) << "\n";
    return 0;
}