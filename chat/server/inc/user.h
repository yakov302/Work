#ifndef USER_H
#define USER_H

#include <string.h>

#include "list_iterator.h"

#define MAGIC_NUMBER 144522
#define STRING_SIZE 30

typedef enum User_return
{
	USER_SUCCESS,
	USER_MALLOC_FAIL,
    USER_ARGS_NOT_INITIALIZED,
	USER_NOT_INITIALIZED,
	USER_GROUP_NOT_EXISTS,
	USER_ALREADY_IN_THE_GROUP

}User_return;

typedef struct User
{
	char m_name[STRING_SIZE];
    List* m_groups;
	int m_magic_number;

}User;

User* create_user(const char* name);

void destroy_user(User* user);

int remove_group_from_user(User* user, char* group_name);

int add_group_for_user(User* user, char* group_name);


#endif // USER_H