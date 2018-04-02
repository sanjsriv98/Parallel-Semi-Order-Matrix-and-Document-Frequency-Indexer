#include "_Hash.h"

char* isalphabet(char* temp){
	char* p;
	for ( p=temp; *p; ++p) if(!isalpha(*p)) *p=' ';
	return temp;
}


int hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (int)(hash%M);
}

void createEmptyHT(){
	ht =(hashTable)calloc(M,sizeof(hashtable)); 
}

void insertWord(char* str){
	int h = hash(str);
	if(ht[h].head==NULL){

		ht[h].size=1;
		wordCount newWord = (wordCount)malloc(sizeof(wordcount));
		newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));
		strcpy(newWord->wordName,str);
		newWord->count =1;
		wordList wl = (wordList)malloc(sizeof(wordlist));
		wl->wc = newWord;
		wl->next=NULL;
		ht[h].head = wl;
		return;
	}
	wordList temp=ht[h].head;
	wordList prev=NULL;
	if (strcmp(temp->wc->wordName,str)==0){
		temp->wc->count+=1;
		return;
	}
	if(strcmp(temp->wc->wordName,str)>0){
		wordCount newWord = (wordCount)malloc(sizeof(wordcount));
		newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));
		strcpy(newWord->wordName,str);
		newWord->count =1;
		wordList wl = (wordList)malloc(sizeof(wordlist));
		wl->wc = newWord;
		wl->next=temp;
		ht[h].head=wl;
		ht[h].size+=1;
		return;
	}
	if(temp->next ==NULL){
		wordCount newWord = (wordCount)malloc(sizeof(wordcount));
		newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));strcpy(newWord->wordName,str);
		strcpy(newWord->wordName,str);
		newWord->count =1;
		wordList wl = (wordList)malloc(sizeof(wordlist));
		wl->wc = newWord;
		wl->next=NULL;
		ht[h].size+=1;
		temp->next = wl;
		return;
		
	}
	while(temp->next!=NULL){
		if (strcmp(temp->wc->wordName,str)==0){
			temp->wc->count+=1;
			return;
		}	
		if(strcmp(temp->wc->wordName,str)>0){
			wordCount newWord = (wordCount)malloc(sizeof(wordcount));
			newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));
			strcpy(newWord->wordName,str);
			newWord->count =1;
			wordList wl = (wordList)malloc(sizeof(wordlist));
			wl->wc = newWord;
			wl->next=temp;
			prev->next=wl;
			ht[h].size+=1;
			return;
		}
		prev=temp;
		temp=temp->next;
	}
	wordCount newWord = (wordCount)malloc(sizeof(wordcount));
	newWord->wordName = (char*)malloc((1+strlen(str))*sizeof(char));
	strcpy(newWord->wordName,str);
	newWord->count =1;
	wordList wl = (wordList)malloc(sizeof(wordlist));
	wl->wc = newWord;
	wl->next=NULL;
	ht[h].size+=1;
	temp->next = wl;
	return;
}
void fill_ht(char* docName){
	// cout << docName << "\n";
	FILE* entry_file = fopen(docName, "r");

	if (entry_file == NULL)
	{
		fprintf(stderr, "Error : Failed to open entry file %s\n",docName);
		return;
	}
	map<string, int> local_dict;
	map<string, int>::iterator itr;
	char * line = NULL,*saveptr1,*str1,*token,*p;
	size_t len = 0;
	ssize_t read;
	int j,k,temp,h;
	while ((read = getline(&line, &len, entry_file)) != -1) {
		line = isalphabet(line);
		for (j = 1, str1 = line; ; j++, str1 = NULL) {
			token = strtok_r(str1,"  \n\t", &saveptr1);
			if (token == NULL)
				break;
			for ( p=token; *p; ++p) *p = tolower(*p);

			itr = local_dict.find(token);

			if (itr == local_dict.end())
			{
				local_dict[token] = 1;
				h = hash(token);
				// cout << "lock is "<< h << "\n";
				omp_set_lock(&hashLocks[h]);
				// cout << "hvhgghhh" << h<<"\n";

				insertWord(token);
				omp_unset_lock(&hashLocks[h]);
			}
		}
	}
	local_dict.clear();
	fclose(entry_file);
	return;
}

void printHT(){
	int i=0,s=0;
	for(i=0;i<M;i++){
		if(ht[i].head==NULL){
			continue;
		}
		printf("Hash Entry %d : %d\n",i,ht[i].size);
		wordList temp =ht[i].head;
		while(temp!=NULL){
			printf("%s %d\n",temp->wc->wordName,temp->wc->count);
			temp=temp->next;
		}
		s+=ht[i].size;
		printf("\n");
	}
	printf("%d\n",s );
}

void fillCumFreq(){
	int i=0,size=M,temp=0;
	for(i=0;i<M;i++){
		temp+=ht[i].size;
		ht[i].cf=temp;
	}
	return;
}


wordCount fillarray(){
	wordCount arr =(wordCount)malloc(sizeof(wordcount)*ht[M-1].cf);
	int i=0,j=0;
	wordList temp,prev;
	#pragma omp parallel shared(arr)
	{
	#pragma omp for  private(j,temp,prev)
	for(i=0;i<M;i++)
	{	
		// ht[i].size>0 ? cout << i<<"\t"<<ht[i].size << "\n" : cout << ""; 
		temp=ht[i].head;
		for(j=0;j<ht[i].size;j++){
			arr[ht[i].cf-ht[i].size+j].count =temp->wc->count;
			arr[ht[i].cf-ht[i].size+j].wordName = temp->wc->wordName;
			prev=temp;
			temp=temp->next;
			free(prev->wc);
			free(prev);
			// cout << ht[i].size<<arr[ht[i].cf-ht[i].size+j].wordName << "\tinside\t" << arr[ht[i].cf-ht[i].size+j].count << "\n";	
		}
		// cout << "\n";
	}
	}
	free(ht);
	// printArray(arr,ht[m-1].cf);
	return arr;
}


// void omp_set_lock(omp_lock_t *lock){return;}

// void omp_unset_lock(omp_lock_t *lock){return;}

// void omp_init_lock(omp_lock_t *lock){return;}