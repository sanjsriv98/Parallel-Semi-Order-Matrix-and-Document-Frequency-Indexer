#include "_FTW.h"

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
