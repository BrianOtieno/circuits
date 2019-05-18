#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "openfile.h"
#include "assigndata.h"
#include "matrixmultiplication.h"
#include "delimiterfunction.h"system("eog image.jpg");


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

struct matrix
{
	float A, B, C, D;
};

struct output_data
{
	float Vin[2];
	float Iin[2];
	float Pin[2];
	float Zin[2];
	float Vout[2];
	float Iout[2];
	float Pout[2];
	float Zout[2];
	float Av[2];
	float Ai[2];
};

char *open_file();
// char *delim_func(const char* data, const char* start_delim, const char* end_delim);
// struct input_data assign_data(char* data_str);
// struct matrix matrix_multiply(struct matrix matrix1, struct matrix matrix2);
struct matrix circuit_matrix(struct input_data data_struct);
struct output_data output_struct(struct input_data data_struct, struct matrix circuitmatrix);
void file_print(char* data_string, struct output_data outputdata);
char* comment_remove(const char* data, const char* start_delim, const char* end_delim);
char* strremove(char* str, const char* sub);

int main()
{
	printf("Feeding data... \n");
	system("eog images/problem.jpg");
	//OPENS ADBC_input.dat and stores data string in data_string
	char* data_string = open_file();
	printf("The following Data was inputted:\n %s\n", data_string);

	//Returns data_struct containing sorted data for calculations
	struct input_data data_struct = assign_data(data_string);

	//Returns matrix struct containing overall circuit matrix
	struct matrix circuitmatrix = circuit_matrix(data_struct);
	printf("Overall Circuit Matrix A, B, C, D:\n %f\n %f\n %f\n %f\n", circuitmatrix.A, circuitmatrix.B, circuitmatrix.C, circuitmatrix.D);

	//Returns struct outputdata containing output values
	struct output_data outputdata = output_struct(data_struct, circuitmatrix);

	//Formats output file and output data
	file_print(data_string, outputdata);

	return(0);
}

