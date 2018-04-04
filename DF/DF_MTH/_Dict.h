#define _DICT_H 500
#include "_Trie.h"
// #include <sys/types.h>
// #include <dirent.h>
// #include <unistd.h>
// #include <errno.h>
// #include <stdbool.h>

extern HeapHead global_heap;
extern int conf;
extern trieNode root;

typedef countindex *countIndex;
// #ifndef _DICT_H
extern map<string, countindex> global_dict;
// map<string, countindex> global_dict;
// #endif

void fill_dict(char *docName);

void fill_global(char *token);
