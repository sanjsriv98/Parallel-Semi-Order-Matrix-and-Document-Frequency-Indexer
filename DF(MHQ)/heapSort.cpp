#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// A heap has current size and array of elements


typedef struct wordcount{
    int count;
    char* wordName;
}wordcount;

typedef wordcount* wordCount;

struct MaxHeap
{
    int size;
    int maxInd;
    int level;
    wordCount array;
};
// A utility function to swap to integers
// void swap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }
void swap(wordCount a,wordCount b){
    wordCount temp = (wordCount)malloc(sizeof(wordcount));
    temp->count=a->count;
    temp->wordName=a->wordName;
    a->count=b->count;
    a->wordName=b->wordName;
    b->count=temp->count;
    b->wordName=temp->wordName;
    free(temp);
}
// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
    int largest = idx;  // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2

    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->maxInd+1 && maxHeap->array[left].count > maxHeap->array[largest].count)
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->maxInd+1 && maxHeap->array[right].count > maxHeap->array[largest].count)
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest],&maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}



// A utility function to create a max heap of given capacity
// struct MaxHeap* createAndBuildHeap(wordCount array, int size)
// {
//     int i;
//     struct MaxHeap* maxHeap =(struct MaxHeap*) malloc(sizeof(struct MaxHeap));
//     maxHeap->size = size;   // initialize size of heap
//     maxHeap->array = array; // Assign address of first element of array

//     // Start from bottommost and rightmost internal mode and heapify all
//     // internal modes in bottom up way
//     for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
//         maxHeapify(maxHeap, i);
//     return maxHeap;
// }

struct MaxHeap* insertToHeap(struct MaxHeap* maxHeap,wordcount wordNode){
    unsigned int t=1;
    if(maxHeap->maxInd==maxHeap->size-1){

        maxHeap->size+=(t<<maxHeap->level);
        // printf("%d\n",maxHeap->size );
        maxHeap->level++;
        // int n = ((int)sqrt(8*maxHeap->size+1) -1 )/2;
        // maxHeap->size= ((n+1)*(n+2))/2 ;
        if (maxHeap->size==1){
            maxHeap->array=(wordCount)malloc(maxHeap->size*sizeof(wordcount));
        }
        else{
            maxHeap->array=(wordCount)realloc(maxHeap->array,maxHeap->size*sizeof(wordcount));
        }
    }
    maxHeap->array[++maxHeap->maxInd].count=wordNode.count;
    maxHeap->array[maxHeap->maxInd].wordName=wordNode.wordName;

    struct MaxHeap* tempmaxHeap =(struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    tempmaxHeap->size = maxHeap->size;
    tempmaxHeap->maxInd=maxHeap->maxInd;
    tempmaxHeap->array = maxHeap->array;
    while (tempmaxHeap->maxInd > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&tempmaxHeap->array[0], &tempmaxHeap->array[tempmaxHeap->maxInd]);
        --tempmaxHeap->maxInd;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(tempmaxHeap, 0);
    }
    // if (tempmaxHeap->size>1)
    // maxHeapify(tempmaxHeap,0);
    return maxHeap;

}


// The main function to sort an array of given size
// void heapSort(wordCount array, int size)
// {
//     // Build a heap from the input data.
//     struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

//     // Repeat following steps while heap size is greater than 1.
//     // The last element in max heap will be the minimum element
//     while (maxHeap->size > 1)
//     {
//         // The largest item in Heap is stored at the root. Replace
//         // it with the last item of the heap followed by reducing the
//         // size of heap by 1.
//         swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
//         --maxHeap->size;  // Reduce heap size

//         // Finally, heapify the root of tree.
//         maxHeapify(maxHeap, 0);
//     }
// }

// A utility function to print a given array of given size
void printArray(struct MaxHeap* maxHeap)
{
    int i;
    for (i = 0; i < maxHeap->maxInd+1; ++i)
        printf("%d %s,\n", maxHeap->array[i].count,maxHeap->array[i].wordName);
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {40,60,10,20,50,30};
    struct MaxHeap* maxHeap =(struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->maxInd=-1;
    maxHeap->size=0;
    maxHeap->level=0;
    maxHeap->array = NULL;
    wordCount temp = (wordCount)malloc(6*sizeof(wordcount));
    int i=0;
    for(i=0;i<6;i++){
        temp[i].wordName = (char*)malloc(20*sizeof(char));
        strcpy(temp[i].wordName,"hello");
        temp[i].count=arr[i];
        maxHeap=insertToHeap(maxHeap,temp[i]);
    }
    // temp[0].count=12;
    // strcpy(temp[0].name,"hah");

    // int size = 6; 
    // sizeof(arr)/sizeof(arr[0]);

    // heapSort(arr, size);

    printf("\nSorted array is \n");
    printArray(maxHeap);
    return 0;
}