#ifndef _THREAD_
#define _THREAD_

#include <stdio.h>
#include <pthread.h>
#include <stdio.h>

typedef void*(*ThreadFunc)(void*);

int run_thread(ThreadFunc function, void* arg);

void join_thread(int thread_id);


#endif // _THREAD_