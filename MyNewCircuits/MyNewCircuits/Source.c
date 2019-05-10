#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include "skippcommnet.c"


//Functions declaration - helps the compiler to know the function name and the data type of the function
//expected. It also shows the parameters that the function will take (if any...)
void readWholeFile(); //This is a function that opens and read the whole file character by character, it then prints the output on the screen...
void assignValuesFromFile();
void printValues();
void sortValues();
void calculateS_PValues();
void calculateOutput();
void getABCDValues();
void makeMatrices();
void readOutputFileName();
void convertRStoGS();

//All global variables are declared some initialized here....
char dataFile[3000];
int counter = 0;
char findChar[] = "n1";
int charPos;
char resistance_mem[9];
int resistance_mem_p = 0;
float resistance[9];
int resistance_p = 0;
char node_one_mem[9];
int node_one_mem_p = 0;
int node_one[9];
int node_one_p = 0;
char node_two_mem[9];
int node_two_mem_p = 0;
int node_two[9];
int node_two_p = 0;
char vt_mem[9];
int vt_mem_p = 0;
int vt[5];
int vt_p = 0;
char rs_mem[9];
int rs_mem_p = 0;
float rs[10];
float nrs[10];
int rs_p = 0;
char rl_mem[9];
int rl_mem_p = 0;
int rl[5];
int rl_p = 0;
float Zl, Zs, Zin, Av, Ai, T, Zout, A, B, C, D, Pin, Pout, Iin, Iout, Vin, Vs, Vout;
float tx[4][4];
int cr = 0;
float nw_tx[9][9];
int mt_c = 0;

int node_c;
float r_nw[10];
int node_app[9];

char fn_mem[30];
int fn_mem_p = 0;
char fn[100];
int fn_p = 0;

