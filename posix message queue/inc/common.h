#ifndef COMMON_H
#define COMMON_H

#include <mqueue.h>
#include <pthread.h>

#include "data.h" //our data implementation

#define MQ_NAME "/mq_vsat_queue" // Must be the same for the sender and receiver in mq_open(). must start with  \ like file that can open.
#define QUEUE_SIZE 10
#define FAIL -1
#define TRUE 1
#define FALSE 0

// arguments for threads
typedef struct Arg
{
    int stop;
    pthread_mutex_t lock;

}Arg;

int set_attribute_struct(struct mq_attr* attribute);


#endif // COMMON_H
