#include "user.h"

User* create_user(Args* args)
{
	User* user = (User*)malloc(sizeof(User));
	if (user == NULL)
	    return NULL;

	user->m_groups = list_create();
	if (user->m_groups == NULL)
	{
		free(user);
		return NULL;
	}

	strcpy (user->m_name, strings(args));
	strcpy (user->m_password, strings(args));
	user->m_active = NOT_ACTIVE;
    user->m_magic_number = MAGIC_NUMBER;
	return user;
}

static void destroy_grup_name(void* name)
{
	free(name);
}

void destroy_user(User* user)
{
	if (user == NULL || user->m_magic_number != MAGIC_NUMBER)
	    return;

	user->m_magic_number = 0;
	list_destroy(&user->m_groups, destroy_grup_name);
	free (user);
    user == NULL;
}

void set_user_password(User* user, char* password)
{
	if (user == NULL || password == NULL)
	    return;

	strcpy(password, user->m_password);
}

char user_status(User* user)
{
	return user->m_active;
}

void set_user_status(User* user, char status)
{
	user->m_active = status;
}

static int is_group_name_equal(void* a, void* b)
{
    if(strcmp((char*)a, (char*)b) == 0)
        return YES;
    return NO;
}

int add_group_for_user(User* user, char* group_name)
{
    if (user == NULL || group_name == NULL)
	    return ARGS_NOT_INITIALIZED;

    if(list_is_exists(user->m_groups, is_group_name_equal, group_name))
        return ALREADY_IN_THE_GROUP;

	char* name = malloc(sizeof(char)*STRING_SIZE);
	if (name == NULL)
	    return ARGS_NOT_INITIALIZED;

	strcpy (name, group_name);
	list_push_tail(user->m_groups, (void*)name);
	return USER_SUCCESS;
}
	
int remove_groupf_rom_user(User* user, char* group_name)
{
    if (user == NULL || group_name == NULL)
	    return ARGS_NOT_INITIALIZED;

    ListItr it = find_first(user->m_groups, is_group_name_equal, group_name);
    if(it != NULL)
    {
        remove_it(it);
		return USER_SUCCESS;
    }
    
	return GROUP_NOT_EXISTS;
}

static void free_group_name(void* group_name)
{
	free((char*)group_name);
}

int deactivate_user(User* user)
{
	if (user == NULL)
	    return USER_NOT_INITIALIZED;

	list_erase(user ->m_groups, free_group_name);
	user->m_active = NOT_ACTIVE;
	return USER_SUCCESS;
}