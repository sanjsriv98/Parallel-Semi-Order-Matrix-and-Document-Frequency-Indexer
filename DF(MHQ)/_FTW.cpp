#define _XOPEN_SOURCE 500
#include "_FTW.h"
#include <limits.h>
// #include <string.h> 
// #include <dirent.h>      //For PATH_MAX
// char path_buf[PATH_MAX + 1];
hashTable ht ;
stopWord* sht;
omp_lock_t hashLocks[M];

char* target(char* a,char* b){
    char *targetdir = (char*)malloc((2+strlen(a)+strlen(b))*sizeof(char));
    strcpy(targetdir,a);
    strcat(targetdir,"/");
    strcat(targetdir,b);
    free(b);
    free(a);
    return targetdir;
}


void filetreewalk(const char *root){
    DIR* FD;
    struct dirent* in_file;
    // struct dirent** chils;
    // FILE    *output_file;
    FILE    *entry_file;
    char* inputfile,*rootcopy;
    // int res=1;
    if (NULL==(FD = opendir (root)))
    {   
        fprintf(stderr, "Error : Failed to open input directory %s\n",root);
        return ;
    }
    while ((in_file=readdir(FD))) 
    {   
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
        if (in_file->d_type == DT_DIR){
            inputfile = (char*)malloc((strlen(in_file->d_name)+1)*sizeof(char));
            rootcopy=(char*)malloc((strlen(root)+1)*sizeof(char));
            strcpy(rootcopy,root);
            strcpy(inputfile,in_file->d_name);
            // cout << target(rootcopy,inputfile) << "\n";
            #pragma omp task //shared(hashLocks) //private(inputfile,rootcopy)
            {
                inputfile=target(rootcopy,inputfile);
                filetreewalk(inputfile);
                free(inputfile);//;free(rootcopy);
            }
            // #pragma omp taskwait
        }
        else if(in_file->d_type==DT_REG){
            inputfile = (char*)malloc((strlen(in_file->d_name)+1)*sizeof(char));
            rootcopy=(char*)malloc((strlen(root)+1)*sizeof(char));
            strcpy(rootcopy,root);
            strcpy(inputfile,in_file->d_name);
            // cout << target(rootcopy,inputfile) << "\n";
            #pragma omp task shared(hashLocks) //   private(inputfile,rootcopy)
            {
                inputfile = target(rootcopy,inputfile);
                fill_ht(inputfile);
                free(inputfile);//free(rootcopy);
            }
            // #pragma omp taskwait
        }else{
            fprintf(stderr, "Error : unknown file type %s\n",in_file->d_name);        
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


int main(int argc, char *argv[])
{
    if(argc<2)
    {
        cerr << "Usage: "<<argv[0]<< " <num_elements> <num_workers>"<<endl;
        exit(-1);
    }
    int i=0;
    for(i=0;i<M;i++){
        omp_init_lock(&hashLocks[i]);
    }
    int num_elem=atoi(argv[1]);
    int nwork=atoi(argv[2]);
    makeStopWords("./stopwords");
    double start=omp_get_wtime();
    createEmptyHT();
    // int flags = FTW_DEPTH | FTW_PHYS;
#pragma omp parallel 
    {
    #pragma omp single
        {
    if (argc == 3){
        // #pragma omp task
        // nftw(".", fileproc, 1, flags);
        filetreewalk(".");
    }
    else{
        // #pragma omp task
        // nftw(argv[3], fileproc, 1, flags);
        filetreewalk(argv[3]);
    }
    // #pragma omp taskwait
    }
    
    }
    // printHT();
    #pragma omp barrier
    fillCumFreq();
    int size =ht[M-1].cf-1;
    // printHT();
    // for(int i=0;i<m;i++){
    //     cout << "dfsdf"<<ht[i].size << "\n";
    // }
    // printHT(ht,m);
    // #pragma omp parallel single num_threads(nwork)
    wordCount arr = fillarray();
#pragma omp parallel num_threads(nwork)
#pragma omp single
    quicksort(arr,0,size);
    double end=omp_get_wtime();    
    printArray(arr,num_elem);
    // if(!isArraySorted(arr,num_elem))
    // {
    //     fprintf(stderr,"Error: array is not sorted!!\n");
    //     exit(-1);
    // }
    // #pragma omp barrier

    // map<string, countindex>::iterator itr;
    // for (itr = global_dict.begin(); itr != global_dict.end(); ++itr)
    // {
    //     cout << itr->first << '\t' << itr->second.count << '\t' << itr->second.index << '\n';
    // }
    // heapSort(global_heap);
    cout << "Time: " << (end-start) << "\n";
    return 0;
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
