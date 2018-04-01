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

void fill_global(char *token)
{
	map<string, countindex>::iterator itr;
	itr = global_dict.find(token);

	if (itr == global_dict.end())
	{
		countindex temp;
		temp.count = 1;
		temp.index = -1;
		global_dict[token] = temp;
		// cout << "not found" << '\n';
		// fill_global(token);
	}
	else
	{
		global_dict[token].count++;
	}

	// cout << token << '\n';
}
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
				// cout << "not found" << '\n';
				fill_global(token);
			}
			// else{
			// 	local_dict[token]++;
			// }
		}
	}
	local_dict.clear();
	// for(itr = local_dict.begin();itr!=local_dict.end();++itr){
	// 	cout << itr->first << '\t' << itr->second << '\n';
	// }
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