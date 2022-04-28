#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#pragma warning(disable : 4996)

const char* DIV = "---------------------------------------------------";

typedef Node Tour;
Tour* tour1;
Tour* tour2;
Tour* tour3;
Tour* tour4;

void handle_out_of_memory() {
    printf("Out of memory");
}

#define STRINGIFY(s) #s
#define INSEL_WORKFLOW(FN, NAME, OH, OM, CH, CM) int _new_insel_##FN(Insel** dst) { Insel* insel; const char* name = STRINGIFY(NAME); \
KokosError err = insel_new(name, {OH, OM} , {CH, CM}, &insel); \
if (kokos_has_error(&err)) { handle_out_of_memory(); return 1; } \
*dst = insel; return 0; \
}

INSEL_WORKFLOW(amity, Amity, 9,0 , 17,0)
INSEL_WORKFLOW(craggy, Craggy, 9,0 , 16,0)
INSEL_WORKFLOW(nubar, Isla Nubar, 7,0, 12,0)
INSEL_WORKFLOW(shutter, Shutter, 8,0, 20,0)
INSEL_WORKFLOW(skull, Skull, 8,0, 17,30)

void _free_inseln(Insel** inseln, int size) {
    for (int i = 0; i < size; i++) {
        insel_free(inseln[i]);
    }
}

int _setup_tour1() {
    Insel* inseln[4];
    int num_inseln = 4;
    Tour** tour = &tour1;

    int err = 0;
    err |= _new_insel_amity(&inseln[0]);
    err |= _new_insel_craggy(&inseln[1]);
    err |= _new_insel_nubar(&inseln[2]);
    err |= _new_insel_amity(&inseln[3]);

    if (err) {
        _free_inseln(inseln, num_inseln);
        return err;
    }

    KokosError alloc_err = node_new(inseln[0], tour);
    if (kokos_has_error(&alloc_err)) {
        handle_out_of_memory();
        _free_inseln(inseln, num_inseln);
        return 1;
    }

    for (int i = 1; i < num_inseln; i++) {
        alloc_err = node_push_back_insel(*tour, inseln[i]);

        if (kokos_has_error(&alloc_err)) {
            handle_out_of_memory();
            node_free(*tour);
            *tour = NULL;
            return 1;
        }
    }

    return 0;
}

int _setup_tour2() {
    Insel* inseln[4];
    int num_inseln = 4;
    Tour** tour = &tour2;

    int err = 0;
    err |= _new_insel_skull(&inseln[0]);
    err |= _new_insel_craggy(&inseln[1]);
    err |= _new_insel_nubar(&inseln[2]);
    err |= _new_insel_skull(&inseln[3]);

    if (err) {
        _free_inseln(inseln, num_inseln);
        return err;
    }

    KokosError alloc_err = node_new(inseln[0], tour);
    if (kokos_has_error(&alloc_err)) {
        handle_out_of_memory();
        _free_inseln(inseln, num_inseln);
        return 1;
    }

    for (int i = 1; i < num_inseln; i++) {
        alloc_err = node_push_back_insel(*tour, inseln[i]);

        if (kokos_has_error(&alloc_err)) {
            handle_out_of_memory();
            node_free(*tour);
            *tour = NULL;
            return 1;
        }
    }

    return 0;
}

int _setup_tour3() {
    Insel* inseln[3];
    int num_inseln = 3;
    Tour** tour = &tour3;

    int err = 0;
    err |= _new_insel_shutter(&inseln[0]);
    err |= _new_insel_skull(&inseln[1]);
    err |= _new_insel_shutter(&inseln[2]);

    if (err) {
        _free_inseln(inseln, num_inseln);
        return err;
    }

    KokosError alloc_err = node_new(inseln[0], tour);
    if (kokos_has_error(&alloc_err)) {
        handle_out_of_memory();
        _free_inseln(inseln, num_inseln);
        return 1;
    }

    for (int i = 1; i < num_inseln; i++) {
        alloc_err = node_push_back_insel(*tour, inseln[i]);

        if (kokos_has_error(&alloc_err)) {
            handle_out_of_memory();
            node_free(*tour);
            *tour = NULL;
            return 1;
        }
    }

    return 0;
}

int _setup_tour4() {
    Insel* inseln[3];
    int num_inseln = 3;
    Tour** tour = &tour4;

    int err = 0;
    err |= _new_insel_shutter(&inseln[0]);
    err |= _new_insel_skull(&inseln[1]);
    err |= _new_insel_shutter(&inseln[2]);

    if (err) {
        _free_inseln(inseln, num_inseln);
        return err;
    }

    KokosError alloc_err = node_new(inseln[0], tour);
    if (kokos_has_error(&alloc_err)) {
        handle_out_of_memory();
        _free_inseln(inseln, num_inseln);
        return 1;
    }

    for (int i = 1; i < num_inseln; i++) {
        alloc_err = node_push_back_insel(*tour, inseln[i]);

        if (kokos_has_error(&alloc_err)) {
            handle_out_of_memory();
            node_free(*tour);
            *tour = NULL;
            return 1;
        }
    }

    return 0;
}

int Setup_Tour() {
    int err = 0;
    err |= _setup_tour1();
    err |= _setup_tour2();
    err |= _setup_tour3();
    err |= _setup_tour4();

    return err;
}

void Output_Tour(const Tour* tour, int id) {

    printf("%s\n", DIV);
    printf("---------------- Tour %d ---------------------------\n", id);
    printf("%s\n%s\n", DIV, DIV);

    for (const Tour* iter = tour; iter != NULL; iter = iter->next) {
        Output_Insel(iter->insel);
        printf("\n%s\n", DIV);
    }

    printf("                         Ende \n");
}

void Cleanup_Tour() {

}

int main() {

    if(Setup_Tour()) return 1;

    int op = 0;
    printf("Bitte die Tour Nummer (1-4) eingeben oder mit 0 beenden: ");
    scanf("%d", &op);

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

    Cleanup_Tour();

    return 0;
}