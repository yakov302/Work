#ifndef USERS_MANAGER_H
#define USERS_MANAGER_H

#include "user.h"
#include "hash_map.h"

#define NOT_EQUAL 0
#define EQUAL 1

typedef struct UserManager
{
	HashMap* m_users;
	int m_magic_number;

}UserManager;

typedef enum UserManager_return
{
	USER_MANAGER_SUCCESS,
	USER_MANAGER_ARGS_NOT_INITIALIZED,
	USER_MANAGER_MALLOC_FAIL,
	USER_MANAGER_USER_NOT_EXISTS,
    USER_MANAGER_GROUP_NOT_EXISTS,
	USER_MANAGER_USER_ALREADY_IN_THE_GROUP,
    USER_MANAGER_USER_ALREADY_LOGGED_IN,
    USER_MANAGER_LOG_IN_FAIL,
    USER_MANAGER_JOIN_GROUP_FAIL,
    USER_MANAGER_LEAVE_GROUP_FAIL,
    USER_MANAGER_LOGE_OUT_FAIL

} UserManager_return;


UserManager* create_users_manager(int capacity);

void destroy_users_manager(UserManager* users_manager);

UserManager_return user_log_in(UserManager* users_manager, const char* name);

UserManager_return user_join_group(UserManager* users_manager, char* user_name, char* group_ame);

UserManager_return user_leave_group(UserManager* users_manager, char* _username, char* _groupName);

UserManager_return user_log_out(UserManager* users_manager, char* name);


#endif // USERS_MANAGER_H
