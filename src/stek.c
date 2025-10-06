#include "stek.h"

#include <stdio.h>
#include <stdlib.h>

t_elem_stek* push(t_elem_stek* top, char* item) {
    t_elem_stek* new_elem_stek = malloc(sizeof(t_elem_stek));
    if (new_elem_stek == NULL) {
        return NULL;
    }
    new_elem_stek->num = item;
    new_elem_stek->pointer_next = top;
    return new_elem_stek;
}

t_elem_stek* pop(t_elem_stek* top) {
    if (top == NULL) {
        return top;
    }
    t_elem_stek* prev_elem_steka = top->pointer_next;
    free(top);
    return prev_elem_steka;
}
