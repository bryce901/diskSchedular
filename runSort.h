#ifndef RUNSORT
#define RUNSORT
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "dataStructs.h"

/* reads the contents of a file into a vector */
void readFile(FILE* theFile, int_array *requests) {
    int ret, value;
	requests->length = 0;

    /* getting length of file */
    while(1) {
        ret = fscanf(theFile, "%d", &value);

        if(ret == 1) ++requests->length;
        else if(errno != 0) {
            perror("ERROR: Can't read file: ");
            exit(-1);
        } else if(ret == EOF) break;
    }

    rewind(theFile);

    requests->theArray = malloc(sizeof(int)*requests->length);
    requests->length=0;

    while(1) {
        ret = fscanf(theFile, "%d", &value);

        /* saving file data */
        if(ret == 1)
            requests->theArray[requests->length++] = value;
        else if(errno != 0) {
            perror("ERROR: Can't read file: ");
            exit(-1);
        } else if(ret == EOF) break;
    }

    requests->end = requests->length;
}

/* sorts array numerically or reverse numerically */
void sortArray(int_array* ia, int theDirection) {
    /* sort the list */
    int x, y;

    /* bubble sort */
    for (x = 0; x < ia->end-1; x++) {
        for (y = 0; y < ia->end-x-1; y++) {
            if(theDirection == 1) {
                if (ia->theArray[y] > ia->theArray[y+1]) {
                    int p = ia->theArray[y];
                    ia->theArray[y] = ia->theArray[y+1];
                    ia->theArray[y+1] = p;
                }
            }
            else {
                if (ia->theArray[y] < ia->theArray[y+1]) {
                    int p = ia->theArray[y];
                    ia->theArray[y] = ia->theArray[y+1];
                    ia->theArray[y+1] = p;
                }
            }

        }
    }
}

#endif
