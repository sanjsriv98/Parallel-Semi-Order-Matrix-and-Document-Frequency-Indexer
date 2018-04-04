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
char *isalphabet(char *temp)
{
    char *p;
    for (p = temp; *p; ++p)
        if (!isalpha(*p))
            *p = ' ';
        else
        {
            *p = tolower(*p);
        }
    return temp;
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
#pragma omp critical(getnode)
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    //LOCK letter
    pCrawl->isEndOfWord = true;
// lock(key);
#pragma omp atomic
    pCrawl->count++;
    free(key);
    return;
}

void traverse(char *prefix, trieNode node)
{
    char *s = prefix;
    trieNode pCrawl = node;
    if (pCrawl->isEndOfWord && pCrawl->count > conf && strcmp(s, "") != 0)
    {
        {
            // LOCK
            omp_set_lock(&heaplock);
            if (pCrawl->count > global_heap->arr[0].count)
            {
                global_heap->arr[0].count = pCrawl->count;
                cout << s << '\n';
                global_heap->arr[0].word = s;
                global_heap->arr[0].triePtr = pCrawl;
                minHeapify(global_heap, global_heap->size - 1, 0);
            }
            // UNLOCK
            omp_unset_lock(&heaplock);
            conf = global_heap->arr[0].count;
        }
    }
    char index;
    int len = strlen(prefix);

    // #pragma omp for private(index, pCrawl, s)
    for (index = 0; index < ALPHABET_SIZE; ++index)
    {
        char next = 'a' + index;
        trieNode pChild = pCrawl->children[index];
        if (pChild)
        {
            // s.push_back(next);
            char *temp = (char *)malloc(sizeof(char) * (2 + len));
            strcpy(temp, prefix);
            temp[len - 2] = next;
            temp[len - 1] = '\0';
            traverse(temp, pChild);
            // s.pop_back();
        }
    }
    // #pragma omp taskwait
    // free(prefix);
}

void traverse2(std::string &prefix, trieNode node)
{
    // if (node->isEndOfWord)
    //     cout << prefix << " " << node->count << "\n";
    if (node->count > conf)
    {
        // LOCK
        omp_set_lock(&heaplock);
        if (node->count > global_heap->arr[0].count)
        {
            // if (global_heap->arr[0].triePtr)
            // global_heap->arr[0].triePtr->index = -1;
            // pCrawl->index = 0;
            global_heap->arr[0].count = node->count;
            global_heap->arr[0].word = prefix;
            global_heap->arr[0].triePtr = node;
            minHeapify(global_heap, global_heap->size - 1, 0);
            // }
            // else
            // {
            // flag = 1;
        }
        // UNLOCK
        omp_unset_lock(&heaplock);
        conf = global_heap->arr[0].count;
    }
#pragma omp for
    for (char index = 0; index < 26; ++index)
    {
        char next = 'a' + index;
        trieNode pChild = node->children[index];
        if (pChild)
        {
            string temp = prefix;
            temp.push_back(next);
            traverse2(temp, pChild);
            // prefix.pop_back();
        }
#pragma omp cancel for
    }
    free(node);
}
int search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

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

void makestopwords(const char *docName)
{
    // cout << docName << "\n";
    FILE *entry_file = fopen(docName, "r");
    if (entry_file == NULL)
    {
        // cout << docName << "\n";
        fprintf(stderr, "Error : Failed to open entry file\n");
        return;
    }
    char *line = NULL, *saveptr1, *str1, *token, *p;
    size_t len = 0;
    ssize_t read;
    int j, k, temp;
    while ((read = getline(&line, &len, entry_file)) != -1)
    {
        line = isalphabet(line);
        for (j = 1, str1 = line;; j++, str1 = NULL)
        {
            token = strtok_r(str1, "  \n\t", &saveptr1);
            if (token == NULL)
                break;
            char *temp = (char *)malloc(sizeof(char) * (1 + strlen(token)));
            strcpy(temp, token);
#pragma omp task
            insert(stoproot, temp);
        }
    }

#pragma omp taskwait
    fclose(entry_file);
}
