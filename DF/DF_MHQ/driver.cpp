#include "_FTW.h"

hashTable ht;
stopWord *sht;
omp_lock_t hashLocks[M];

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_elements> <num_workers> [<directory_root>]" << endl;
        return 0;
        ;
    }
    int num_elem = atoi(argv[1]);
    int nwork = atoi(argv[2]);
    double start = omp_get_wtime();
    makeStopWords("../stopwords");
    int i = 0;
    for (i = 0; i < M; i++)
    {
        omp_init_lock(&hashLocks[i]);
    }

    createEmptyHT();
#pragma omp parallel num_threads(nwork)
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
    printf("TREEWALK COMPLETE %f\n", omp_get_wtime() - start);
    fillCumFreq();
    // printHT();
    int size = ht[M - 1].cf - 1;
    wordCount arr = fillarray();
#pragma omp parallel num_threads(nwork)
#pragma omp single
    quicksort(arr, 0, size);
    double end = omp_get_wtime();
    if ((1 + size) < num_elem)
        printArray(arr, size + 1);
    else
        printArray(arr, num_elem);
    cout << "Time: " << (end - start) << "\n";
    return 0;
}
