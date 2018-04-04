#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <iostream>
#include "_FTW.h"

HeapHead global_heap;
trieNode root;
trieNode stoproot;
int conf;
omp_lock_t heaplock;
omp_lock_t letterlocks[27][26];

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_elements> <num_workers>" << endl;
        // return 0;
        exit(-1);
    }
    int num_elem = atoi(argv[1]);
    int nwork = atoi(argv[2]);
    stoproot = getNode();
    makestopwords("./stopwords");
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
    int flags = FTW_DEPTH | FTW_PHYS;
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
        cout << global_heap->arr[j].word << "\t" << global_heap->arr[j].count << "\n";
    }
    printf("Time : %f\n", end - start);
    return 0;
}

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
#pragma omp task
            {
                inputfile = target(rootcopy, inputfile);
                filetreewalk(inputfile);
                free(inputfile); //;free(rootcopy);
            }
            // #pragma omp taskwait
        }
        else if (in_file->d_type == DT_REG)
        {
            inputfile = (char *)malloc((strlen(in_file->d_name) + 1) * sizeof(char));
            rootcopy = (char *)malloc((strlen(root) + 1) * sizeof(char));
            strcpy(rootcopy, root);
            strcpy(inputfile, in_file->d_name);
#pragma omp task
            {
                inputfile = target(rootcopy, inputfile);
                fill_dict(inputfile);
            }
            // #pragma omp taskwait
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