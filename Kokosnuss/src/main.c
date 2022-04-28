#include <stdio.h>
#include <stdlib.h>
#include "node.h"

// Gets size of an array
#define SIZEOF(ARR) sizeof(ARR) / sizeof(ARR[0])

// Divider used for printing
const char* DIV = "---------------------------------------------------";

typedef Node Tour;
// The available tours
Tour* tour1;
Tour* tour2;
Tour* tour3;
Tour* tour4;

// Display an out of memory error
void _display_out_of_memory() {
    printf("Out of memory");
}

/*
    Frees all insel ptrs in inseln
    
    @inseln the inseln to free
    @count number of elements to free
*/
void _free_inseln(Insel** inseln, int count) {
    for (int i = 0; i < count; i++) {
        insel_free(inseln[i]);
    }
}

/*
    Allocates Inseln from a list of insel types.

    @types array of insel types
    @into pointer to an array where the allocated 
        inseln will be assigned into
    @count number of types in types
    @return 1 if allocation fails, 0 otherwise
*/
int _bulk_alloc_insel(InselType* types, Insel** into, int count) {

    // Try allocating 'count' inseln, return 1 if allocation fails
    for (int i = 0; i < count; i++) {
        int alloc_err = insel_new_from(types[i], into + i);

        if (alloc_err) {
            _free_inseln(into, count);
            return 1;
        }
    }

    return 0;
}

/*
    Initialises a tour from an array of valid insel pointers.

    @tour the tour to initialise
    @inseln the inseln which will be assigned into tour
    @count the number of elements in inseln
    @return 1 if allocation fails, 0 otherwise
*/
int _init_tour(Tour** tour, Insel** inseln, int count) {

    // Alloc the root node
    int alloc_err = node_new(inseln[0], tour);

    // Check for alloc error
    if (alloc_err) {
        _display_out_of_memory();

        // Release inseln, since they're valid ptrs
        _free_inseln(inseln, count);
        return 1;
    }

    // Try pushing the remaining inseln into the root node
    // Return if alloc error occurs
    for (int i = 1; i < count; i++) {
        alloc_err = node_push_back_insel(*tour, inseln[i]);

        // Check for alloc error
        if (alloc_err) {
            _display_out_of_memory();

            // Free both the remaining unpushed inseln
            // as well as the nodes which have already
            // been successfully allocated
            _free_inseln(inseln, count);
            node_free(*tour);
            return 1;
        }
    }

    return 0;
}

// Setzp function for tour1
int _setup_tour1() {
    // Types of inseln to allocate
    InselType types[] = {Amity, Craggy, Isla_Nubar, Amity};

    // Array where the successfully allocated inseln will be stored
    Insel* inseln[] = { NULL, NULL, NULL, NULL };
    int num_inseln = SIZEOF(types);

    Tour** tour = &tour1;

    // Try allocating all inseln, if fails display error and return
    if (_bulk_alloc_insel(types, inseln, num_inseln)) {
        _display_out_of_memory();
        return 1;
    }

    // Initialise the tour with the previously acquired inseln
    return _init_tour(tour, inseln, num_inseln);
}

// For Doc, see _setup_tour1, since they only differ in the 'types' array
int _setup_tour2() {
    InselType types[] = { Skull, Craggy, Isla_Nubar, Skull };
    Insel* inseln[] = { NULL, NULL, NULL, NULL };
    int num_inseln = SIZEOF(types);
    Tour** tour = &tour2;

    if (_bulk_alloc_insel(types, inseln, num_inseln)) {
        _display_out_of_memory();
        return 1;
    }

    return _init_tour(tour, inseln, num_inseln);
}

// For Doc, see _setup_tour1, since they only differ in the 'types' array
int _setup_tour3() {
    InselType types[] = { Shutter, Skull, Shutter };
    Insel* inseln[] = { NULL, NULL, NULL };
    int num_inseln = SIZEOF(types);
    Tour** tour = &tour3;

    if (_bulk_alloc_insel(types, inseln, num_inseln)) {
        _display_out_of_memory();
        return 1;
    }

    return _init_tour(tour, inseln, num_inseln);
}

// For Doc, see _setup_tour1, since they only differ in the 'types' array
int _setup_tour4() {
    InselType types[] = { Isla_Nubar, Skull, Shutter, Amity, Isla_Nubar };
    Insel* inseln[] = { NULL, NULL, NULL, NULL, NULL };
    int num_inseln = SIZEOF(types);
    Tour** tour = &tour4;

    if (_bulk_alloc_insel(types, inseln, num_inseln)) {
        _display_out_of_memory();
        return 1;
    }

    return _init_tour(tour, inseln, num_inseln);
}

// Initialiser function for all tours
int Setup_Tour() {
    int err = 0;
    err |= _setup_tour1();
    err |= _setup_tour2();
    err |= _setup_tour3();
    err |= _setup_tour4();

    return err;
}

// Display a tour
void Output_Tour(const Tour* tour, int id) {

    printf("%s\n", DIV);
    printf("---------------- Tour %d ---------------------------\n", id);
    printf("%s\n%s\n", DIV, DIV);

    // Iterate over each node in tour and display the insel
    for (const Tour* iter = tour; iter != NULL; iter = iter->next) {
        output_insel(iter->insel);
        printf("\n%s\n", DIV);
    }

    printf("                         Ende \n");
}

// Release the memory held by each tour
void Cleanup_Tour() {
    node_free(tour1);
    node_free(tour2);
    node_free(tour3);
    node_free(tour4);
}

int main() {

    // Check if setup failed
    if (Setup_Tour()) {
        // Release memory
        Cleanup_Tour();
        return 1;
    }

    // User operation request
    int op;
    printf("Bitte die Tour Nummer (1-4) eingeben oder mit 0 beenden: ");
    scanf("%d", &op);

    // Output a tour based on 'op'
    switch (op) {
    case 1:
        Output_Tour(tour1, op);
        break;
    case 2:
        Output_Tour(tour2, op);
        break;
    case 3:
        Output_Tour(tour3, op);
        break;
    case 4:
        Output_Tour(tour4, op);
        break;
    default:
        break;
    };

    // Release memory
    Cleanup_Tour();

    return 0;
}