#ifndef _TOUR_H_
#define _TOUR_H_

#include "custom_node.h"

typedef struct Tour {
    InselType* inseltypes;
    int inselcount;
    Node* root;
} Tour;

typedef struct TheTours {
    Tour* tours;
    int tourcount;
} TheTours;

#endif