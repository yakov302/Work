#include "../inc/common.h"

// attribute for mq_open()
int set_attribute_struct(struct mq_attr* attribute)
{
    attribute->mq_flags = 0;               /* Flags: 0 or O_NONBLOCK. O_NONBLOCK =  Open the queue in nonblocking mode (The default is to enter block when the queue is full/empty)*/
    attribute->mq_maxmsg = QUEUE_SIZE;     /* Max. # of messages on queue */  //need to update the max limit in the file:  /proc/sys/fs/mqueue/msg_max (The default is only 10)
    attribute->mq_msgsize = sizeof(Msg);   /* Max. message size (bytes) */
    attribute->mq_curmsgs = 0;             /* # of messages currently in queue */
}