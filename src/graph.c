#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func_and_op.h"
#include "stek.h"

#define PRECEDENCE_ADD 1   // + -
#define PRECEDENCE_MULT 2  // * /
// #define PRECEDENCE_POWER 3   // ^ возвдеение в степень делать не надо
#define PRECEDENCE_FUNC 4   // sin, cos, etc.
#define PRECEDENCE_UNARY 5  // -x унарные операторы

#define M_PI 3.14159265358979323846


#define WIDTH 80
#define HEIGHT 25

int input(char* input_func_str) {
    int i = 0;
    int flag = 1;
    while (i < 998 && flag) {
        scanf("%c", &input_func_str[i]);
        if (input_func_str[i] == '\n') {
            flag = 0;
        } else {
            i++;
        }
    }
    input_func_str[i] = '\0';
    return 1;
}

int get_precedence(char* token) {
    if (!(strcmp(token, "+")) || !(strcmp(token, "-"))) return PRECEDENCE_ADD;
    if (!(strcmp(token, "*")) || !(strcmp(token, "/"))) return PRECEDENCE_MULT;
    if (!(strcmp(token, "sin")) || !(strcmp(token, "cos")) || !(strcmp(token, "tg")) ||
        !(strcmp(token, "ctg")) || !(strcmp(token, "ln")) || !(strcmp(token, "sqrt")))
        return PRECEDENCE_FUNC;
    return 0;
}

char** split_to_tokens(const char* input_func_str, int* size_of_mass_token) { //разбивает входную строку на токены используя пробел как разделитель
    *size_of_mass_token = 0; // размер расмсматриваемого токена 
    int cnt_tokens = 1; // количество токенов
    for (int i = 0; input_func_str[i] != '\0'; i++) {
        if (input_func_str[i] == ' ') cnt_tokens++;
    }
    char** result = malloc(cnt_tokens * sizeof(char*)); // массив указателей на токены
    for (int i = 0; input_func_str[i] != '\0'; i++) { //перебираем токены 
        int start_of_token = 0;
        int end_of_token = 0;
        while (input_func_str[i] == ' ') {
            i++;
        }
        start_of_token = i;
        while (input_func_str[i] != ' ' && input_func_str[i] != '\0') {
            i++;
        }
        end_of_token = i;
        int lenght = end_of_token - start_of_token; //длина токена
        result[*size_of_mass_token] = malloc((lenght + 1) * sizeof(char)); //выделаем память для оперделенного токена
        for (int k = 0; k < lenght; k++) {
            result[*size_of_mass_token][k] = input_func_str[k + start_of_token]; // копирование токена из исходной строки в массив указателей на токены
        }
        result[*size_of_mass_token][lenght] = '\0'; //добавление конца строки. в конец токена
        (*size_of_mass_token)++;
    }
    return result;
}

void free_mass_token(char** mass_token, int size_of_mass_token) {
    for (int i = 0; i < size_of_mass_token; i++) {
        free(mass_token[i]);
    }
    free(mass_token);
}

