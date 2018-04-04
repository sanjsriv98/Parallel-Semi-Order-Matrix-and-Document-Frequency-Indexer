// #include <stdio.h>
#include "_Dict.h"

// char *isalphabet(char *temp)
// {
// 	char *p;
// 	for (p = temp; *p; ++p)
// 		if (!isalpha(*p))
// 			*p = ' ';
// 		else
// 		{
// 			*p = tolower(*p);
// 		}
// 	return temp;
// }

void fill_dict(char *docName)
{
	// cout << docName << "\n";
	FILE *entry_file = fopen(docName, "r");
	map<string, int> local_dict;
	map<string, int>::iterator itr;
	if (entry_file == NULL)
	{
		// cout << docName << "\n";
		fprintf(stderr, "Error : Failed to open entry file\n");
		return;
	}
	else
	{
		// cout << docName << "\n";
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
			// for (p = token; *p; ++p)
			// 	*p = tolower(*p);
			if (search(stoproot, token))
				continue;
			itr = local_dict.find(token);

			if (itr == local_dict.end())
			{
				local_dict[token] = 1;
				// if (strcmp(token, "") == 0)
				// {
				// 	cout << "lol" << docName << "\n";
				// }
				char *temp = (char *)malloc(sizeof(char) * (1 + strlen(token)));
				strcpy(temp, token);
#pragma omp task
				insert(root, temp);
			}
			// else
			// {
			// 	local_dict[token]++;
			// }
		}
	}
#pragma omp taskwait
	// for (itr = local_dict.begin(); itr != local_dict.end(); ++itr)
	// {
	// 	cout << itr->first << '\t' << itr->second << '\n';
	// }
	fclose(entry_file);
	// for (itr = local_dict.begin(); itr != local_dict.end(); ++itr)
	// {
	// 	cout << "key: \"" << itr->first << "\" "
	// 		 << "value: " << itr->second << "   filename :" << docName << endl;
	// }
	local_dict.clear();
	free(docName);
}
