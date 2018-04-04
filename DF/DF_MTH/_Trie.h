// SAMIP JASANI 2015A7PS0127P
// SANJAY 2015A7PS0102P
#ifndef _TRIE_H
#define _TRIE_H
#define ALPHABET_SIZE (26)
// #include <stdio.h>
// #include <stdlib.h>
#include <math.h>
// #include <string.h>
// #include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // enum tokenType type;
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
    int index;
    int count;
} TrieNode;

typedef TrieNode *trieNode;
extern trieNode root;

#include "_MinHeap.h"
char *isalphabet(char *temp);
trieNode getNode(void);
void insert(trieNode root, char *key);
void traverse(char *prefix, trieNode node);
void traverse2(std::string &prefix, trieNode node);
int search(trieNode root, const char *key);
void makestopwords(const char *docName);

#endif