#include <pthread.h>

#include "../inc/sender.h"
#include "../inc/receiver.h"
#include "../inc/thread.h"
#include "../inc/common.h"

int main()
{
    Arg* arg = (Arg*)malloc(sizeof(Arg));
    arg->stop = FALSE;
    pthread_mutex_init(&arg->lock, NULL);

    int t1 = run_thread(sender_positive, (void*)arg);
    int t2 = run_thread(sender_negative, (void*)arg);
    int t3 = run_thread(receiver, (void*)arg);
    int t4 = run_thread(receiver, (void*)arg);
    int t5 = run_thread(receiver, (void*)arg);

    while(TRUE)
    {
        char c = getchar();
        if(c == 'q' || c == 27)
        {
            arg->stop = TRUE;
            break;
        }
    }

    join_thread(t5);
    join_thread(t4);
    join_thread(t3);
    join_thread(t2);
    join_thread(t1);

    pthread_mutex_destroy(&arg->lock);
    free(arg);

    return TRUE;
}
