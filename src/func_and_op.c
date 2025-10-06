#include "func_and_op.h"

#include <math.h>
#include <string.h>

int is_operator(char* token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
           strcmp(token, "/") == 0;
}

int is_function(char* token) {
    return strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "ctg") == 0 ||
           strcmp(token, "tg") == 0 || strcmp(token, "sqrt") == 0 || strcmp(token, "ln") == 0;
}

double apply_operator(char* op, double a, double b) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return b != 0 ? a / b : 0;
    return 0;
}

double apply_function(char* func, double a) {
    if (strcmp(func, "sin") == 0) return sin(a);
    if (strcmp(func, "cos") == 0) return cos(a);
    if (strcmp(func, "tg") == 0) return tan(a);
    if (strcmp(func, "ctg") == 0) return cos(a) / sin(a);
    if (strcmp(func, "ln") == 0) return a > 0 ? log(a) : NAN;
    if (strcmp(func, "sqrt") == 0) return a >= 0 ? sqrt(a) : NAN;
    return NAN;
}

int is_number(const char* mass_token) {
    int flag = 1;
    for (int i = 0; mass_token[i] != '\0'; i++) {
        if (!(mass_token[i] == '0' || mass_token[i] == '1' || mass_token[i] == '2' || mass_token[i] == '3' ||
              mass_token[i] == '4' || mass_token[i] == '5' || mass_token[i] == '6' || mass_token[i] == '7' ||
              mass_token[i] == '8' || mass_token[i] == '9')) {
            flag = 0;
        }
    }
    return flag;
}