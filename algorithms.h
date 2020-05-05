#ifndef ALGORITHMS
#define ALGORITHMS

#include "dataStructs.h"
#include "runSort.h"
#include <stdio.h>
#include <stdlib.h>


#define theLeft -1
#define theRight 1
#define maxValue 4999
#define minValue 0


int firstComeFirstServe(int startPosition, int_array* requests) {
    
    if(requests->length == 0) return 0;

    /* finding the first request */
    int sum = abs(startPosition-requests->theArray[0]);

    /* find the distance between other requests */
    int x;
    for (x = 0; x < requests->length-1; x++)
        sum += abs(requests->theArray[x]-requests->theArray[x+1]);

    return sum;
}


int shortestSeekTimeFirst(int startPosition, int_array* requests) {
    /* copy value */
    int_array *ord_req = dupArray(requests);

    sortArray(ord_req, 1);
    int index = 0;
    while(ord_req->theArray[index] < startPosition) ++index;

    /* numbers to compare are right and left */
    int right, left;
    if(ord_req->theArray[index] == startPosition) {
        right = index+1;
        left = index-1;
    }

    else {
        right = index;
        left = index-1;
    }
    /* finds request that is closest */
    int rightDelta, leftDelta, sum = 0;
    while(1) {
        rightDelta = abs(ord_req->theArray[right]-ord_req->theArray[index]);
        leftDelta = abs(ord_req->theArray[left]-ord_req->theArray[index]);

        /* trying left because it is shorter */
        if((rightDelta > leftDelta) && left > -1) {
            sum += leftDelta;
            index = left--;
        }
        /* vise versa */
        else if(right < ord_req->length) {
            sum += rightDelta;
            index = right++;
        }
        else break;
    }

    freeArray(ord_req);
    free(ord_req);
    return sum;
}


int baseScan(int startPosition, int_array* requests, int circular, int look) {
    int_array left, right;

    left.theArray = malloc(sizeof(int)*10);
    right.theArray = malloc(sizeof(int)*10);

    /* initializing */
    left.length = 10;
    right.length = 10;
    left.end = 0;
    right.end = 0;

    /* direction on the disk */
    int theDirection=0;

    /* finding starting position */
    int x;
    /* cycle thru requests */
    for (x = 0; x < requests->length; ++x) {

        if(requests->theArray[x] != startPosition) {

            /* finds which direction to go in */
            if(requests->theArray[x] > startPosition) theDirection = theRight;
            else theDirection = theLeft;
            break;
        }
    }

    
	/* now we have to go to the edge of the disk in order to change directions back*/
    if(look != 1) {
        if(circular == 1) {
            appendValue(minValue, &left);
            appendValue(maxValue, &right);
        }
        else {
            if (theDirection == theLeft) appendValue(minValue, &left);
            else if (theDirection == theRight) appendValue(maxValue, &right);
        }
    }

    /* requests for the vectors */
    for (x = 0; x < requests->length; x++) {
        if (requests->theArray[x] < startPosition)
            appendValue(requests->theArray[x], &left);
        if (requests->theArray[x] > startPosition)
            appendValue(requests->theArray[x], &right);
    }

    /* the arrays are sorted in the direction it will be headed in */
    if(circular == 1) {
        sortArray(&left, theDirection);
        sortArray(&right, theDirection);
    }

    else {
        sortArray(&left, -1);
        sortArray(&right, 1);
    }

    int sum= 0;
    
    for(x = theRight; x > -2; x-=2) {
        /* right sum */
        if(theDirection == theRight) {
            int k;
            for (k = 0; k < right.end; ++k) {
                sum += abs(startPosition-right.theArray[k]);
                startPosition = right.theArray[k];
            }
            theDirection = theLeft;
        }
        /* left sum */
        else if(theDirection == theLeft) {
            int k;
            for (k = 0; k < left.end; ++k) {
                sum += abs(startPosition-left.theArray[k]);
                startPosition = left.theArray[k];
            }
            theDirection = theRight;
        }
    }

    freeArray(&right);
    freeArray(&left);
    return sum;
}

/*LOOK algorithm */
int LOOK(int startPosition, int_array* requests) {
	return baseScan(startPosition, requests, 0, 1);
}

/* performs the C-LOOK algorithm */
int CLOOK(int startPosition, int_array* requests) {
	return baseScan(startPosition, requests, 1, 1);
}

/*C-SCAN algorithm */
int CSCAN(int startPosition, int_array* requests) {
    return baseScan(startPosition, requests, 1, 0);
}

/*SCAN algorithm */
int SCAN(int startPosition, int_array* requests) {
	return baseScan(startPosition, requests, 0, 0);
}

#endif
