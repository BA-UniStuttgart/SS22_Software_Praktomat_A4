#include <stdlib.h>
#include "tour.h"
#include "util.h"

// Predefined InselTypes for each tour
static InselType _inseltypes_tour1[] = {Amity, Craggy, Isla_Nubar, Amity};
static InselType _inseltypes_tour2[] = { Skull, Craggy, Isla_Nubar, Skull };
static InselType _inseltypes_tour3[] = { Shutter, Skull, Shutter };
static InselType _inseltypes_tour4[] = { Isla_Nubar, Skull, Shutter, Amity, Isla_Nubar };

// Array of each tour with their corresponding insel types
static Tour _tours[] = {

    //Tour 1
    {
        .inseltypes = _inseltypes_tour1,
        .inselcount = SIZEOF(_inseltypes_tour1),
        .root = NULL
    },

    //Tour 2
    {
        .inseltypes = _inseltypes_tour2,
        .inselcount = SIZEOF(_inseltypes_tour2),
        .root = NULL
    },

    //Tour 3
    {
        .inseltypes = _inseltypes_tour3,
        .inselcount = SIZEOF(_inseltypes_tour3),
        .root = NULL
    },

    //Tour 4
    {
        .inseltypes = _inseltypes_tour4,
        .inselcount = SIZEOF(_inseltypes_tour4),
        .root = NULL
    }
};

// Holds all tours and a count; Available via extern keyword
TheTours theTours = {
    .tours = _tours,
    .tourcount = SIZEOF(_tours)
};