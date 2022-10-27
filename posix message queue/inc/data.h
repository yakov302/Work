#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MSG_SIZE 256

//our "data" struct example
typedef struct Msg 
{
    char m_msg[MSG_SIZE];
    int m_index;
}Msg;

void enter_data(Msg* msg, char* data, int index);

void give_data(Msg* msg, char* data, int* index);


#endif // DATA_H
