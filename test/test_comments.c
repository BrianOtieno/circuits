#include "../CircuitAnalysis/openfile.h"
#include "../CircuitAnalysis/assigndata.h"
#include "../CircuitAnalysis/matrixmultiplication.h"
#include "../CircuitAnalysis/outputdisplay.h"


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



struct output_data output_struct(struct input_data data_struct, struct matrix circuitmatrix);
void file_print(char* data_string, struct output_data outputdata);

int main(int argc, char const *argv[])
{
  
    char* data_string = open_file();

    if(data_string == NULL){
        assert(false && "No data test data imported!");
    }else{
        assert(true && "Data imported!");
	    printf("In data:\n %s\n", data_string);
    }

    //Check if # not in comment

    if (strstr(data_string, "#")!=NULL){
        assert(false && "Comments still in data");
    }

    printf("No comments in: \n %s\n ", data_string); 
    //Returns data_struct containing sorted data for calculations
	struct input_data data_struct = assign_data(data_string);

	//Returns matrix struct containing overall circuit matrix
	struct matrix circuitmatrix = circuit_matrix(data_struct);
	printf("Overall Circuit Matrix A, B, C, D:\n %f\n %f\n %f\n %f\n", circuitmatrix.A, circuitmatrix.B, circuitmatrix.C, circuitmatrix.D);

    //Returns struct outputdata containing output values
	struct output_data outputdata = output_struct(data_struct, circuitmatrix);

	//Formats output file and output data
	file_print(data_string, outputdata);
}


