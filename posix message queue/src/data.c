#include "../inc/data.h"

void enter_data(Msg* msg, char* data, int index)
{
    if(msg == NULL || data == NULL)
        printf("uninitialized arguments\n");
    
    strcpy(msg->m_msg, data);
    msg->m_index = index;
}

void give_data(Msg* msg, char* data, int* index)
{
    if(msg == NULL || data == NULL)
        printf("uninitialized arguments\n");
    
    strcpy(data, msg->m_msg);
    *index = msg->m_index;
}