#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "protocol.h"

#define MAGIC_NUMBER 144522
#define STRING_SIZE 30
#define NOT_ACTIVE 0
#define ACTIVE 1

typedef enum User_return
{
	USER_SUCCESS,
	USER_MALLOC_FAIL,
	USER_NOT_INITIALIZED,
	USER_NOT_FOUND_IN_HASH,
	ALREADY_IN_THE_GROUP

}User_return;

struct User
{
	char m_name[STRING_SIZE];
	char m_password[STRING_SIZE];
	char m_active;
    List* m_groups;
	int m_magic_number;
};
typedef struct User User;


User* create_user (Args* arg);

void DestroyUser (User* user);

void set_user_password (User* user, char* password);

int user_status (User* user);

void set_user_status (User* _user, int _status);

/**Function remove group from list of user's groups. 
Input: User struct created above, and group name to remove.
Output: USER_STRUCT_SUCCESS - if group removed successfully.
		USER_STRUCT_NOT_FOUND_IN_HASH - if group didn't found
		USER_STRUCT_NOT_INITIALIZED - if one of parameters is NULL**/
int RemoveGroupFromUser (User* _user, char* _groupName);

/**Function add group to list of user's groups. 
Input: User struct created above, and group name to add.
Output: USER_STRUCT_SUCCESS - if group removed successfully.
		ALMOST_IN_THE_GROUP - if user allmost connected to group.
		USER_STRUCT_MALLOC_FAIL - if allocation failed.
		USER_STRUCT_NOT_INITIALIZED- if one of parameters is NULL**/
int AddGroupForUser (User* _user, char* _groupName);

/**This function remove all groups and change user's status to no active.
Input: User struct created above, and group name to add.
Output: USER_STRUCT_NOT_INITIALIZED - if user is NULL, and USER_STRUCT_SUCCESS if success.**/
int UserNotActive (User* _user);


#endif // USER_H