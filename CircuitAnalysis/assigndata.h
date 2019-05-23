#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef DELIMITERFUNCTION_H
#include "delimiterfunction.h"
#endif

struct input_data 
{
	int node_arr[20][2];
	float res[20];
	float source_voltage;
	float source_current;
	float source_res;
	int load_node;
	int load_res;
	int num_elements;
};

struct input_data assign_data(char* data_str)
{
	struct input_data data_struct = {
	.node_arr = 0,
	.res = 0,
	.source_voltage = 0,
	.source_current = 0,
	.source_res = 0,
	.load_node = 0,
	.load_res = 0,
	.num_elements = 0
	};

	//Assigns <CIRCUIT> node associations to data_struct.node_arr[][], and resistance value to data_struct.res[]
	char var;
	int i = 0;
	float  inputval = { 0 };

	//Attains string between "<CIRCUIT>" and "</CIRCUIT>"
	char* circuit_string = delim_func(data_str, "<CIRCUIT>", "</CIRCUIT>");

	//Tokenises string into lines for sscanf
	char* input_nodes = strtok(circuit_string, "\n");
	while (input_nodes != NULL)
	{
		//Circuit component connections stored in data_struct, where conductance is converted to resistance if required
		sscanf(input_nodes, "n1=%d n2=%d %c=%f\n", &data_struct.node_arr[i][0], &data_struct.node_arr[i][1], &var, &inputval);
		if (var == 'G') {
			data_struct.res[i] = 1 / inputval;
		}
		else {
			data_struct.res[i] = inputval;
		}

		//Resets input_node pointer
		input_nodes = strtok(NULL, "\n");
		i++;
	}

	//<TERMS> input for source V: data_struct.source_voltage, or I: data_struct.source_current for Norton, and associated R: data_struct.source_res
	char thv_type[5], thv_input[5];
	float source_val = { 0 }, source_input = { 0 };


	//Assigns <TERMS> block values to variables
	char* thv_source = delim_func(data_str, "<TERMS>", "</TERMS>");
	sscanf(thv_source, "%2s=%f %2s=%f\n", thv_type, &source_val, thv_input, &source_input);

	//Assigns source values for current or voltage
	if (thv_type[0] == 'V') {
		data_struct.source_voltage = source_val;

		if (thv_input[0] == 'R') {
			data_struct.source_res = source_input;
		}
		else {
			data_struct.source_res = 1 / source_input;
		}
	}
	else {
		data_struct.source_current = source_val;

		if (thv_input[0] == 'R') {
			data_struct.source_res = source_input;
		}
		else {
			data_struct.source_res = 1 / source_input;
		}
	}

	//<TERMS> input for load node connection and R value
	char* thv_sourcel2 = strstr(thv_source, "\n") + 1;
	sscanf(thv_sourcel2, "%d RL=%d\n", &data_struct.load_node, &data_struct.load_res);

	//Number of elements in a circuit
	int num_element = 0;
	while (data_struct.node_arr[num_element][0] != 0)
	{
		num_element++;
	}

	data_struct.num_elements = num_element;

	//Loop to ensure smaller node connection value is in 1st column of the array
	for (int c = 0; c < num_element + 1; c++)
	{
		if (data_struct.node_arr[c][1] < data_struct.node_arr[c][0] && data_struct.node_arr[c][1] != 0)
		{
			//Where a non-zero value is present, the smaller input node value is stored in the 1st line
			int swap7 = data_struct.node_arr[c][0];
			data_struct.node_arr[c][0] = data_struct.node_arr[c][1];
			data_struct.node_arr[c][1] = swap7;
			swap7 = 0;
		}
	}

	//Bubble sort by first node value
	for (int a = 0; a < num_element - 1; a++) //Loop for num_element number of elements
	{
		for (int b = 0; b < (num_element - a - 1); b++) //Last element which has been sorted already
		{
			if (data_struct.node_arr[b][0] > data_struct.node_arr[b + 1][0])
			{
				//Where there is a greater 1st node, the larger value's associated node values
				//and resistance is along the array
				int swap1 = data_struct.node_arr[b][0];
				data_struct.node_arr[b][0] = data_struct.node_arr[b + 1][0];
				data_struct.node_arr[b + 1][0] = swap1;
				swap1 = 0;

				int swap2 = data_struct.node_arr[b][1];
				data_struct.node_arr[b][1] = data_struct.node_arr[b + 1][1];
				data_struct.node_arr[b + 1][1] = swap2;
				swap2 = 0;

				float swap3 = data_struct.res[b];
				data_struct.res[b] = data_struct.res[b + 1];
				data_struct.res[b + 1] = swap3;
				swap3 = 0;
			}
		}
	}

	//Ensures shunts are ahead of resistors in the data array
	for (int c = 0; c < num_element + 1; c++)
	{
		if (data_struct.node_arr[c][0] == data_struct.node_arr[c + 1][0] && data_struct.node_arr[c][1] > data_struct.node_arr[c + 1][1])
		{
			//For a node i, if a shunt is present  before a series resistance it must be before it in the array
			int swap4 = data_struct.node_arr[c][0];
			data_struct.node_arr[c][0] = data_struct.node_arr[c + 1][0];
			data_struct.node_arr[c + 1][0] = swap4;
			swap4 = 0;

			int swap5 = data_struct.node_arr[c][1];
			data_struct.node_arr[c][1] = data_struct.node_arr[c + 1][1];
			data_struct.node_arr[c + 1][1] = swap5;
			swap5 = 0;

			float swap6 = data_struct.res[c];
			data_struct.res[c] = data_struct.res[c + 1];
			data_struct.res[c + 1] = swap6;
			swap6 = 0;
		}
	}

	return data_struct;
}