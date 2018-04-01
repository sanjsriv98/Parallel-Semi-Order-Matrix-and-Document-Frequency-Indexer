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


typedef struct countindex{
	int count;
	int index;
}countindex;

typedef countindex* countIndex;

map<string,countindex> global_dict;


void fill_dict(char* docName);

void fill_global(char* token);
