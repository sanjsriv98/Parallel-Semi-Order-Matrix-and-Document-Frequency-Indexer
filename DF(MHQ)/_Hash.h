// SAMIP JASANI 2015A7PS0127P
// SANJAY 2015A7PS0102P
#define ALPHABET_SIZE (26)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <map>
#include <iterator>
#include <string>
#include <omp.h>
#include <iostream>
#include <functional>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
using namespace std;
#define CUTOFF 2000
#define MAX_NUM 99999.9


typedef struct wordcount{
    int count;
    char* wordName;
}wordcount;

typedef wordcount* wordCount;

typedef struct wordlist
{
	wordCount wc;
	struct wordlist* next;
}wordlist;

typedef wordlist* wordList;

typedef struct hashtable{
	wordList head;
	int size;
	int cf; 
}hashtable;

typedef hashtable* hashTable;

extern hashTable ht ;
extern int m;

void fill_ht(char* docName);
char* isalphabet(char* temp);
int hash(char *str,int m);
void createEmptyHT();
void insertWord(char* str);
void printHT();
void fillCumFreq();
wordCount fillarray();
int acompare(wordcount lhs, wordcount rhs);
int divide(wordCount a, int left, int right);
void seq(wordCount a, int left, int right);
void quicksort(wordCount a, int left, int right);
void printArray(wordCount a, int n);
bool isArraySorted(wordCount a, int n);
int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

