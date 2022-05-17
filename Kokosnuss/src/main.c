#include <stdio.h>
#include <stdlib.h>
#include "tour.h"

// Gets size of an array
#define SIZEOF(ARR) sizeof(ARR) / sizeof(ARR[0])

// Divider used for printing
const char* DIV = "---------------------------------------------------";

// Holds all tours. Defined in tour.c
extern TheTours theTours;

// Display an out of memory error
void _display_out_of_memory() {
    printf("Out of memory");
}

/*
    Performs setup of a tour.
    
    @tour the tour to be initialised.
    @return 1 if out of memory, 2 if tour is a nullptr, 0 otherwise
*/
int _setup_tour(Tour* tour) {

    // Sanity check
    if(!tour) {
        return 2;
    }

    // First create a new insel and initialise the root node
    Insel* insel;
    int alloc_err = insel_new_from(tour->inseltypes[0], &insel);

    // Check if allocation failed
    if(alloc_err) {
        _display_out_of_memory();
        return 1;
    }

    Node* new_node;
    alloc_err = node_new(insel, &(tour->root) );

    // Check if allocation failed. Release acquired insel on fail
    if(alloc_err) {
        _display_out_of_memory();
        insel_free(insel);
        return 1;
    }

    // Iterate over each inseltype and try pushing the rest
    InselType* start = tour->inseltypes + 1;
    InselType* end = tour->inseltypes + tour->inselcount;

    for(InselType* inseltype = start; inseltype != end; inseltype++) {
        
        Insel* insel;
        alloc_err = insel_new_from(*inseltype, &insel);

        // Check if allocation failed
        if(alloc_err) {
            _display_out_of_memory();
            return 1;
        }

        /* 
            Both root and insel are valid ptr, so the
            only errors returned are alloc errors
        */
        alloc_err = node_push_back_insel(tour->root, insel);

        // Check if allocation failed. Release all memory on fail
        if(alloc_err) {
            _display_out_of_memory();
            insel_free(insel);
            node_free(tour->root);
            return 1;
        }
    }

    return 0;
}

/*
    Initialiser function for all tours. 
    Returns 1 if error occurred, 0 otherwise
*/
int Setup_Tours() {

    // Iterate over each tour in theTours and initialise it
    Tour* start = theTours.tours;
    Tour* end = theTours.tours + theTours.tourcount;

    for(Tour* tour = start; tour != end; tour++) {

        int err = _setup_tour(tour);

        // Check for errors
        if(err) {
            return 1;
        }
    }

    return 0;
}

// Display a tour
void Output_Tour(const Tour* tour, int id) {

    printf("%s\n", DIV);
    printf("---------------- Tour %d ---------------------------\n", id);
    printf("%s\n%s\n", DIV, DIV);

    // Iterate over each node in tour and display the insel
    for (Node* iter = tour->root; iter != NULL; iter = iter->next) {
        output_insel(iter->insel);
        printf("\n%s\n", DIV);
    }

    printf("                         Ende \n");
}

// Release the memory held by each tour
void Cleanup_Tour() {
   // Iterate over each tour in theTours and free the root nodes
    Tour* start = theTours.tours;
    Tour* end = theTours.tours + theTours.tourcount;

    for(Tour* tour = start; tour != end; tour++) {
        node_free(tour->root);
    }
}

int main() {

    // Check if setup failed
    if (Setup_Tours()) {
        // Release memory
        Cleanup_Tour();
        return 1;
    }

    while(1) {
        // User operation request
        int op;
        printf("Bitte die Tour Nummer (1-4) eingeben oder mit 0 beenden: ");
        scanf("%d", &op);

        // If user operation is not in range 1..=4, break
        if(op > 4 || op == 0) {
            break;
        }
        
        // Output the tour
        int index = op - 1;
        Output_Tour(theTours.tours + index, op);
    }

    // Release memory
    Cleanup_Tour();

    return 0;
}