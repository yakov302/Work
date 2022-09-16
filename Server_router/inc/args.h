#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 30

typedef struct Args
{
    char* m_strings;
    int* m_ints;
    float* m_floats;

    int m_num_of_strings;
    int m_num_of_ints;
    int m_num_of_floats;

}Args;

void args_create(Args* args, int num_of_strings, int num_of_ints, int num_of_float);

void push_string(Args* args, const char* string);

void push_int(Args* args, int number);

void push_float(Args* args, float number);

void args_destroy(Args* args);


#endif //ARGS_H
