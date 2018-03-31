// SAMIP JASANI 2015A7PS0127P
// SANJAY 2015A7PS0102P

// C implementation of search and insert operations
// on Trie
#include "_Trie.h"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node

// Returns new trie node (initialized to NULLs)
trieNode getNode(void)
{
    trieNode pNode = NULL;

    pNode = (trieNode )malloc(sizeof(TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;
        pNode->count = 0;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
int insert(trieNode root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    trieNode pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->count++;
    pCrawl->isEndOfWord = true;
    return pCrawl->count;

}

// Returns true if key presents in trie, else false
int search(trieNode root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    trieNode pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


