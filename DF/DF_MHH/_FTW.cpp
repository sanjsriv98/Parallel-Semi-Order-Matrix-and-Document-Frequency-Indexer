#define _XOPEN_SOURCE 500
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
    // struct dirent** chils;
    // FILE    *output_file;
    FILE *entry_file;
    char *inputfile, *rootcopy;
    // int res=1;
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
// cout <<inputfile << "\n";
#pragma omp task //shared(hashLocks) //private(inputfile,rootcopy)
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
// cout << target(rootcopy,inputfile) << "\n";
#pragma omp task shared(hashLocks) //   private(inputfile,rootcopy)
            {
                inputfile = target(rootcopy, inputfile);
                fill_ht(inputfile);
                free(inputfile); //free(rootcopy);
            }
            // #pragma omp taskwait
        }
        else
        {
            fprintf(stderr, "Error : unknown file type %s\n", in_file->d_name);
        }
        // if((res = readdir_r(FD,in_file,chils))!=0){
        //     fprintf(stderr, "Error : Failed to open directory %s\n",in_file->d_name);
        // }
    }
#pragma omp taskwait
    closedir(FD);
    //
    return;
}

// int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
// {
// printf("%s %lu\n", fpath, strlen(fpath));
// if (strlen(fpath) =)
// {
//     char* tempstr = (char*)malloc((1+strlen(fpath))*sizeof(char));
//     strcpy(tempstr,fpath);
//     #pragma omp task shared(hashLocks)
//     {
//         // fill_dict(tempstr);
//         fill_ht(tempstr);
//     }
//     // FILE *fp = fopen(fpath, "r");
//     // char *str = (char *)calloc(100, sizeof(char));
//     // fscanf(fp, "%s ", str);
//     // printf("%s\n", str);
//     // fclose(fp);
//     // }
//     return 0;
// };