char** conver_to_polsk_not(char** mass_token, int size_of_mass_token, int* size_of_polsk_not) {
    *size_of_polsk_not = 0;// количесто=во токенов в польской нотации

    t_elem_stek* top = NULL; //стек 

    char** polsk_not = malloc(sizeof(char*) * size_of_mass_token);
    for (int i = 0; i < size_of_mass_token; i++) {
        if ((strcmp(mass_token[i], "(")) == 0) {
            top = push(top, mass_token[i]);
        }

        if ((strcmp(mass_token[i], ")")) == 0) { //если появляется ) скобка: все операторы из стека засовываем в финальную строку до (
            while (top != NULL && (strcmp(top->num, "(")) != 0) { //выталкиваем все что в стеке до (
                polsk_not[*size_of_polsk_not] = malloc((strlen(top->num) + 1) * sizeof(char));
                strcpy(polsk_not[*size_of_polsk_not], top->num); //закидываем топ в ыфхоной массив
                (*size_of_polsk_not)++;
                top = pop(top); //удаляем топ из стека

                // удаляем саму открывающую скобку
                if (top != NULL && strcmp(top->num, "(")) { // удаляем ( из стека
                    top = pop(top);
                }
            }
        }

        if (is_number(mass_token[i])) {
            polsk_not[*size_of_polsk_not] = malloc((strlen(mass_token[i]) + 1) * sizeof(char));
            strcpy(polsk_not[*size_of_polsk_not], mass_token[i]);
            (*size_of_polsk_not)++;
        }

        else if (!(strcmp(mass_token[i], "x"))) {
            polsk_not[*size_of_polsk_not] = malloc(sizeof(char) * (1 + 1));  //
            strcpy(polsk_not[*size_of_polsk_not], "x");
            (*size_of_polsk_not)++;
        }

        else if (get_precedence(mass_token[i])) {  // в случае если это не одна из ождаемых операций для
                                                   // которой можно определеить приоритет, то функция вернет 0
            if (top == NULL) {
                top = push(top, mass_token[i]);
            } else {
                if (get_precedence(top->num) >=
                    get_precedence(mass_token[i])) {  // если у операции в стеке больший приоритет, то
                                                      // добавляем ее в выходную строку
                    while (top != NULL && (get_precedence(top->num) >= get_precedence(mass_token[i]))) {
                        polsk_not[*size_of_polsk_not] = malloc((strlen(top->num) + 1) * sizeof(char));
                        strcpy(polsk_not[*size_of_polsk_not], top->num);
                        (*size_of_polsk_not)++;
                        top = pop(top);
                    }
                    top = push(top, mass_token[i]);
                } else {  // случай если в стеке +, а мы рассматриваем умножение (у умножения приоритет
                          // больше)
                    top = push(top, mass_token[i]);
                }
            }
        }
    }
    // мы зкончили читать токены и теперь нужно остатки стека закинуть в итоговую строку
    while (top != NULL) {
        if ((strcmp(top->num, "(")) != 0 && (strcmp(top->num, ")")) != 0) {
            polsk_not[*size_of_polsk_not] = malloc((strlen(top->num) + 1) * sizeof(char));
            strcpy(polsk_not[*size_of_polsk_not], top->num);
            (*size_of_polsk_not)++;
        }
        top = pop(top);
    }

    return polsk_not;
}

double working_with_stack(double x, char** polsk_not, int number_of_tokens) {
    t_elem_stek* top = NULL;

    char buffer[32];  // буфер для преобразования чисел

    for (int i = 0; i < number_of_tokens; ++i) {
        if (is_number(polsk_not[i])) {
            top = push(top, polsk_not[i]);
        } else if (strcmp(polsk_not[i], "x") == 0) {
            sprintf(buffer, "%f", x);
            top = push(top, buffer);
        } else if (is_operator(polsk_not[i])) {
            if (top != NULL && top->pointer_next != NULL) {
                char* b_str = top->num;
                top = pop(top);

                char* a_str = top->num;
                top = pop(top);

                double a = atof(a_str);
                double b = atof(b_str);
                double res = apply_operator(polsk_not[i], a, b);

                sprintf(buffer, "%lf", res);
                top = push(top, buffer);
            }
        } else if (is_function(polsk_not[i])) {
            if (top != NULL) {
                char* a_str = top->num;
                top = pop(top);

                double a_val = atof(a_str);
                double res = apply_function(polsk_not[i], a_val);

                sprintf(buffer, "%lf", res);
                top = push(top, buffer);
            }
        }
    }
    double number = 0.0;
    if (top != NULL) {
        number = atof(top->num);
    }

    while (top != NULL) {
        top = pop(top);  // освобождаем память
    }

    return number;
}

void draw(char** polsk_not, int number_of_tokens) {
    double delta_x = M_PI * 4.0 / (WIDTH - 1);

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            double x = col * delta_x;
            double result = working_with_stack(x, polsk_not, number_of_tokens);

            int screen_y = HEIGHT - 1 - (int)((result + 1.0) * (HEIGHT - 1) / 2.0 + 0.5);

            if (screen_y >= 0 && screen_y < HEIGHT && screen_y == row) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main(void) {
    char input_func_str[1000];

    int size_of_mass_token = 0;
    int size_of_polsk_not = 0;

    input(input_func_str);

    char** mass_token = split_to_tokens(input_func_str, &size_of_mass_token);

    char** polsk_not = conver_to_polsk_not(mass_token, size_of_mass_token, &size_of_polsk_not);

    draw(polsk_not, size_of_polsk_not);

    free_mass_token(mass_token, size_of_mass_token);
    free_mass_token(polsk_not, size_of_polsk_not);

    return 0;
}
