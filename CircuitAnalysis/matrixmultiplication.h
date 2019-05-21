#include <stdlib.h>
#include <math.h>
#include <string.h>



struct matrix matrix_multiply(struct matrix matrix1, struct matrix matrix2)
{
	//Multiplies matrix1 by matrix2
	struct matrix matrix = {
	.A = 0,
	.B = 0,
	.C = 0,
	.D = 0,
	};

	matrix.A = matrix1.A * matrix2.A + matrix1.B * matrix2.C;
	matrix.B = matrix1.A * matrix2.B + matrix1.B * matrix2.D;
	matrix.C = matrix1.C * matrix2.A + matrix1.D * matrix2.C;
	matrix.D = matrix1.C * matrix2.B + matrix1.D * matrix2.D;

	return matrix;
}

struct matrix circuit_matrix(struct input_data data_struct)
{
	//Calculates overall circuit matrix 

	//Initial identity matrix
	struct matrix matrix1 = { .A = 1,.B = 0,.C = 0,.D = 1 };
	struct matrix matrix2 = { .A = 0,.B = 0,.C = 0,.D = 0 };

	//Loop through every component j in circuit
	for (int j = 1; j < data_struct.num_elements + 1; j++)
	{
		//ABCD matrix for a shunt resistance
		if (data_struct.node_arr[j - 1][1] == 0) {
			matrix2.A = 1;
			matrix2.B = 0;
			matrix2.C = 1 / data_struct.res[j - 1];
			matrix2.D = 1;
		}
		//ABCD matrix for a series resistance
		else
		{
			matrix2.A = 1;
			matrix2.B = data_struct.res[j - 1];
			matrix2.C = 0;
			matrix2.D = 1;
		}
		//Matrix 1 contains the overall matrix of i components, therefore matrix 2 contains nxt component values
		matrix1 = matrix_multiply(matrix1, matrix2);
	}
	return matrix1;
}



struct output_data output_struct(struct input_data data_struct, struct matrix circuitmatrix)
{
	//Forming output struct
	struct output_data outputdata = {
	.Vin = 0,
	.Iin = 0,
	.Pin = 0,
	.Zin = 0,
	.Vout = 0,
	.Iout = 0,
	.Pout = 0,
	.Zout = 0,
	.Av = 0,
	.Ai = 0
	};

	//Stores Zin in outputdata[0].Zin struct, and db equivalent in outputdata.Zin[1]
	outputdata.Zin[0] = (circuitmatrix.A * data_struct.load_res + circuitmatrix.B) / (circuitmatrix.C * data_struct.load_res + circuitmatrix.D);
	outputdata.Zin[1] = 20 * log10f(outputdata.Zin[0]);

	//Repeated for all possible output values
	outputdata.Zout[0] = (circuitmatrix.D * data_struct.source_res + circuitmatrix.B) / (circuitmatrix.C * data_struct.source_res + circuitmatrix.A);
	outputdata.Zout[1] = 20 * log10f(outputdata.Zout[0]);

	outputdata.Av[0] = 1 / (circuitmatrix.A + (circuitmatrix.B / data_struct.load_res));
	outputdata.Av[1] = 20 * log10f(outputdata.Av[0]);

	outputdata.Ai[0] = 1 / (circuitmatrix.C * data_struct.load_res + circuitmatrix.D);
	outputdata.Ai[1] = 20 * log10f(outputdata.Ai[0]);

	outputdata.Vin[0] = (data_struct.source_voltage * outputdata.Zin[0]) / (data_struct.source_res + outputdata.Zin[0]);
	outputdata.Vin[1] = 20 * log10f(outputdata.Vin[0]);

	outputdata.Iin[0] = data_struct.source_voltage / (data_struct.source_res + outputdata.Zin[0]);
	outputdata.Iin[1] = 20 * log10f(outputdata.Iin[0]);

	outputdata.Pin[0] = outputdata.Vin[0] * outputdata.Iin[0];
	outputdata.Pin[1] = 10 * log10f(outputdata.Pin[0]);

	outputdata.Vout[0] = outputdata.Vin[0] * outputdata.Av[0];
	outputdata.Vout[1] = 20 * log10f(outputdata.Vout[0]);

	outputdata.Iout[0] = outputdata.Iin[0] * outputdata.Ai[0];
	outputdata.Iout[1] = 20 * log10f(outputdata.Iout[0]);

	outputdata.Pout[0] = outputdata.Vout[0] * outputdata.Iout[0];
	outputdata.Pout[1] = 10 * log10f(outputdata.Pout[0]);

	return outputdata;
}



// #endif