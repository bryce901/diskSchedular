#include "algorithms.h"
#include "runSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/* this will make an array of functions*/
typedef int (*func_array) (int, int_array*);

int main(int argc, char const *argv[]) {
    /* all of the algorithms that have been implimented */
    func_array functions[] = {firstComeFirstServe, shortestSeekTimeFirst, SCAN, CSCAN, LOOK, CLOOK};
    /* algorithm names */
    char* names[] = {"firstComeFirstServe", "shortestSeekTimeFirst", "SCAN", "C-SCAN", "LOOK", "C-LOOK"};

    /* checking inputs */
    if(argc != 3) {
        printf("Wrong usage. Refer to the README");
        return -1;
    }
    else if ((atoi(argv[1]) < minValue) ||(atoi(argv[1]) > maxValue)) {
        printf("Wrong usage. Refer to the README");
        return -1;
    }

    
    FILE* theFile = fopen(argv[2], "r");

    if(theFile == NULL) {
        printf("Argument %s must be between a valid filepath\n", argv[2]);
        return -1;
    }

    int_array theRequests;
    readFile(theFile, &theRequests);
    fclose(theFile);

    /* running the algorithms */
    int i;
    for (i = 0; i < 6; ++i)
        printf("Total movement for %s:\t%08d\n", names[i], functions[i](atoi(argv[1]), &theRequests));

    freeArray(&theRequests);
    return 0;
}
