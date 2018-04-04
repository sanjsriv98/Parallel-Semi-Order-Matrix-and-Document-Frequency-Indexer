// #define _XOPEN_SOURCE 500
// #include <stdio.h>
// #include <iostream>
#include "_FTW.h"

HeapHead global_heap;
trieNode root;
trieNode stoproot;
int conf;
omp_lock_t heaplock;
omp_lock_t letterlocks[27][26];

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