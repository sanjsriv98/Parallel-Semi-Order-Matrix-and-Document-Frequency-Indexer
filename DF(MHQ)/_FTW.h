// #define _DICT_H 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "_Hash.h"

int fileproc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

extern hashTable ht ;
extern int m;