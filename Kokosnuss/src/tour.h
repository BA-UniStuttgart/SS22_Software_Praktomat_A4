#ifndef _TOUR_H_
#define _TOUR_H_

#include "custom_node.h"

typedef struct Tour {
    const InselType* inseltypes;
    const int inselcount;
    Node* root;
} Tour;

typedef struct TheTours {
    const Tour* tours;
    const int tourcount;
} TheTours;

#endif