#ifndef _INSEL_H_
#define _INSEL_H_

typedef struct Time {
    int hour;
    int minute;
} Time;

typedef struct Insel {
    char* name;
    Time open;
    Time closed;
} Insel;

typedef enum InselType {
    Amity,
    Craggy,
    Isla_Nubar,
    Shutter,
    Skull
} InselType;

int insel_new(const char* name, Time open, Time closed, Insel** dst);
void insel_free(Insel* insel);
int output_insel(const Insel* insel);
int insel_new_from(InselType type, Insel** dst);

#endif