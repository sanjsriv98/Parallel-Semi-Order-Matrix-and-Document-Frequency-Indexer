// SAMIP JASANI 2015A7PS0127P
// SANJAY 2015A7PS0102P

// C implementation of search and insert operations
// on Trie
#include "_Trie.h"

// Alphabet size (# of symbols)
// #define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case

// trie node

// Returns new trie node (initialized to NULLs)
trieNode getNode(void)
{
    trieNode pNode = NULL;

    pNode = (trieNode)malloc(sizeof(TrieNode));

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
void insert(trieNode root, const char *key)
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
    //LOCK letter
    pCrawl->count++;
    if (pCrawl->isEndOfWord)
    {
        // checkindex etc;
        if (pCrawl->index == -1)
        {
            if (pCrawl->count > conf)
            {
                // LOCK
                if (pCrawl->count > global_heap->arr[0].count)
                {
                    if (global_heap->arr[0].triePtr)
                        global_heap->arr[0].triePtr->index = -1;
                    pCrawl->index = 0;
                    global_heap->arr[0].count = pCrawl->count;
                    global_heap->arr[0].word = key;
                    global_heap->arr[0].triePtr = pCrawl;
                    minHeapify(global_heap, global_heap->size - 1, 0);
                }
                // UNLOCK
                conf = global_heap->arr[0].count;
            }
        }
        else
        {
            // LOCK
            int index = pCrawl->index;
            global_heap->arr[index].count++;
            minHeapify(global_heap, global_heap->size - 1, index);
            // UNLOCK
            if (index == 0)
            {
                conf = global_heap->arr[0].count;
            }
        }
    }
    else
    {
        pCrawl->isEndOfWord = true;
        pCrawl->index = -1;
        if (pCrawl->count > conf)
        {
            // LOCK HEAP
            if (pCrawl->count > global_heap->arr[0].count)
            {
                if (global_heap->arr[0].triePtr)
                    global_heap->arr[0].triePtr->index = -1;
                pCrawl->index = 0;
                global_heap->arr[0].count = pCrawl->count;
                global_heap->arr[0].word = key;
                global_heap->arr[0].triePtr = pCrawl;
                minHeapify(global_heap, global_heap->size - 1, 0);
            }
            // UNLOCK
            conf = global_heap->arr[0].count;
        }
    }
    //UNLOCK Letter
    return;
}

// Returns true if key presents in trie, else false
// int search(trieNode root, const char *key)
// {
//     int level;
//     int length = strlen(key);
//     int index;
//     trieNode pCrawl = root;

//     for (level = 0; level < length; level++)
//     {
//         index = CHAR_TO_INDEX(key[level]);

//         if (!pCrawl->children[index])
//             return 0;

//         pCrawl = pCrawl->children[index];
//     }

//     if (pCrawl != NULL && pCrawl->isEndOfWord)
//     {
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }
