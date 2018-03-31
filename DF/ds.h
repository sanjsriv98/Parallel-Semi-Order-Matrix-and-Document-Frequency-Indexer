#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct docnode
{
	char* name;
	struct docnode* next;
}docnode;

typedef docnode* docNode;

typedef struct wordnode{
	char* wordName;
	int freq;
	docNode **headDoc;
}