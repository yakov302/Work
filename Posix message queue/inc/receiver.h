#ifndef RECEIVER_H
#define RECEIVER_H

#include <fcntl.h>     // mq must library
#include <mqueue.h>    // mq must library
#include <sys/stat.h>  // mq must library

#include <errno.h>     // for errors
#include <unistd.h>    // for sleep
#include <pthread.h>   // for mutex

#include "common.h"    // module that contains all the things that should be the same for the sender and receiver
#include "err.h"       // module that print explains for all errors

void* receiver(void* arg);


#endif // RECEIVER_H
