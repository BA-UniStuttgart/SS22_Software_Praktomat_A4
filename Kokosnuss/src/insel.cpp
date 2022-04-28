#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insel.h"
#include "err.h"

#pragma warning(disable : 4996)

/*
    Tries to allocate a new Insel and set it to dst.

    This function will try to allocate a new Insel and set it to.
    All input parameters will be cloned.

    This function may return a KokosError:OutOfMemoryError if memory could
    not be allocated. In that case dst will be invalidated as NULL.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError insel_new(const char* name, Time open, Time closed, Insel** dst) {

    // Try allocating mem to hold one Insel
    Insel* insel = (Insel*)malloc(sizeof(Insel));

    // Sanity check
    if (!insel) {
        // Invalidate dst
        *dst = NULL;

        return kokos_memory();
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
        // Otherwise, memory leak
        free(insel);

        // Invalidate dst
        *dst = NULL;

        return kokos_memory();
    }

    // Copy name in the new buffer
    strcpy(new_name, name);

    // Assign
    insel->name = new_name;
    insel->open = open;
    insel->closed = closed;
    *dst = insel;

    return kokos_noerr();
}

/*
    Try to free a heap allocated Insel.
    May fail if the insel ptr is a stack ptr.
    If insel is null, a KokosError:Nullpointer
    will be returned.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError insel_free(Insel* insel) {

    if (!insel) {
        return kokos_nullptr(1);
    }

    // Must be freed, since it was allocated on the heap
    free(insel->name);
    // Free the ptr itself
    free(insel);

    return kokos_noerr();
}

/*
    Displays the information held by insel.
    Will return a KokosError:NullPointerError if
    insel is a nullptr.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError Output_Insel(const Insel * insel) {

    // Sanity check
    if (!insel) {
        return kokos_nullptr(1);
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

    return kokos_noerr();

}