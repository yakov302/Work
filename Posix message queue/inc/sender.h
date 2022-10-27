#ifndef SENDER_H
#define SENDER_H

#include <fcntl.h>     // mq must library
#include <mqueue.h>    // mq must library
#include <sys/stat.h>  // mq must library

#include <errno.h>     // for errors
#include <unistd.h>    // for sleep

#include "common.h"    // module that contains all the things that should be the same for the sender and receiver
#include "err.h"       // // module that print explains for all errors

#define TEST_MSG "VSAT test msg # %ld"
#define FIX_MESSAGE_PRIORITY 1

void* sender_positive(void* arg);

void* sender_negative(void* arg);


#endif // SENDER_H
