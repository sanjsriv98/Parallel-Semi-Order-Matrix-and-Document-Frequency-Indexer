#include "_Hash.h"

char *isalphabet(char *temp)
{
	char *p;
	for (p = temp; *p; ++p)
	{
		if (!isalpha(*p))
			*p = ' ';
		else
			*p = tolower(*p);
	}
	return temp;
}

int myhash(char *str)
{
	unsigned long myhash = 5381;
	int c;
	while (c = *str++)
		myhash = ((myhash << 5) + myhash) + c; /* myhash * 33 + c */
	return (int)(myhash % M);
}

void createEmptyHT()
{
	ht = (hashTable)calloc(M, sizeof(hashtable));
}

void insertWord(char *str, int h)
{
	if (ht[h].head == NULL)
	{

		ht[h].size = 1;
		wordCount newWord = (wordCount)malloc(sizeof(wordcount));
		newWord->wordName = (char *)malloc((1 + strlen(str)) * sizeof(char));
		strcpy(newWord->wordName, str);
		newWord->count = 1;
		wordList wl = (wordList)malloc(sizeof(wordlist));
		wl->wc = newWord;
		wl->next = NULL;
		ht[h].head = wl;
		return;
	}
	wordList temp = ht[h].head;
	wordList prev = NULL;
	if (strcmp(temp->wc->wordName, str) == 0)
	{
		temp->wc->count += 1;
		return;
	}
	if (strcmp(temp->wc->wordName, str) > 0)
	{
		wordCount newWord = (wordCount)malloc(sizeof(wordcount));
		newWord->wordName = (char *)malloc((1 + strlen(str)) * sizeof(char));
		strcpy(newWord->wordName, str);
		newWord->count = 1;
		wordList wl = (wordList)malloc(sizeof(wordlist));
		wl->wc = newWord;
		wl->next = temp;
		ht[h].head = wl;
		ht[h].size += 1;
		return;
	}
	// if(temp->next ==NULL){
	// 	wordCount newWord = (wordCount)malloc(sizeof(wordcount));
	// 	newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));strcpy(newWord->wordName,str);
	// 	strcpy(newWord->wordName,str);
	// 	newWord->count =1;
	// 	wordList wl = (wordList)malloc(sizeof(wordlist));
	// 	wl->wc = newWord;
	// 	wl->next=NULL;
	// 	ht[h].size+=1;
	// 	temp->next = wl;
	// 	return;

	// }
	while (temp->next != NULL)
	{
		if (strcmp(temp->wc->wordName, str) == 0)
		{
			temp->wc->count += 1;
			return;
		}
		if (strcmp(temp->wc->wordName, str) > 0)
		{
			wordCount newWord = (wordCount)malloc(sizeof(wordcount));
			newWord->wordName = (char *)malloc((1 + strlen(str)) * sizeof(char));
			strcpy(newWord->wordName, str);
			newWord->count = 1;
			wordList wl = (wordList)malloc(sizeof(wordlist));
			wl->wc = newWord;
			wl->next = temp;
			prev->next = wl;
			ht[h].size += 1;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	wordCount newWord = (wordCount)malloc(sizeof(wordcount));
	newWord->wordName = (char *)malloc((1 + strlen(str)) * sizeof(char));
	strcpy(newWord->wordName, str);
	newWord->count = 1;
	wordList wl = (wordList)malloc(sizeof(wordlist));
	wl->wc = newWord;
	wl->next = NULL;
	ht[h].size += 1;
	temp->next = wl;
	return;
}
void fill_ht(char *docName)
{
	FILE *entry_file = fopen(docName, "r");

	if (entry_file == NULL)
	{
		fprintf(stderr, "Error : Failed to open entry file %s\n", docName);
		return;
	}
	map<string, int> local_dict;
	map<string, int>::iterator itr;
	char *line = NULL, *saveptr1, *str1, *token, *p;
	size_t len = 0;
	ssize_t read;
	int j, k, temp, h;
	while ((read = getline(&line, &len, entry_file)) != -1)
	{
		line = isalphabet(line);
		for (j = 1, str1 = line;; j++, str1 = NULL)
		{
			token = strtok_r(str1, "  \n\t", &saveptr1);
			if (token == NULL)
				break;
			h = myhash(token);
			if (checkStopWord(token, h) == 1)
				continue;
			itr = local_dict.find(token);

			if (itr == local_dict.end())
			{
				local_dict[token] = 1;
				omp_set_lock(&hashLocks[h]);
				// #pragma omp critical
				{
					insertWord(token, h);
				}
				omp_unset_lock(&hashLocks[h]);
			}
		}
	}
	local_dict.clear();
	fclose(entry_file);
	return;
}

void printHT()
{
	int i = 0, s = 0;
	for (i = 0; i < M; i++)
	{
		if (ht[i].head == NULL)
		{
			continue;
		}
		printf("myhash Entry %d : %d\n", i, ht[i].size);
		wordList temp = ht[i].head;
		while (temp != NULL)
		{
			printf("%s %d\n", temp->wc->wordName, temp->wc->count);
			temp = temp->next;
		}
		s += ht[i].size;
		printf("\n");
	}
	printf("%d\n", s);
}

void fillCumFreq()
{
	int i = 0, temp = 0;
	for (i = 0; i < M; i++)
	{
		temp += ht[i].size;
		ht[i].cf = temp;
	}
	return;
}

wordCount fillarray()
{
	wordCount arr = (wordCount)malloc(sizeof(wordcount) * ht[M - 1].cf);
	int i = 0, j = 0;
	wordList temp, prev;
#pragma omp parallel for schedule(dynamic) private(j, temp, prev)
	for (i = 0; i < M; i++)
	{
		temp = ht[i].head;
		for (j = 0; j < ht[i].size; j++)
		{
			arr[ht[i].cf - ht[i].size + j].count = temp->wc->count;
			arr[ht[i].cf - ht[i].size + j].wordName = temp->wc->wordName;
			prev = temp;
			temp = temp->next;
			free(prev->wc);
			free(prev);
		}
	}
	free(ht);
	return arr;
}

void makeStopWords(const char *fname)
{
	sht = (stopWord *)malloc(M * sizeof(stopWord));
	int i;
	for (i = 0; i < M; i++)
	{
		sht[i] = NULL;
	}
	FILE *fp = fopen(fname, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error : Failed to open entry file\n");
		return;
	}
	char *line = NULL, *saveptr1, *str1, *token, *p;
	size_t len = 0;
	ssize_t read;
	stopWord temp;
	char *key;
	int j, k;
	while ((read = getline(&line, &len, fp)) != -1)
	{
		line = isalphabet(line);
		for (j = 1, str1 = line;; j++, str1 = NULL)
		{
			token = strtok_r(str1, " \n\t", &saveptr1);
			if (token == NULL)
				break;
			k = myhash(token);
			key = (char *)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(key, token);
			temp = (stopWord)malloc(sizeof(stopword));
			temp->key = key;
			temp->next = sht[k];
			sht[k] = temp;
		}
	}
	fclose(fp);
	return;
}

int checkStopWord(char *key, int hash)
{
	if (sht[hash] == NULL)
	{
		return 0;
	}
	else
	{
		stopWord temp;
		temp = sht[hash];
		while (temp != NULL)
		{
			if (strcmp(temp->key, key) == 0)
			{
				return 1;
			}
			temp = temp->next;
		}
		return 0;
	}
}