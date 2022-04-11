#include "header.h"

const int max_k_strings = 1000;

int miss_all_blank(char* buffer, int* position)
{
	while(buffer[*position] == ' ')
	{
		++(*position);
	}
}


char** part_buff(char* buffer)
{
	char** strings = (char**)calloc(max_k_strings, sizeof(char*));
	if(!strings)
		return NULL;

	int position = 0;
	int len = strlen(buffer);
	int k_str = 0;

	while(position < len)
	{
		miss_all_blank(buffer, &position);
		char* end_str_ptr = strchr(buffer, '\n');
		int str_len = int(buffer + position - end_str_ptr + 1);

		char* new_str = (char*)calloc(str_len + 1, sizeof(char));
		if(!new_str)
			return NULL;

		for(int i = 0; i < str_len; ++i)
		{
			new_str[i] = buffer[position];
			++position;
		}

		new_str[str_len] = '\0';

		++k_str;
	}
}

int main()
{
	char *str = "aabaaca";
	char* pos = strchr(str, 'b');

	printf("%p %p %d\n", str, pos, pos-str);

	return 0;
}