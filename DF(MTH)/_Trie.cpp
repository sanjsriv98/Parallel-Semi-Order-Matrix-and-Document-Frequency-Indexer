// SAMIP JASANI 2015A7PS0127P
// SANJAY 2015A7PS0102P

#include "_Trie.h"

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
void insert(trieNode root, char *key)
{
    int flag = 0;
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
    lock(key);
    pCrawl->count++;
    if (pCrawl->isEndOfWord)
    {
        // checkindex etc;
        if (pCrawl->index == -1)
        {
            if (pCrawl->count > conf)
            {
                // LOCK
                omp_set_lock(&heaplock);
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
                else
                {
                    flag = 1;
                }
                // UNLOCK
                omp_unset_lock(&heaplock);
                conf = global_heap->arr[0].count;
            }
            else
            {
                flag = 1;
            }
        }
        else
        {
            // LOCK
            omp_set_lock(&heaplock);
            int index = pCrawl->index;
            global_heap->arr[index].count++;
            minHeapify(global_heap, global_heap->size - 1, index);
            // UNLOCK
            omp_unset_lock(&heaplock);
            if (index == 0)
            {
                conf = global_heap->arr[0].count;
            }
            flag = 1;
        }
    }
    else
    {
        pCrawl->isEndOfWord = true;
        pCrawl->index = -1;
        if (pCrawl->count > conf)
        {
            // LOCK HEAP
            omp_set_lock(&heaplock);
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
            else
            {
                flag = 1;
            }
            // UNLOCK
            omp_unset_lock(&heaplock);
            conf = global_heap->arr[0].count;
        }
        else
        {
            flag = 1;
        }
    }
    //UNLOCK Letter
    unlock(key);
    if (flag == 1)
    {
        free(key);
    }
    return;
}

void traverse(std::string &prefix, trieNode node)
{
    if (node->isEndOfWord)
        cout << prefix << '\n';

    for (char index = 0; index < ALPHABET_SIZE; ++index)
    {
        char next = 'a' + index;
        trieNode pChild = node->children[index];
        if (pChild)
        {
            prefix.push_back(next);
            traverse(prefix, pChild);
            prefix.pop_back();
        }
    }
}