char nn1[10];
char nn2[10];
// Program's main function where all other functions are called....
int main(void) {
	readWholeFile(); //work
	readOutputFileName();
	assignValuesFromFile(); //work
	calculateS_PValues();
	convertRStoGS();
	sortValues();
	printValues(); //work
	makeMatrices();
	getABCDValues();
	calculateOutput();
	getchar();
}
//Function definition to read entire .dat file...
void readWholeFile() {
	FILE *fp = fopen("E:/Circuits/Netlist_06pa.dat", "r");
	// Return if could not open file
	if (fp == NULL) {
		printf("File not found\n");
		return 1;
	}
	char line[100000];
	while (fgets(line, sizeof(line), fp) != NULL) {
		char *hash = strchr(line, '#'); // find the first occurrence of # in a line
		if (hash != NULL) {
			*hash = '\0';
		}else{
			do{
				//Taking input single character at a time
				char c = fgetc(fp);
				dataFile[charPos] = c;
				charPos++;
				// Checking for end of file
				if (feof(fp))
					break;
				printf("%c", c);
			} while (1);
		}
	}
	fclose(fp);
}
// This function locates and picks values from the file, then store them in their respective variables...
void assignValuesFromFile() {
	counter;
	counter = count_apps(dataFile, findChar);
	printf("Counter : %d", counter);
	printf("\n");
	int e_p = charPos - 2;
	charPos = 0;

	while (charPos < e_p) {

		if (dataFile[charPos] == 'R' && dataFile[charPos + 1] == '=') {
			charPos += 2;

			while (isdigit(dataFile[charPos])) {
				resistance_mem[resistance_mem_p] = dataFile[charPos];
				resistance_mem_p++;
				charPos++;
			}
			resistance[resistance_p] = atof(resistance_mem);
			//	printf("R values = %d\n", resistance[resistance_p]); // Print R values - Testing purposes
			memset(resistance_mem, 0, sizeof(resistance_mem));
			resistance_mem_p = 0;
			resistance_p++;
		}
		else if (dataFile[charPos] == 'G' && dataFile[charPos + 1] == '=') {
			charPos += 2;

			while (dataFile[charPos] && dataFile[charPos] != '\n') {
				resistance_mem[resistance_mem_p] = dataFile[charPos];
				resistance_mem_p++;
				charPos++;
			}
			resistance[resistance_p] = atof(resistance_mem);
			printf("G = %.5f\n", resistance[resistance_p]); // Print R values - Testing purposes
			memset(resistance_mem, 0, sizeof(resistance_mem));
			resistance_mem_p = 0;
			resistance_p++;
		}
		else if (dataFile[charPos] == 'n' && dataFile[charPos + 1] == '1' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			printf("node 1 = %c", dataFile[charPos]);
			nn1[counter] = dataFile[charPos];
			while (isdigit(dataFile[charPos])) {
				node_one_mem[node_one_mem_p] = dataFile[charPos];
				node_one_mem_p++;
				charPos++;
			}
			node_one[node_one_p] = atoi(node_one_mem);
			//	printf("N1 values = %d\n", node_one[node_one_p]); //Print Node 1 values - Testing.....
			memset(node_one_mem, 0, sizeof(node_one_mem));
			node_one_mem_p = 0;

			node_one_p++;
		}
		else if (dataFile[charPos] == 'n' && dataFile[charPos + 1] == '2' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			nn2[counter] = dataFile[charPos];
			//printf("%c", dataFile[charPos + 2]); // debugging
			while (isdigit(dataFile[charPos])) {
				//printf("%c", dataFile[charPos]); // debugging
				node_two_mem[node_two_mem_p] = dataFile[charPos];
				node_two_mem_p++;
				charPos++;
			}
			node_two[node_two_p] = atoi(node_two_mem);
			//printf("N2 values = %d\n", node_two[node_two_p]); //debugging.....
			memset(node_two_mem, 0, sizeof(node_two_mem));
			node_two_mem_p = 0;

			//printf("%d\n", node_one[node_one_p]); // debugging

			node_two_p++;
		}
		else if (dataFile[charPos] == 'V' && dataFile[charPos + 1] == 'T' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			//printf("%c", dataFile[charPos + 2]); // debugging
			while (isdigit(dataFile[charPos])) {
				//printf("%c", dataFile[charPos]); // debugging
				vt_mem[vt_mem_p] = dataFile[charPos];
				vt_mem_p++;
				charPos++;
			}
			vt[vt_p] = atoi(vt_mem);
			//printf("VT values = %d\n", vt[vt_p]); //debugging.....
			memset(vt_mem, 0, sizeof(vt_mem));
			vt_mem_p = 0;

			vt_p++;
		}
		else if (dataFile[charPos] == 'R' && dataFile[charPos + 1] == 'S' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			//printf("%c", dataFile[charPos + 2]); // debugging
			while (isdigit(dataFile[charPos])) {
				//printf("%c", dataFile[charPos]); // debugging
				rs_mem[rs_mem_p] = dataFile[charPos];
				rs_mem_p++;
				charPos++;
			}
			rs[rs_p] = atoi(rs_mem);
			//printf("RS values = %d\n", rs[rs_p]); //debugging.....
			memset(rs_mem, 0, sizeof(rs_mem));
			rs_mem_p = 0;

			//printf("%d\n", node_one[node_one_p]); // debugging

			rs_p++;
		}
		else if (dataFile[charPos] == 'G' && dataFile[charPos + 1] == 'S' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			//printf("%c", dataFile[charPos + 2]); // debugging
			while (dataFile[charPos] && dataFile[charPos] != '\n') {
				//printf("%c", dataFile[charPos]); // debugging
				rs_mem[rs_mem_p] = dataFile[charPos];
				rs_mem_p++;
				charPos++;
			}
			rs[rs_p] = atof(rs_mem);
			//printf("RS values = %d\n", rs[rs_p]); //debugging.....
			memset(rs_mem, 0, sizeof(rs_mem));
			rs_mem_p = 0;

			//printf("%d\n", node_one[node_one_p]); // debugging

			rs_p++;
		}
		else if (dataFile[charPos] == 'R' && dataFile[charPos + 1] == 'L' && dataFile[charPos + 2] == '=') {
			charPos += 3;
			//printf("%c", dataFile[charPos + 2]); // debugging
			while (isdigit(dataFile[charPos])) {
				//printf("%c", dataFile[charPos]); // debugging
				rl_mem[rl_mem_p] = dataFile[charPos];
				rl_mem_p++;
				charPos++;
			}
			rl[rl_p] = atoi(rl_mem);
			//printf("RL values = %d\n", rl[rl_p]); //debugging.....
			memset(rl_mem, 0, sizeof(rl_mem));
			rl_mem_p = 0;
			rl_p++;
		}

		charPos++;
	}
}
void readOutputFileName() {
	counter;
	counter = count_apps(dataFile, findChar);
	printf("\n");
	int e_p = charPos - 2;
	charPos = 0;

	while (charPos < e_p) {
		if (dataFile[charPos] == 'F' && dataFile[charPos + 1] == 'i' && dataFile[charPos + 2] == 'l' && dataFile[charPos + 3] == 'e' && dataFile[charPos + 4] == '_' && dataFile[charPos + 5] == 'n' && dataFile[charPos + 6] == 'a' && dataFile[charPos + 7] == 'm' && dataFile[charPos + 8] == 'e' && dataFile[charPos + 9] == '=') {
			charPos += 10;
			while ((dataFile[charPos]) && dataFile[charPos] != '\n') {
				//printf("Output File name\n");

				fn_mem[fn_mem_p] = dataFile[charPos];
				printf("%c", fn_mem[fn_mem_p]); // debugging!
				strncat(fn, &fn_mem[fn_mem_p], 1);

				charPos++;
			}
		}
		charPos++;
	}

}
void printValues() { // display R, N1 and N2 values
	int i;

	for (i = 0; i < counter; i++) {
		printf("R[%d]:\t %.5f\n", i, resistance[i]);
		printf("N1[%d]:\t %d\n", i, node_one[i]);
		printf("N2[%d]:\t %d\n", i, node_two[i]);

		printf("nn1 = %c\n", nn1[i]);
		printf("nn2 = %c\n", nn2[i]);

	}
	printf("VT: %d\n", vt[0]);
	printf("RS: %.5f\n", nrs[0]);
	printf("RL: %d\n", rl[0]);
}

