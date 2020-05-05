
#ifndef DEBUGGING_CODE
#define DEBUGGING_CODE

#include "algorithms.h"

void print_int_array(int_array* ia) {
    int n;
    for (n = 0; n < ia->end; n++) {
        printf("%d, ", ia->theArray[n]);
    }
    printf("\n");
}

#endif
