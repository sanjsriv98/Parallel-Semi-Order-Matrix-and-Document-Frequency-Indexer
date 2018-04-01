// #include <stdio.h>
#include "_Dict.h"

char *isalphabet(char *temp)
{
	char *p;
	for (p = temp; *p; ++p)
		if (!isalpha(*p))
			*p = ' ';
	return temp;
}

// void fill_global(char *token)
// {
// 	map<string, countindex>::iterator itr;
// 	itr = global_dict.find(token);

// 	if (itr == global_dict.end())
// 	{
// 		countindex temp;
// 		temp.count = 1;
// 		temp.index = -1;
// 		global_dict[token] = temp;
// 		if (temp.count > conf)
// 		{
// 			// LOCK
// 			if (temp.count > global_heap->arr[0].count)
// 			{
// 				global_dict[global_heap->arr[0].word].index = -1;
// 				global_dict[token].index = 0;
// 				global_heap->arr[0].count = temp.count;
// 				global_heap->arr[0].word = global_dict.find(token)->first;
// 				minHeapify(global_heap, global_heap->size - 1, 0);
// 			}
// 			// UNLOCK
// 			conf = global_heap->arr[0].count;
// 		}
// 		// cout << "not found" << '\n';
// 		// fill_global(token);
// 		// global_heap->size = 0;
// 	}
// 	else
// 	{
// 		global_dict[token].count++;
// 		if (global_dict[token].index == -1)
// 		{
// 			if (global_dict[token].count > conf)
// 			{
// 				// LOCK
// 				if (global_dict[token].count > global_heap->arr[0].count)
// 				{
// 					global_dict[global_heap->arr[0].word].index = -1;
// 					global_dict[token].index = 0;
// 					global_heap->arr[0].count = global_dict[token].count;
// 					global_heap->arr[0].word = global_dict.find(token)->first;
// 					minHeapify(global_heap, global_heap->size - 1, 0);
// 				}
// 				// UNLOCK
// 				conf = global_heap->arr[0].count;
// 			}
// 		}
// 		else
// 		{
// 			// LOCK
// 			int index = global_dict[token].index;
// 			global_heap->arr[index].count++;
// 			minHeapify(global_heap, global_heap->size - 1, index);
// 			// UNLOCK
// 			if (index == 0)
// 			{
// 				conf = global_heap->arr[0].count;
// 			}
// 		}
// 	}

// 	// cout << token << '\n';
// }

void fill_dict(const char *docName)
{
	FILE *entry_file = fopen(docName, "r");
	map<string, int> local_dict;
	map<string, int>::iterator itr;
	if (entry_file == NULL)
	{
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
			for (p = token; *p; ++p)
				*p = tolower(*p);
			itr = local_dict.find(token);

			if (itr == local_dict.end())
			{
				local_dict[token] = 1;
				// if (strcmp(token, "h") == 0)
				// {
				// 	printf(" h\t %s\n", docName);
				// }
				// cout << "not found" << '\n';
				// fill_global(token);
				insert(root, token);
			}
			// else{
			// 	local_dict[token]++;
			// }
		}
	}
	// for (itr = local_dict.begin(); itr != local_dict.end(); ++itr)
	// {
	// 	cout << itr->first << '\t' << itr->second << '\n';
	// }
	local_dict.clear();
}

// int main(int argc,char *argv[]){
// 	global_dict.clear();
// 	if (argc == 1)
//         fill_dict("map.cpp");
//     else
//         fill_dict(argv[1]);
//     map <string,countindex> :: iterator itr;
//     for(itr = global_dict.begin();itr!=global_dict.end();++itr){
// 		cout << itr->first << '\t' << itr->second.count << '\t' << itr->second.index << '\n';
// 	}
// 	global_dict.clear();
// 	// fill_dict("map.cpp");
// 	// cout << '\t' << local_dict.find("value_4")  << '\n';
// 	// printf("%d\n",local_dict.find("value"));
// 	return 0;
// }