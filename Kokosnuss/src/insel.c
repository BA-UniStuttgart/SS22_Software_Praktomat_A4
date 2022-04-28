#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insel.h"

/*
    Tries to allocate a new Insel and set it to dst.
    All input parameters will be cloned.

    @name insel name
    @open open time
    @closed closed time
    @dst pointer where allocation result will be assigned to
    @return 1 if allocation failed, otherwise 0
*/
int insel_new(const char* name, Time open, Time closed, Insel** dst) {

    // Try allocating mem to hold one Insel
    Insel* insel = (Insel*)malloc(sizeof(Insel));

    // Sanity check
    if (!insel) {
        return 1;
    }
    
    /*
        + 1 because strlen ignores the null character
        and we want to copy the entire string, including
        the null character
    */
    size_t name_len = strlen(name) + 1;
    
    // Try allocate enough mem to hold 'name' including the null byte
    char* new_name = (char*)malloc(name_len * sizeof(char));

    // Sanity check
    if (!new_name) {
        // Release acquired mem
        free(insel);

        return 1;
    }

    // Copy name in the new buffer
    strcpy(new_name, name);

    // Assign
    insel->name = new_name;
    insel->open = open;
    insel->closed = closed;
    *dst = insel;

    return 0;
}

/*
    Tries to free a heap allocated Insel.
    If insel is a nullptr, this is a No-Op,
    thus this function will not fail.

    @insel the insel to be freed
*/
void insel_free(Insel* insel) {
    if (insel) {
        // Must be freed, since it was allocated on the heap
        free(insel->name);
        // Free the ptr itself
        free(insel);
    }
}

/*
    Displays the information held by insel.

    @insel the insel to display info for
    @return 1 if insel is a nullptr, otherwise 0
*/
int output_insel(const Insel * insel) {

    // Sanity check
    if (!insel) {
        return 1;
    }

    // Gather info from insel ptr
    char* insel_name = insel->name;
    int open_hour = insel->open.hour;
    int open_minute = insel->open.minute;
    int closed_hour = insel->closed.hour;
    int closed_minute = insel->closed.minute;

    // Display info
    printf("Insel        : %s\nÖffnungszeiten: %02d:%02d bis %02d:%02d",
        insel_name,
        open_hour,
        open_minute,
        closed_hour,
        closed_minute
    );

    return 0;

}
/*
    Tries to allocate a new Insel from a known InselType.
    All input parameters will be cloned.

    @type the insel type
    @dst pointer where allocation result will be assigned to
    @return the result of a call to 'insel_new'
*/
int insel_new_from(InselType type, Insel** dst) {

    const char* name;
    Time open;
    Time closed;
    
    switch (type) {
    case Amity:
        name = "Amity"; 
        open = (Time) { 9, 0 };
        closed = (Time) { 17, 0 };
        break;
    case Craggy:
        name = "Craggy";
        open = (Time) { 9, 0 };
        closed = (Time) { 16, 0 };
        break;
    case Isla_Nubar:
        name = "Isla Nubar";
        open = (Time) { 7, 0 };
        closed = (Time) { 12, 0 };
        break;
    case Shutter:
        name = "Shutter";
        open = (Time) { 8, 0 };
        closed = (Time) { 20, 0 };
        break;
    default: // Skull
        name = "Skull";
        open = (Time) { 8, 0 };
        closed = (Time) { 17, 30 };
        break;
    }

    return insel_new(name, open, closed, dst);
}