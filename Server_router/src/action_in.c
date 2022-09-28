#include "action_in.h"

void get_buffer(char* buffer, int client_socket, Mutex* mutex)
{
    // need switch case here

    Args arg_r;
    args_create(&arg_r, 1, 1, 0);
    unpack(buffer, &arg_r);

    printf("\n-------------------------------------------------------start_message\n");
    printf("string: %s\n", arg_r.m_strings + (0*STRING_SIZE));
    printf("int: %d\n", arg_r.m_ints[0]);
    printf("---------------------------------------------------------end_message\n\n");

    args_destroy(&arg_r);


    char buff[512];
    char message[30];

    Args arg_s;
    args_create(&arg_s, 1, 1, 0);
    push_int(&arg_s, client_socket);
    sprintf(message, "from server to client - %d", client_socket);
    push_string(&arg_s, message);
    int size = pack(buff, &arg_s, MESSAGES_4);
    args_destroy(&arg_s);

    send_to_client(client_socket, buff, size, mutex);
}
