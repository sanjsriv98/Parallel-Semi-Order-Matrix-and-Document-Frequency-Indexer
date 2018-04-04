#include "_FTW.h"
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_elements> <num_workers> [<directory_root>]" << endl;
        // return 0;
        return 0;
    }
    int num_elem = atoi(argv[1]);
    int nwork = atoi(argv[2]);
    stoproot = getNode();
    makestopwords("../stopwords");
    double start = omp_get_wtime();
    int i, j, k = num_elem;
#pragma omp parallel for private(i, j) num_threads(nwork)
    for (i = 0; i < 27; i++)
    {
        for (j = 0; j < 26; j++)
        {
            omp_init_lock(&letterlocks[i][j]);
        }
    }
    omp_init_lock(&heaplock);
    root = getNode();
    global_heap = InitialiseHead(k);

#pragma omp parallel num_threads(nwork)
#pragma omp single
    {
        if (argc == 3)
            filetreewalk(".");
        else
            filetreewalk(argv[3]);
    }
    printf("TREEWALK COMPLETE %f\n", omp_get_wtime() - start);
    string s;
    traverse2(s, root);
    heapSort(global_heap);
    double end = omp_get_wtime();

    for (j = 0; j < global_heap->size; j++)
    {
        if (global_heap->arr[j].count != 0)
            cout << global_heap->arr[j].word << "\t" << global_heap->arr[j].count << "\n";
    }
    printf("Time : %f\n", end - start);
    return 0;
}
