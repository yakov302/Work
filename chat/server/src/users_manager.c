#include "users_manager.h"

static size_t hash_for_user_name(void* name)
{
	int i;
	size_t mul = 1;

	const int len = strlen ((char*)name);
	for (i = 0; i < len; ++i)
		mul *= ((char*)name)[i]+((i+1));

	return mul;
}

static int compare_user_names (const void* first_name, const void* second_name)	
{
	if (strcmp ((char*)((User*)((Element*)first_name)->m_value)->m_name, (char*)second_name) == 0)
	{
		return EQUAL;
	}
	return NOT_EQUAL;
}

static void destroy_user_element(void* element) 
{
    if(element != NULL)
    {
	    destroy_user(((Element*)element)->m_value);
        free(((Element*)element)->m_key);
        free(element);
    }
}

UserManager* create_users_manager(int capacity)
{
    if(capacity < 1)
        return NULL;

	UserManager* user_manager = (UserManager*)malloc(sizeof(UserManager));
	if (user_manager == NULL)
	    return NULL;

	user_manager->m_users = hash_map_create(capacity, hash_for_user_name, compare_user_names, destroy_user_element);
	if (user_manager->m_users == NULL)
	{
		free(user_manager);
		return NULL; 
	}

    user_manager->m_magic_number = MAGIC_NUMBER;
	return user_manager;
}

void destroy_users_manager(UserManager* user_manager)
{
	if (user_manager == NULL || user_manager->m_magic_number != MAGIC_NUMBER)
	    return;

	user_manager->m_magic_number = 0;
	hash_map_destroy(&user_manager->m_users); 
	free (user_manager);
    user_manager = NULL;
}

static char* create_key(const char* name)
{
    char* user_name = (char*)malloc(sizeof(name));
    if (user_name == NULL)
        return NULL;

    strcpy(user_name, name);
    return user_name;
}

UserManager_return user_log_in(UserManager* users_manager, const char* name)
{
	if (users_manager == NULL || name == NULL)
		return USER_MANAGER_ARGS_NOT_INITIALIZED;

	if (hash_map_is_exists(users_manager->m_users, name)) {return USER_MANAGER_USER_ALREADY_LOGGED_IN;}

    char* user_name = create_key(name);
    if (user_name == NULL) {return USER_MANAGER_MALLOC_FAIL;}

    User* user = create_user(name);
    if (user == NULL)
    {   
        free(user_name);
        return USER_MANAGER_MALLOC_FAIL;
    }

    Map_return status = hash_map_insert(users_manager->m_users, user_name, user);
    if (status != MAP_SUCCESS)
    {
        free (user_name);
        destroy_user (user);
        return USER_MANAGER_LOG_IN_FAIL;
    }
            
    return USER_MANAGER_SUCCESS;
}

UserManager_return user_join_group (UserManager* users_manager, char* user_name, char* group_name)
{
	if (users_manager == NULL || user_name == NULL || group_name == NULL)
	    return USER_MANAGER_ARGS_NOT_INITIALIZED;

    void* user;
	Map_return m_result = hash_map_find(users_manager->m_users, user_name, &user);
	if (m_result != MAP_SUCCESS) {return USER_MANAGER_USER_NOT_EXISTS;}

    User_return u_result = add_group_for_user((User*)user, group_name);
	if (u_result == USER_ALREADY_IN_THE_GROUP) {return USER_MANAGER_USER_ALREADY_IN_THE_GROUP;}
    else if(u_result == USER_SUCCESS) {return USER_MANAGER_SUCCESS;}
	return USER_MANAGER_JOIN_GROUP_FAIL;
}
	
UserManager_return user_leave_group (UserManager* users_manager, char* user_name, char* group_name)
{
	if (users_manager == NULL || user_name == NULL || group_name == NULL)
	    return USER_MANAGER_ARGS_NOT_INITIALIZED;

    void* user;
	Map_return m_result = hash_map_find(users_manager->m_users, user_name, &user);
	if (m_result != MAP_SUCCESS) {return USER_MANAGER_USER_NOT_EXISTS;}

	User_return u_result = remove_group_from_user((User*)user, group_name); 
    if (u_result == USER_GROUP_NOT_EXISTS) {return USER_MANAGER_GROUP_NOT_EXISTS;}
    else if(u_result == USER_SUCCESS) {return USER_MANAGER_SUCCESS;}
	return USER_MANAGER_LEAVE_GROUP_FAIL;
}

UserManager_return user_log_out(UserManager* users_manager, char* user_name)
{
	if (!hash_map_is_exists(users_manager->m_users, user_name)) {return USER_MANAGER_USER_NOT_EXISTS;}
	Map_return result = hash_map_remove_and_free(users_manager->m_users , user_name);
    if(result != MAP_SUCCESS) {return USER_MANAGER_LOGE_OUT_FAIL;}
	return USER_MANAGER_SUCCESS;
}
	