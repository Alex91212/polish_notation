#ifndef FUNC_AND_OP
#define FUNC_AND_OP

int is_operator(char* token);

int is_function(char* token);

double apply_operator(char* op, double a, double b);

double apply_function(char* func, double a);

int is_number(const char* mass_token);

#endif