#define _XOPEN_SOURCE 500
#include "_FTW.h"
#include <limits.h>
hashTable ht;
stopWord *sht;
omp_lock_t hashLocks[M];

char *target(char *a, char *b)
{
    char *targetdir = (char *)malloc((2 + strlen(a) + strlen(b)) * sizeof(char));
    strcpy(targetdir, a);
    strcat(targetdir, "/");
    strcat(targetdir, b);
    free(b);
    free(a);
    return targetdir;
}

void filetreewalk(const char *root)
{
    DIR *FD;
    struct dirent *in_file;
    FILE *entry_file;
    char *inputfile, *rootcopy;
    if (NULL == (FD = opendir(root)))
    {
        fprintf(stderr, "Error : Failed to open input directory %s\n", root);
        return;
    }
    while ((in_file = readdir(FD)))
    {
        if (!strcmp(in_file->d_name, "."))
            continue;
        if (!strcmp(in_file->d_name, ".."))
            continue;
        if (in_file->d_type == DT_DIR)
        {
            inputfile = (char *)malloc((strlen(in_file->d_name) + 1) * sizeof(char));
            rootcopy = (char *)malloc((strlen(root) + 1) * sizeof(char));
            strcpy(rootcopy, root);
            strcpy(inputfile, in_file->d_name);
#pragma omp task //shared(hashLocks)
            {
                inputfile = target(rootcopy, inputfile);
                filetreewalk(inputfile);
                free(inputfile);
            }
        }
        else if (in_file->d_type == DT_REG)
        {
            inputfile = (char *)malloc((strlen(in_file->d_name) + 1) * sizeof(char));
            rootcopy = (char *)malloc((strlen(root) + 1) * sizeof(char));
            strcpy(rootcopy, root);
            strcpy(inputfile, in_file->d_name);
#pragma omp task //shared(hashLocks)
            {
                inputfile = target(rootcopy, inputfile);
                fill_ht(inputfile);
                free(inputfile);
            }
        }
        else
        {
            fprintf(stderr, "Error : unknown file type %s\n", in_file->d_name);
        }
    }
#pragma omp taskwait
    closedir(FD);
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_elements> <num_workers>" << endl;
        exit(-1);
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
