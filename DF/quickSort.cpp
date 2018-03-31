#include <iostream>
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
using namespace std;
#define CUTOFF 2000
#define MAX_NUM 99999.9


typedef struct wordcount{
    int count;
    char* wordName;
}wordcount;

typedef wordcount* wordCount;
/*
 * The divide chooses as pivot the middle element and redistributes the elements
 */
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
int acompare(wordcount lhs, wordcount rhs) { return lhs.count > rhs.count; }   
int divide(wordCount a, int left, int right)
{
    int pivot=a[(left+right)/2].count;
    int i = left-1, j = right+1;
    wordcount tmp;

    while(true)
    {
		do{
			i++;
		}while(a[i].count>pivot);
		do{
			j--;
		}while(a[j].count<pivot);

		if(i>=j)
		   break;

		//swap
		tmp.count=a[i].count;
        tmp.wordName=a[i].wordName;
		a[i].count=a[j].count;
        a[i].wordName=a[j].wordName;
		a[j].count=tmp.count;
        a[j].wordName=tmp.wordName;
    }

    //j is the pivot
    return j;
}



/*
 * Base case: we resort on std::sort
 */
void seq(wordCount a, int left, int right)
{
    std::sort(&(a[left]),&(a[right+1]),acompare);

}


//sort the array from index left to index right (included)
void quicksort(wordCount a, int left, int right)
{
    if(!(right-left<=CUTOFF))
    {
	int p=divide(a,left,right);
#pragma omp task
	quicksort(a,left,p);
#pragma omp task
	quicksort(a,p+1,right);
#pragma omp taskwait
    }
    else
	seq(a,left,right);
}
int *generateRandomArray(int n)
{
    srand ((time(0)));
    int *numbers=new int[n];
    wordCount num = (wordCount)malloc(6*sizeof(wordcount));
    for(int i=0;i<n;i++){
        numbers[i]=(int) (rand()) / ((RAND_MAX/MAX_NUM));

    }
    return numbers;
}
void printArray(wordCount a, int n)
{
    for(int i=0;i<n;i++)
        cout << a[i].count << "   "<< a[i].wordName <<endl;
}

//simple check
bool isArraySorted(wordCount a, int n)
{
    for(int i=1;i<n;i++)
        if(a[i].count>a[i-1].count)
            return false;
    return true;
}
// int main(int argc, char *argv[])
// {
//     if(argc<2)
//     {
// 		cerr << "Usage: "<<argv[0]<< " <num_elements> <num_workers>"<<endl;
// 		exit(-1);
//     }

//     int num_elem=atoi(argv[1]);
//     int nwork=atoi(argv[2]);
//     wordCount num = (wordCount)malloc(num_elem*sizeof(wordcount));
//     int *numbers=generateRandomArray(num_elem);
//     for(int i=0;i<num_elem;i++){
//         num[i].wordName=(char*)malloc(10*sizeof(char));
//         strcpy(num[i].wordName,"hello");
//         num[i].count=numbers[i];
//     }

//     printArray(num,num_elem);
//     //build the operand
//     //Operand *op=new Operand();
//     printf("\n\n");
//     long start_t=current_time_usecs();

//     //compute
// #pragma omp parallel num_threads(nwork)
// #pragma omp single
//     quicksort(num,0,num_elem-1);

//     long end_t=current_time_usecs();
//     printArray(num,num_elem);
//     if(!isArraySorted(num,num_elem))
//     {
// 		fprintf(stderr,"Error: array is not sorted!!\n");
// 		exit(-1);
//     }
//     printf("Time (usecs): %Ld\n",end_t-start_t);

//     return 0;
// }