void calculateS_PValues() {
	node_c = 0;
	//	printf("Counter_2: %d\n", counter); // for testing...
	while (node_c <= counter) {

		if (node_two[node_c] != 0) { // Checking whether a node is in series.....

			if (resistance[node_c] > 1) {// The value given is an R value or must be an R value
				r_nw[node_c] = (float)resistance[node_c]; // Picks the value of R as it is
				node_app[node_c] = 0; // sets the m[i][j]th matrix element to 0
			}
			else {
				r_nw[node_c] = (1 / (float)resistance[node_c]); // Calculates G = 1/R
				node_app[node_c] = 0; // sets the m[i][j]th matrix element to 0
			}
		}
		else if (node_two[node_c] == 0) {// Checks whether the node is in shunt.

			if (resistance[node_c] > 1) {// Checks whether the value provided is R or G i.e R > 1 and G < 1
				r_nw[node_c] = (1 / (float)resistance[node_c]); // If R is found then G is calculated as R/1
				node_app[node_c] = 1; // sets the m[i][j]th matrix element to 1
			}
			else {
				r_nw[node_c] = (float)resistance[node_c]; // If G is found then it is saved as it is...
				node_app[node_c] = 1; // sets the m[i][j]th matrix element to 1
			}
		}

		node_c++;
	}

	int i;
	for (i = 0; i < counter; i++) {
		printf("R[%d]: %.5f\n", i, r_nw[i]); // Prints out the values of R from new arrangement above...
		printf("R nodes[%d]: %d\n", i, node_app[i]);
	}
}
void convertRStoGS() {

		if(rs[0] >= 1) {
			nrs[0] = (float)rs[0];
		}
		else{
			nrs[0] = 1/(float)rs[0];
		}

	printf("Value of Counter= %d\n", counter);
	printf("Value of RS with rs = %.5f\n", rs[0]);
	printf("Value of RS with nrs= %.5f\n", nrs[0]);
}
void sortValues() {
	int i, j;
	int temp;
	int temp0;
	float temp1;
	int n2[10];

	printf("Before Sorting\n");
	for (i = 0; i < counter; i++)
	{
		printf("%d\t%d\t%.5f\n", node_one[i], node_two[i], r_nw[i]);
	}

	for (i = 0; i < counter; i++) {
		for (j = 0; j < (counter - i - 1); j++) {
			if (node_one[j] > node_one[j + 1]) {
				temp = node_one[j];
				temp0 = node_two[j];
				temp1 = r_nw[j];

				node_one[j] = node_one[j + 1];
				node_two[j] = node_two[j + 1];
				r_nw[j] = r_nw[j + 1];

				node_one[j + 1] = temp;
				node_two[j + 1] = temp0;
				r_nw[j + 1] = temp1;
			}
		}
	}

	printf("After Sorting\n");
	for (i = 0; i < counter; i++)
	{
		printf("%d\t%d\t%.5f\n", node_one[i], node_two[i], r_nw[i]);
	}

}

void makeMatrices() {
	while (cr <= counter) {
		if (node_app[cr] == 1) {
			tx[cr][0] = (float)1;
			tx[cr][1] = (float)0;
			tx[cr][2] = r_nw[cr];
			tx[cr][3] = (float)1;
		}
		else if (node_app[cr] == 0) {
			tx[cr][0] = (float)1;
			tx[cr][1] = r_nw[cr];
			tx[cr][2] = (float)0;
			tx[cr][3] = (float)1;
		}
		cr++;
	}
	int i; //row and column
	for (i = 0; i < counter; i++) {
		printf("Matrix[%d] = %f\t%f\t%f\t%f\n", i, tx[i][0], tx[i][1], tx[i][2], tx[i][3]);
	}
}

