#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "comments.h"
#include "removestring.h"


char* open_file()
{
	//Opens file "ABCD_input.dat" and stores string in data_str
	// FILE* input_data = fopen("ABCD_input.dat", "r");
	FILE* input_data = fopen("../Data/Netlist_06Ga.dat", "r");

	if (input_data == NULL) {
		return "No file opened";
	}

	//Attains length of input_data file stream
	fseek(input_data, 0, SEEK_END);
	long length = ftell(input_data);

	//Reset stream pointer and allocate memory for data string
	fseek(input_data, 0, SEEK_SET);
	char* data_str = malloc((length + 1) * sizeof(char));

	if (data_str == NULL) {
		return "Data not copied to string";
	}

	//Places file stream into block of memory
	long offset = 0;
	while (!feof(input_data) && offset < length) {
		offset += fread(data_str + offset, sizeof(char), length - offset, input_data);
	}
	
	//Null terminates data string
	data_str[offset] = '\0';

	//Loop to remove comments from data_str
	char* sub;

	//When there are comments in data_str
	while ((strstr(data_str, "#")) != NULL) {

		//Find location of the comment
		sub = comment_remove(data_str, "#", "\n");

		//Comment removed from data_str
		data_str = strremove(data_str, sub);
		sub = NULL;
	}
	
	//Null terminates string
	fclose(input_data);

	return data_str;
}