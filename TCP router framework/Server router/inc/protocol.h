#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "args.h"

/*
    ***buufer order*** 

    [toal message size]      (4 bytes)

    [message type]           (1 bytes)

    [number of strings]      (1 bytes)

    [strings 1 size]         (1 bytes)
    [string 1]
        .
        .
        .
    [strings n size]         (1 bytes)
    [string n]

    [number of ints]         (1 bytes)

    [int 1]
        .
        .
        .
    [int n]

    [number of float]         (1 bytes)

    [float 1]
        .
        .
        .
    [float n]
*/

typedef enum Message_type
{
    // Internal messages

    BUFFER_NOT_INITIALIZE,
    ARGS_NOT_INITIALIZE,

    // Client to server

    MESSAGES_1,
    MESSAGES_2,
    MESSAGES_3,
    MESSAGES_4,
    MESSAGES_5,
    WAKE_UP_SERVER,

    // Server to client

    MESSAGES_6,
    MESSAGES_7,
    MESSAGES_8,
    MESSAGES_9,
    MESSAGES_10,
    WAKE_UP_CLIENT

} Message_type;


int pack(char* buffer, Args* arganmats, Message_type message);

Message_type unpack(char* buffer, Args* arganmats);

int message_size(char* buffer);

Message_type message_type(char* buffer);


#endif //PROTOCOL_H
