#ifndef STEK_H
#define STEK_H

typedef struct s_elem_stek {
    char* num;
    struct s_elem_stek* pointer_next;
} t_elem_stek;

t_elem_stek* pop(t_elem_stek* head);

t_elem_stek* push(t_elem_stek* head, char* item);

#endif
