#include "_Hash.h"

char* isalphabet(char* temp){
	char* p;
	for ( p=temp; *p; ++p) if(!isalpha(*p)) *p=' ';
	return temp;
}


int hash(char *str,int m)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (int)(hash%m);
}

void createEmptyHT(){
	ht =(hashTable)calloc(m,sizeof(hashtable)); 
}

void insertWord(char* str){
	int h = hash(str,m);
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
	
	FILE* entry_file = fopen(docName, "r");

	if (entry_file == NULL)
	{
		fprintf(stderr, "Error : Failed to open entry file\n");
		return;
	}
	map<string, int> local_dict;
	map<string, int>::iterator itr;
	char * line = NULL,*saveptr1,*str1,*token,*p;
	size_t len = 0;
	ssize_t read;
	int j,k,temp;
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
				insertWord(token);
			}
		}
	}
	local_dict.clear();
	return;
}

void printHT(){
	int i=0,s=0;
	for(i=0;i<m;i++){
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
	int i=0,size=m,temp=0;
	for(i=0;i<m;i++){
		temp+=ht[i].size;
		ht[i].cf=temp;
	}
	return;
}


wordCount fillarray(){
	wordCount arr =(wordCount)malloc(sizeof(wordcount)*ht[m-1].cf);
	int i=0,j=0;
	wordList temp;
	// #pragma omp parallel shared(arr)
	{
	// #pragma omp for  private(j,temp)
	for(i=0;i<m;i++)
	{	
		// ht[i].size>0 ? cout << i<<"\t"<<ht[i].size << "\n" : cout << ""; 
		temp=ht[i].head;
		for(j=0;j<ht[i].size;j++){
			arr[ht[i].cf-ht[i].size+j].count =temp->wc->count;
			arr[ht[i].cf-ht[i].size+j].wordName = temp->wc->wordName;
			temp=temp->next;
			// cout << ht[i].size<<arr[ht[i].cf-ht[i].size+j].wordName << "\tinside\t" << arr[ht[i].cf-ht[i].size+j].count << "\n";	
		}
		// cout << "\n";
	}
	}
	// printArray(arr,ht[m-1].cf);
	return arr;
}

