#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>



void file_print(char* data_string, struct output_data outputdata)
{
	//Formatting output data and creating file
	
	char outval[13][30];
	int i = 0;

	//Returns string between deliminations "<OUTPUT>" and "</OUTPUT>"
	char* output_string = delim_func(data_string, "<OUTPUT>", "</OUTPUT>");
	char* output_str = strtok(output_string, "\n=");

	//Tokens are used to input data from string into outval[j] by line or '=' delimination
	while (output_str != NULL)
	{
		sscanf(output_str, "%[^\n]s", &outval[i - 1][30]);
		output_str = strtok(NULL, "\n");
		i++;
	}

	//Initializing array variables
	char print_type[200] = "";
	char print_unit[200] = "";
	char print_val[200] = "";
	char fstr[12][15];

	//Lines from outval[2] contain an data output format
	for (int j = 2; j < 12; j++)
	{
		//Each output variable type is concatenated to form the output type string (print_type)
		if ((strstr(outval[j], "Vin")) != NULL) {
			strcat(print_type, "Vin, ");

			//If the variable is to be outputted as dB, it is concatenated to the print_unit string
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBV, ");

				//Converts float to string type for concatenation
				sprintf(fstr[j], "%g", outputdata.Vin[1]);
				
				//When output is in dB, the float for the dB variable type is concatenated to print_val
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "V, ");
				sprintf(fstr[j], "%g", outputdata.Vin[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Iin")) != NULL) {
			strcat(print_type, "Iin, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBI, ");
				sprintf(fstr[j], "%g", outputdata.Iin[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "I, ");
				sprintf(fstr[j], "%g", outputdata.Iin[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Pin")) != NULL) {
			strcat(print_type, "Pin, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBW, ");
				sprintf(fstr[j], "%g", outputdata.Pin[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "W, ");
				sprintf(fstr[j], "%g", outputdata.Pin[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Zin")) != NULL) {
			strcat(print_type, "Zin, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBOhm, ");
				sprintf(fstr[j], "%g", outputdata.Zin[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "Ohm, ");
				sprintf(fstr[j], "%g", outputdata.Zin[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Vout")) != NULL) {
			strcat(print_type, "Vout, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBV, ");
				sprintf(fstr[j], "%g", outputdata.Vout[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "V, ");
				sprintf(fstr[j], "%g", outputdata.Vout[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Iout")) != NULL) {
			strcat(print_type, "Iout, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBI, ");
				sprintf(fstr[j], "%g", outputdata.Iout[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "I, ");
				sprintf(fstr[j], "%g", outputdata.Iout[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Pout")) != NULL) {
			strcat(print_type, "Pout, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBW, ");
				sprintf(fstr[j], "%g", outputdata.Pout[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "W, ");
				sprintf(fstr[j], "%g", outputdata.Pout[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Zout")) != NULL) {
			strcat(print_type, "Zout, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dBOhm, ");
				sprintf(fstr[j], "%g", outputdata.Zout[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "Ohm, ");
				sprintf(fstr[j], "%g", outputdata.Zout[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Av")) != NULL) {
			strcat(print_type, "Av, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dB, ");
				sprintf(fstr[j], "%g", outputdata.Av[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "L, ");
				sprintf(fstr[j], "%g", outputdata.Av[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}

		}

		if ((strstr(outval[j], "Ai")) != NULL) {
			strcat(print_type, "Ai, ");
			if ((strstr(outval[j], "dB")) != NULL)
			{
				strcat(print_unit, "dB, ");
				sprintf(fstr[j], "%g", outputdata.Ai[1]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
			else
			{
				strcat(print_unit, "L, ");
				sprintf(fstr[j], "%g", outputdata.Ai[0]);
				strcat(fstr[j], ", ");
				strcat(print_val, fstr[j]);
			}
		}
	}

	//Output file stream is created and named from outval[1]
	char filename[30];
	sprintf(filename, "%s", outval[1]);
	FILE* output_file = fopen(filename, "w+");

	//Each print_xxx type string is outputted to the file
	fprintf(output_file, "%s\n", print_type);
	fprintf(output_file, "%s\n", print_unit);
	fprintf(output_file, "%s\n", print_val);

	// return(0);
}

