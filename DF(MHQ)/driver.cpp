#include "_Hash.h"

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
int main(int argc, char** argv){
	if(argc<2)
    {
		cerr << "Usage: "<<argv[0]<< " <num_elements> <num_workers>"<<endl;
		exit(-1);
    }

    int num_elem=atoi(argv[1]);
    int nwork=atoi(argv[2]);
	m=5000;

	ht = createEmptyHT(m);
	ht = fill_ht("driver.c",ht,m);
	ht = fillCumFreq(ht,m);

	wordCount arr = fillarray(ht,m);
	long start_t=current_time_usecs();
    // printArray(arr,ht[m-1].cf-1);
#pragma omp parallel num_threads(nwork)
#pragma omp single
    quicksort(arr,0,ht[m-1].cf-1);
    long end_t=current_time_usecs();
    printArray(arr,ht[m-1].cf-1);
    if(!isArraySorted(arr,num_elem))
    {
		fprintf(stderr,"Error: array is not sorted!!\n");
		exit(-1);
    }
    printf("hahasTime (usecs): %Ld\n",end_t-start_t);
	return 0;
}