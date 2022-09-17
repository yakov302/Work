#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list_iterator.h"
#include "protocol.h"

#define MAGIC_NUMBER 144522
#define STRING_SIZE 30
#define NOT_ACTIVE 0
#define ACTIVE 1

typedef enum User_return
{
	USER_SUCCESS,
	USER_MALLOC_FAIL,
    ARGS_NOT_INITIALIZED,
	USER_NOT_INITIALIZED,
	GROUP_NOT_EXISTS,
	ALREADY_IN_THE_GROUP

}User_return;

typedef struct User
{
	char m_name[STRING_SIZE];
	char m_password[STRING_SIZE];
	char m_active;
    List* m_groups;
	int m_magic_number;
}User;

User* create_user(Args* arg);

void destroy_user(User* user);

void set_user_password(User* user, char* password);

char user_status(User* user);

void set_user_status(User* user, char status);

int remove_group_from_user(User* user, char* group_name);

int add_group_for_user(User* user, char* group_name);

int deactivate_user(User* user);


#endif // USER_H