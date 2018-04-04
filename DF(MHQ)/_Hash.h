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
#define M 50000

typedef struct wordcount
{
	int count;
	char *wordName;
} wordcount;

typedef wordcount *wordCount;

typedef struct stopword
{
	char *key;
	struct stopword *next;
} stopword;

typedef stopword *stopWord;

typedef struct wordlist
{
	wordCount wc;
	struct wordlist *next;
} wordlist;

typedef wordlist *wordList;

typedef struct hashtable
{
	wordList head;
	int size;
	int cf;
} hashtable;

typedef hashtable *hashTable;

extern hashTable ht;
extern omp_lock_t hashLocks[M];
extern stopWord *sht;

void fill_ht(char *docName);
char *isalphabet(char *temp);
int myhash(char *str);
void createEmptyHT();
void insertWord(char *str, int h);
void printHT();
void fillCumFreq();
wordCount fillarray();
void makeStopWords(const char *fname);
int checkStopWord(char *key, int hash);
