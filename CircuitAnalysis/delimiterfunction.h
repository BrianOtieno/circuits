#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* delim_func(const char *data, const char *start_delim, const char *end_delim)
{
	//Returns string pointer of string between "start_delim" and "end_delim"
	char *target = NULL;
	char *start, *end;

	//Finds pointer to end of start_delim and end_delim
	start = strstr(data, start_delim);
	start += strlen(start_delim);
	end = strstr(start, end_delim);

	//Allocates mnemory for string assignment and copies string between delmiters
	target = (char*)malloc(end - start + 1);
	memcpy(target, start, end - start);

	if (target == NULL) {
		printf("Error creating data string");
	}
	//Null termination and removal of \n character
	target[end - start] = '\0';
	target += 1;

	return target;
}