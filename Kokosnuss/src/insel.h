#ifndef _INSEL_H_
#define _INSEL_H_

#include "err.h"

typedef struct Time {
    int hour;
    int minute;
} Time;

typedef struct Insel {
    char* name;
    Time open;
    Time closed;
} Insel;

/*
    Tries to allocate a new Insel and set it to dst.

    This function will try to allocate a new Insel and set it to.
    All input parameters will be cloned.

    This function may return a KokosError:OutOfMemoryError if memory could
    not be allocated. In that case dst will be invalidated as NULL.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError insel_new(const char* name, Time open, Time closed, Insel** dst);

/*
    Try to free a heap allocated Insel.
    May fail if the insel ptr is a stack ptr.
    If insel is null, a KokosError:Nullpointer
    will be returned.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError insel_free(Insel* insel);

/*
    Displays the information held by insel.
    Will return a KokosError:NullPointerError if
    insel is a nullptr.

    If no error occurred, a KokosError:None will be returned.
*/
KokosError Output_Insel(const Insel* insel);

#endif