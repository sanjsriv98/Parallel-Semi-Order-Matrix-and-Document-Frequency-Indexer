#define _DICT_H 500
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
// #include <math.h>
#include <string.h>
#include <ctype.h>
// #include <sys/types.h>
// #include <dirent.h>
// #include <unistd.h>
// #include <errno.h>
// #include <stdbool.h>
using namespace std;

typedef struct countindex
{
	int count;
	int index;
} countindex;

typedef countindex *countIndex;
// #ifndef _DICT_H
extern map<string, countindex> global_dict;
// map<string, countindex> global_dict;
// #endif

void fill_dict(const char *docName);

void fill_global(char *token);