void getABCDValues(){

	nw_tx[0][0] = (tx[0][0] * tx[1][0]) + (tx[0][1] * tx[1][2]);
	nw_tx[0][1] = (tx[0][0] * tx[1][1]) + (tx[0][1] * tx[1][3]);
	nw_tx[0][2] = (tx[0][2] * tx[1][0]) + (tx[0][3] * tx[1][2]);
	nw_tx[0][3] = (tx[0][2] * tx[1][1]) + (tx[0][3] * tx[1][3]);

	while (mt_c < counter - 1) {
		nw_tx[mt_c + 1][0] = (nw_tx[mt_c][0] * tx[mt_c + 2][0]) + (nw_tx[mt_c][1] * tx[mt_c + 2][2]);
		nw_tx[mt_c + 1][1] = (nw_tx[mt_c][0] * tx[mt_c + 2][1]) + (nw_tx[mt_c][1] * tx[mt_c + 2][3]);
		nw_tx[mt_c + 1][2] = (nw_tx[mt_c][2] * tx[mt_c + 2][0]) + (nw_tx[mt_c][3] * tx[mt_c + 2][2]);
		nw_tx[mt_c + 1][3] = (nw_tx[mt_c][2] * tx[mt_c + 2][1]) + (nw_tx[mt_c][3] * tx[mt_c + 2][3]);

		mt_c = mt_c + 1;
	}
	for (int i = 0; i < counter; i++) {
		printf("nw_tx %d: %f\t%f\t%f\t%f\n", i, nw_tx[i][0], nw_tx[i][1], nw_tx[i][2], nw_tx[i][3]);//working...
		//printf("mt_cVal 3 : %d\n", counter);
	}
	A = nw_tx[mt_c - 1][0];
	B = nw_tx[mt_c - 1][1];
	C = nw_tx[mt_c - 1][2];
	D = nw_tx[mt_c - 1][3];

	printf("mt_cVal : %d\n", mt_c);
	printf("A = %.4f  B = %.4f  \nC = %.4f  D = %.4f\n", A, B, C, D);
}

void calculateOutput() {
	float Vout1, Ai1;
	Zl = rl[0];
	Zs = rs[0];
	Vs = vt[0];
	Zin = ((A*Zl + B) / (C*Zl + D));
	Vin = ((Vs*Zin)) / (Zs + Zin);
	Iin = Vs / (Zs + Zin);
	Pin = 10 * log((Vin * Iin));
	Av = (1 / (A + (B / Zl)));
	Vout = 1 / ((C*Zl) + D);
	Vout1 = 20 * log10((Vin * Av));
	Ai = (1 / (C*Zl) + D);
	Ai1 = 10 * log((1 / (C*Zl) + D));
	Iout = (Iin * Ai);
	Pout = 10 * log(Vout * Iout);
	T = (2 / A * Zl + B + C * Zl*Zs + D * Zs);
	Zout = (((D*Zs) + B) / ((C*Zs) + A));

	FILE *fp;
	char file_location[100];

	strcpy(file_location, "E:/Circuits/");

	char get_file = strcat(file_location, fn);
	printf("The name of the file location: %s\n", file_location);
	printf("The name of the file is: %s\n", fn);

	fp = fopen(file_location, "w+");
	//fprintf(fp, "Zin=%.2f\nAv=%.2f\nAi=%.2f\nTransmittance=%.2f\nZout=%.2f\n", Zin, Av, Ai, T, Zout);
	fprintf(fp, "Vin, \tVout, \tIin, \tIout, \tPin, \tZout, \tPout, \tZin, \tAv, \tAi\n");
	fprintf(fp, "V, \tdBV, \tI, \tI, \tdBW, \tOhm, \tdBW, \tOhm, \tL, \tdB\n");
	fprintf(fp, "%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e,\t%.4e\n", Vin, Vout1, Iin, Iout, Pin, Zout, Pout, Zin, Av, Ai1);
	fclose(fp);
}



int count_apps(char *fp, char *findChar)
{
	int count = 0;
	int i;

	for (i = 0; fp[i] != '\0'; i++)
	{
		int j;
		for (j = 0; findChar[j] != '\0' && findChar[j] == fp[i + j]; j++)
			;
		if (findChar[j] == '\0')
			count++;
	}
	return count;
}

