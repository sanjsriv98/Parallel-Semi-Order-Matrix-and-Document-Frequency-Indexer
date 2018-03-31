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

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // enum tokenType type;
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
    int count;
}TrieNode;

typedef TrieNode* trieNode;

trieNode getNode(void);
void insert(trieNode root, const char *key, int type);
int search(trieNode root, const char *key);