#ifndef ACTION_IN_H
#define ACTION_IN_H

#include "tcp.h"
#include "mutex.h"

void get_buffer(char* buffer, int client_socket, Mutex* mutex);


#endif // ACTION_IN_H
