#define _XOPEN_SOURCE 500
#include "_FTW.h"

HeapHead global_heap;
trieNode root;
int conf;
omp_lock_t heaplock;
omp_lock_t letterlocks[27][26];
inline long current_time_usecs() __attribute__((always_inline));
inline long current_time_usecs()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec) * 1000000L + t.tv_usec;
}

inline long current_time_nsecs() __attribute__((always_inline));
inline long current_time_nsecs()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (t.tv_sec) * 1000000000L + t.tv_nsec;
}

int main(int argc, char *argv[])
{
    long start_t = current_time_usecs();

    int i, j, k = 10;
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
#pragma omp parallel
#pragma omp single
    {
        if (argc == 1)
            nftw(".", fileproc, 1, flags);
        else
            nftw(argv[1], fileproc, 1, flags);
    }
    long end_t = current_time_usecs();

    heapSort(global_heap);
    printf("Time (usecs): %ld\nTime (msecs): %ld\n", end_t - start_t, (end_t - start_t) / 1000);
    // std::string s;
    // traverse(s, root);
    return 0;
}

int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    char *temp = (char *)malloc(sizeof(char) * (1 + strlen(fpath)));
    strcpy(temp, fpath);
    // #pragma omp task
    fill_dict(temp);

    return 0;
};
