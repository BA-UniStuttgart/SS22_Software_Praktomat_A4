#ifndef _UTIL_H_
#define _UTIL_H_

// Gets size of an array
#define SIZEOF(ARR) sizeof(ARR) / sizeof(ARR[0])

/*
    Iterates over a collection by address.

    @TARGET     Iteration Target; E.g int* if the collection is an array of integers
    @NAME       Name of the iterator
    @COLL       The collection to iterate over
    @SIZE       The size of the collection
    @LAMBDA     The expression to execute for each element
*/
#define FOR_EACH(TARGET, NAME, COLL, SIZE, LAMBDA) for(TARGET NAME = COLL; NAME != COLL + SIZE; NAME++) LAMBDA

#endif