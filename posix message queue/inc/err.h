// module that print explains for all errors

#ifndef ERROR_H
#define ERROR_H

#include <errno.h>  
#include <stdio.h>

inline static void fatal_error(const char* error,  char* func)
{
    perror(error);

    if(func == "mq_open")
    {
        switch (errno)
        {
        case EACCES:
            printf("explain: The queue exists, but the caller does not have permission \nto open it in the specified mode.\n");
            printf("explain: name contained more than one slash.\n");
            break;

        case EEXIST:
            printf("explain: Both O_CREAT and O_EXCL were specified in oflag, but a \nqueue with this name already exists.\n");
            break;

        case EINVAL:
            printf("explain: name doesn't follow the format in mq_overview(7).\n");
            printf("explain: O_CREAT was specified in oflag, and attr was not NULL, but \nattr->mq_maxmsg or attr->mq_msqsize was invalid.  Both of \nthese fields must be greater than zero.  In a process that \nis unprivileged (does not have the CAP_SYS_RESOURCE \ncapability), attr->mq_maxmsg must be less than or equal to \nthe msg_max limit, and attr->mq_msgsize must be less than \nor equal to the msgsize_max limit.  In addition, even in a \nprivileged process, attr->mq_maxmsg cannot exceed the \nHARD_MAX limit.  (See mq_overview(7) for details of these\n limits.)\n");
            break;

        case EMFILE:
            printf("explain: The per-process limit on the number of open file and \nmessage queue descriptors has been reached (see the \ndescription of RLIMIT_NOFILE in getrlimit(2)).\n");
            break;

        case ENAMETOOLONG:
            printf("explain: name was too long.\n");
            break;

        case ENFILE:
            printf("explain: The system-wide limit on the total number of open files \nand message queues has been reached.\n");
            break;

        case ENOENT:
            printf("explain: The O_CREAT flag was not specified in oflag, and no queue \nwith this name exists.\n");
            printf("explain: name was just \"/\" followed by no other characters.\n");
            break;

        case ENOMEM:
            printf("explain: Insufficient memory.\n");
            break;

        case ENOSPC:
            printf("explain: Insufficient space for the creation of a new message queue. \nThis probably occurred because the queues_max limit was encountered; see mq_overview(7).\n");
            break;

        default:
            break;
        }
    }

    if(func == "mq_send")
    {
        switch (errno)
        {
        case EAGAIN:
            printf("explain: The queue was full, and the O_NONBLOCK flag was set for \nthe message queue description referred to by mqdes.\n");
            break;

        case EBADF:
            printf("explain: The descriptor specified in mqdes was invalid or not \nopened for writing.\n");
            break;

        case EINTR:
            printf("explain: The call was interrupted by a signal handler; see \nsignal(7).\n");
            break;

        case EINVAL:
            printf("explain: The call would have blocked, and abs_timeout was invalid, \neither because tv_sec was less than zero, or because \ntv_nsec was less than zero or greater than 1000 million.\n");
            break;

        case EMSGSIZE:
            printf("explain: msg_len was greater than the mq_msgsize attribute of the \nmessage queue.\n");
            break;

        case ETIMEDOUT:
            printf("explain:  The call timed out before a message could be transferred.\n");
            break;

        default:
            break;
        }
    }

    if(func == "mq_close")
    {
        switch (errno)
        {
        case EBADF:
            printf("explain: The message queue descriptor specified in mqdes is \ninvalid.\n");
            break;

        default:
            break;
        }
    }

    if(func == "mq_unlink")
    {
        switch (errno)
        {
        case EACCES:
            printf("explain: The caller does not have permission to unlink this message \nqueue.\n");
            break;

        case ENAMETOOLONG:
            printf("explain: name was too long.\n");
            break;

        case ENOENT :
            printf("explain: There is no message queue with the given name.\n");
            break;

        default:
            break;
        }
    }

    if(func == "mq_receive")
    {
        switch (errno)
        {
        case EAGAIN:
            printf("explain: The queue was empty, and the O_NONBLOCK flag was set for \nthe message queue description referred to by mqdes.\n");
            break;

        case EBADF:
            printf("explain: The descriptor specified in mqdes was invalid or not \nopened for reading.\n");
            break;

        case EINTR :
            printf("explain: The call was interrupted by a signal handler; see \nsignal(7).\n");
            break;

        case EINVAL:
            printf("explain: The call would have blocked, and abs_timeout was invalid, \neither because tv_sec was less than zero, or because \ntv_nsec was less than zero or greater than 1000 million.\n");
            break;

        case EMSGSIZE:
            printf("explain: msg_len was less than the mq_msgsize attribute of the \nmessage queue.\n");
            break;

        case ETIMEDOUT:
            printf("explain: The call timed out before a message could be transferred.\n");
            break;

        default:
            break;
        }
    }
}

#endif // ERROR_H
