#ifndef DATASTRUCTS
#define DATASTRUCTS
#include <stdlib.h>

typedef struct{
    int* theArray;
    int length;
    int end;
} int_array;

/* appending value */
void appendValue(int i, int_array* ia) {
	if (ia->end == ia->length) {
		int* temp = malloc(sizeof(int)*(ia->length + 10));

		/* copying */
		int i;
		for (i = 0; i < ia->length; i++)
			temp[i] = ia->theArray[i];

		free(ia->theArray);
		ia->theArray = temp;
		ia->length += 10;
	}

	/* inserting another value */
	ia->theArray[ia->end++] = i;
}

int_array* dupArray(int_array* b) {
    int_array* a = malloc(sizeof(int_array));
    a->theArray = malloc(sizeof(int)*b->length);

    a->length = b->length;
    a->end = b->end;
    /* cloning array */
    int i;
    for (i = 0; i < a->length; ++i)
        a->theArray[i] = b->theArray[i];

    return a;
}


void freeArray(int_array* arr) {
    free(arr->theArray);
}

#endif
