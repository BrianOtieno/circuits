#include "../CircuitAnalysis/openfile.h"

#include <assert.h>
#include <stdbool.h>




int main(int argc, char const *argv[])
{
    // assert(false && "Intended failure");

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

}


