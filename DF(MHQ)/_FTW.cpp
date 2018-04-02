#define _XOPEN_SOURCE 500
#include "_FTW.h"
hashTable ht ;
int m;
inline long current_time_usecs() __attribute__((always_inline));
inline long current_time_usecs(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec)*1000000L + t.tv_usec;

}

inline long current_time_nsecs() __attribute__((always_inline));
inline long current_time_nsecs(){
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (t.tv_sec)*1000000000L + t.tv_nsec;
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        cerr << "Usage: "<<argv[0]<< " <num_elements> <num_workers>"<<endl;
        exit(-1);
    }

    int num_elem=atoi(argv[1]);
    int nwork=atoi(argv[2]);
    m=5000;
    long start_t=current_time_usecs();

    createEmptyHT();
    int flags = FTW_DEPTH | FTW_PHYS;
#pragma omp parallel 
    {
    #pragma omp single
        {
    if (argc == 3){
        // #pragma omp task
        nftw(".", fileproc, 1, flags);
    }
    else{
        // #pragma omp task
        nftw(argv[3], fileproc, 1, flags);
    }
    // #pragma omp taskwait
    }
    
    }
    // printHT();
    fillCumFreq();
    // printHT();
    // for(int i=0;i<m;i++){
    //     cout << "dfsdf"<<ht[i].size << "\n";
    // }
    // printHT(ht,m);
    wordCount arr = fillarray();
#pragma omp parallel num_threads(nwork)
#pragma omp single
    quicksort(arr,0,ht[m-1].cf-1);
    long end_t=current_time_usecs();
    printArray(arr,num_elem);
    if(!isArraySorted(arr,num_elem))
    {
        fprintf(stderr,"Error: array is not sorted!!\n");
        exit(-1);
    }
    // #pragma omp barrier

    // map<string, countindex>::iterator itr;
    // for (itr = global_dict.begin(); itr != global_dict.end(); ++itr)
    // {
    //     cout << itr->first << '\t' << itr->second.count << '\t' << itr->second.index << '\n';
    // }
    // heapSort(global_heap);
    printf("Time (usecs): %Ld\n",end_t-start_t);
    return 0;
}

int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    // printf("%s %lu\n", fpath, strlen(fpath));
    // if (strlen(fpath) =)
    // {
    char* tempstr = (char*)malloc((1+strlen(fpath))*sizeof(char));
    strcpy(tempstr,fpath);
    // #pragma omp task
    { 
        // fill_dict(tempstr);
        fill_ht(tempstr);
    }
    // FILE *fp = fopen(fpath, "r");
    // char *str = (char *)calloc(100, sizeof(char));
    // fscanf(fp, "%s ", str);
    // printf("%s\n", str);
    // fclose(fp);
    // }
    return 0;
};
