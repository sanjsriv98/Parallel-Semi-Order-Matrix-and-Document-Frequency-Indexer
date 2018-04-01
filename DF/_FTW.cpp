#define _XOPEN_SOURCE 500
#include "_FTW.h"

map<string, countindex> global_dict;
HeapHead global_heap;
int conf;

int main(int argc, char *argv[])
{
    int flags = FTW_DEPTH | FTW_PHYS;
    global_heap = InitialiseHead(10);
    if (argc == 1)
        nftw(".", fileproc, 1, flags);
    else
        nftw(argv[1], fileproc, 1, flags);
    map<string, countindex>::iterator itr;
    for (itr = global_dict.begin(); itr != global_dict.end(); ++itr)
    {
        cout << itr->first << '\t' << itr->second.count << '\t' << itr->second.index << '\n';
    }
    heapSort(global_heap);
    return 0;
}

int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    // printf("%s %lu\n", fpath, strlen(fpath));
    // if (strlen(fpath) =)
    // {
    fill_dict(fpath);
    // FILE *fp = fopen(fpath, "r");
    // char *str = (char *)calloc(100, sizeof(char));
    // fscanf(fp, "%s ", str);
    // printf("%s\n", str);
    // fclose(fp);
    // }
    return 0;
};
