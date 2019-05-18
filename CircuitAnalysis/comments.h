#include <string.h>
#include <stdlib.h>



char* comment_remove(const char* data, const char* start_delim, const char* end_delim)
{
	//Returns string pointer of string between "start_delim" and "end_delim"
	char* target = NULL;
	char* start, * end;

	//Finds pointer to start of start_delim and end_delim
	start = strstr(data, start_delim);
	end = strstr(start, end_delim);

	//Adds 1 for length of end_delim
	end += +1;

	//Allocates mnemory for string assignment and copies string between delmiters to target
	target = (char*)malloc(end - start + 1);
	memcpy(target, start, end - start);

	if (start == NULL) {
		return("empty");
	}

	//Null termination
	target[end - start] = '\0';

	return target;
}