#include "../inc/receiver.h"

int prev_number_positive = 0;
int prev_number_negative = 0;

static int validate_fifo(Msg* msg)
{
    int number =  msg->m_index;

    if(number < 0)
    {
        if(number - prev_number_negative != -1)
        {
            printf("FIFO ERR: current number: %d, previous number: %d\n", number, prev_number_negative);
            return FALSE;
        }
        prev_number_negative = number;
    }

    if(number > 0)
    {
        if(number - prev_number_positive != 1)
        {
            printf("FIFO ERR: current number: %d, previous number: %d\n", number, prev_number_positive);
            return FALSE;
        }
        prev_number_positive = number;
    }

    return TRUE;
}

static void printf_msg(Msg* msg)
{
    if(msg->m_msg[0] != 'V')
    {
        printf("empty!\n");
        return;
    }

    printf("%s\n", msg->m_msg);
}

static void zero_msg(Msg* msg)
{
    msg->m_index = 0;
    msg->m_msg[0] = '\0';
}

void* receiver(void* arg)
{
    struct mq_attr attribute;            // attribute of mq
    set_attribute_struct(&attribute);    // in common.c

    // mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
    // On success, mq_open() returns a message queue descriptor for use by other message queue functions.
    // On error, mq_open() returns (mqd_t) -1, with errno set to indicate the error.
    // O_CREAT = Create the message queue if it does not exist. 
    // Q_RDONLY = Open the queue to receive messages only. 
    // O_NONBLOCK =  Open the queue in nonblocking mode (The default is to enter block when the queue is empty)
    // S_IRUSR/S_IWUSR = Read permission bit for the owner of the file/Write permission bit for the owner of the file.
    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_RDONLY /* | O_NONBLOCK */, S_IRUSR | S_IWUSR, &attribute);  
    if(queue == FAIL)
    {
        fatal_error("mq_open fail", "mq_open");
        return NULL;
    }

    while(!((Arg*)arg)->stop)
    {
        pthread_mutex_lock(&((Arg*)arg)->lock);

        Msg recive_msg;

        //size_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
        // On success, mq_receive() and mq_timedreceive() return the number of bytes in the received message;
        // on error, -1 is returned, with errno set to indicate the error.
        size_t mq_receive_return = mq_receive(queue, (char*)&recive_msg, sizeof(recive_msg), NULL); // can use mq_timedreceive() for limiting block mode when the queue is empty
        if(mq_receive_return == FAIL)
        {
            if(errno == EAGAIN) // EAGAIN = mq is empty
            {
                printf("mq is empty!\n"); // if you set mq to O_NONBLOCK
            }
            else
            {
                fatal_error("mq_receive fail", "mq_receive");
                ((Arg*)arg)->stop =  TRUE;
            }
        }

        attribute.mq_curmsgs--;
        if(!validate_fifo(&recive_msg))
            ((Arg*)arg)->stop =  TRUE;
        printf_msg(&recive_msg);

        // zero_msg(recive_msg) // if you set mq to O_NONBLOCK
        pthread_mutex_unlock(&((Arg*)arg)->lock);
    }

    // closes the message queue descriptor mqdes.
    // On success mq_close() returns 0;
    // on error, -1 is returned, with errno set to indicate the error.
    int mq_close_return = mq_close(queue);
    if(mq_close_return != 0)
        fatal_error("mq_close fail", "mq_close");

    // delete the message queue.
    // On success mq_unlink() returns 0;
    // on error, -1 is returned, with errno set to indicate the error.
    int mq_unlink_return = mq_unlink(MQ_NAME);
    if(mq_unlink_return)
        fatal_error("mq_unlink fail", "mq_unlink");

    return NULL;
}