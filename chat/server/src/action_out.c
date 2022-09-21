#include "action_out.h"

static int pack_2_strings(char* buffer, Message_type message_type, char* first_string, char* second_string)
{
    Args arg;
    args_create(&arg, 2, 0, 0);
    push_string(&arg, first_string);
    push_string(&arg, second_string);

    int size = pack(buffer, &arg, message_type);

    args_destroy(&arg);
    return size;
}

static int pack_1_strings(char* buffer, Message_type message_type, char* string)
{
    Args arg;
    args_create(&arg, 1, 0, 0);
    push_string(&arg, string);

    int size = pack(buffer, &arg, message_type);

    args_destroy(&arg);
    return size;
}

void send_only_message(Message_type message_type, int client_socket, Mutex* mutex)
{
    Args arg;
    char buffer[BUFFER_SIZE];
    args_create(&arg, 0, 0, 0);

    int size = pack(buffer, &arg, message_type);
    int result = send_to_client(client_socket, buffer, size, mutex);
    if(result != TRUE)
        printf("send to client %d fail, return value: %d", client_socket, result);

    args_destroy(&arg);
}

void send_connect_to_group_success(char* group_name, char* ip, Message_type message_type, int client_socket, Mutex* mutex)
{
    char buffer[BUFFER_SIZE];
    int size = pack_2_strings(buffer, message_type, group_name, ip);

    int result = send_to_client(client_socket, buffer, size, mutex);
    if(result != TRUE)
        printf("send to client %d fail, return value: %d", client_socket, result);
}

void send_all_groups_names(char* groups_names_list, int client_socket, Mutex* mutex)
{
    char buffer[GRUPS_NAMES_LIST_SIZE];
    int size = pack_1_strings(buffer, PRINT_EXISTING_GROUPS_SUCCESS, groups_names_list);

    int result = send_to_client(client_socket, buffer, size, mutex);
    if(result != TRUE)
        printf("send to client %d fail, return value: %d", client_socket, result);  
}

