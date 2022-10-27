#include "../inc/sender.h"
#include "../inc/err.h"

static int counter_positive = 0;
static int counter_negative = 0;

static Msg* make_message(Msg* msg, size_t counter)
{
    char data[MSG_SIZE];
    sprintf(data, TEST_MSG, counter);
    enter_data(msg, data, counter);
}

void* sender_positive(void* arg)
{
    struct mq_attr attribute;
    set_attribute_struct(&attribute); 

    // O_NONBLOCK =  Open the queue in nonblocking mode (The default is to enter block when the queue is full) 
    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_WRONLY /* | O_NONBLOCK */, S_IRUSR | S_IWUSR, &attribute);  
    if(queue == FAIL)
    {
        fatal_error("mq_open fail", "mq_open");
        return NULL;
    }

    while(!((Arg*)arg)->stop)
    {
        ++counter_positive;
        Msg send_msg;
        make_message(&send_msg, counter_positive);

        //int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
        // On success, mq_send() and mq_timedsend() return zero;
        // on error, -1 is returned, with errno set to indicate the error.
        int mq_send_return = mq_send(queue, (char*)&send_msg, sizeof(send_msg), FIX_MESSAGE_PRIORITY); // // can use mq_timedsend() for limiting block mode when the queue is full
        if(mq_send_return == FAIL)
        {
            if(errno != EAGAIN) // EAGAIN = mq is full
            {
                printf("mq is full!\n"); // if you set mq to O_NONBLOCK
            }
            else
            { 
                fatal_error("mq_send fail", "mq_send");
                ((Arg*)arg)->stop =  TRUE;
            }
        }

        attribute.mq_curmsgs++;  
    }

    int mq_close_return = mq_close(queue);
    if(mq_close_return != 0)
        fatal_error("mq_close fail", "mq_close");

    int mq_unlink_return = mq_unlink(MQ_NAME);
    if(mq_unlink_return)
        fatal_error("mq_unlink fail", "mq_unlink");

    return NULL;
}

void* sender_negative(void* arg)
{
    struct mq_attr attribute;
    set_attribute_struct(&attribute); 

    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_WRONLY /* | O_NONBLOCK */, S_IRUSR | S_IWUSR, &attribute);  
    if(queue == FAIL)
    {
        fatal_error("mq_open fail", "mq_open");
        return FALSE;
    }

    while(!((Arg*)arg)->stop)
    {
        --counter_negative;
        Msg send_msg;
        make_message(&send_msg, counter_negative);

        int mq_send_return = mq_send(queue, (char*)&send_msg, sizeof(send_msg), FIX_MESSAGE_PRIORITY);
        if(mq_send_return != 0)
        {
            if(errno == EAGAIN) 
            {
                printf("mq is full!\n"); 
            }
            else
            { 
                fatal_error("mq_send fail", "mq_send");
                ((Arg*)arg)->stop =  TRUE;
            }
        }  

        attribute.mq_curmsgs++;  
    }

    int mq_close_return = mq_close(queue);
    if(mq_close_return != 0)
        fatal_error("mq_close fail", "mq_close");

    int mq_unlink_return = mq_unlink(MQ_NAME);
    if(mq_unlink_return)
        fatal_error("mq_unlink fail", "mq_unlink");

    return NULL;
}