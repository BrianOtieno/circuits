// #include "../CircuitAnalysis/comments.h"
#include "../CircuitAnalysis/openfile.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void matrix_test();


int main(int argc, char const *argv[])
{
    assert( true && "My first unit test"); 
    matrix_test();
}


void matrix_test(){
    struct stat st = {0};

    if (stat("../Data", &st) == -1) {
        mkdir("../Data", 0700);
        printf("Directory created");
 

    char* data_string = open_file();
	printf("The following Data was inputted:\n %s\n", data_string);



    }
    
} 