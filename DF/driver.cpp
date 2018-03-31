#include "_Trie.h"

char* isalphabet(char* temp){
	char* p;
	for ( p=temp; *p; ++p) if(!isalpha(*p)) *p=' ';
	return temp;
}

trieNode fill_trie(char* docName,trieNode local_root,trieNode global_root){
	FILE* entry_file = fopen(docName, "r");
	if (entry_file == NULL)
	{
		fprintf(stderr, "Error : Failed to open entry file\n");
		return NULL;
	}
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
				temp=insert(local_root,token);
				if(temp==1){
					temp=insert(global_root,token);	
				}
		}
	}
	return root;
}

// trieNode fill_global_trie(trieNode* root,trieNode* docNode){
// 	trieNode pCrawl =root;
// 	trieNode pCrawlDoc = docNode;
// 	int i=0;
// 	for(i=0;i<26;i++){
		
// 	}
// }


int main(){
	
	return 0;
}