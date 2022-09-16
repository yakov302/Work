#include "router.h"

static void* thread_function(void* arg)
{
	Router* router = (Router*)arg;
	run_router(router);
	return NULL;
}

Router* router_create()
{
    Router* router = (Router*)malloc(sizeof(Router));
    if(router == NULL)
        return NULL;
    
    router->m_socket = socket_create();
    if(router->m_socket == NULL)
    {
        free(router);
        return NULL;
    }

    router->m_mutex = tcp_create();
    if(router->m_mutex == NULL)
    {
        free(router->m_socket);
        free(router);
        return NULL;
    }

    router->m_buffer = (char*)malloc(BUFFER_SIZE*sizeof(char));
    if(router->m_socket == NULL)
    {
        free(router->m_mutex);
        free(router->m_socket);
        free(router);
        return NULL;
    }

    router->m_stop = OFF;
    router->m_activity = 0;
    router->m_thread_id = run_thread(thread_function, (void*)router);
    return router;
}

void router_destroy(Router* router)
{
    if(router == NULL)
        return;

    join_thread(router->m_thread_id);
    free(router->m_buffer);
    tcp_destroy(router->m_mutex);
    socket_destroy(router->m_socket);
    free(router);
    router = NULL;

    printf("+ router destroyed\n");
}

static void fatal_error(Router* router, const char* fail)
{
	perror(fail);
    stop_router(router);
    router_destroy(router);
}

static void delete_deleted(Router* router)
{
    ListItr it = ListItrBegin(router->m_socket->m_deleted_sockets);
	ListItr end = ListItrEnd(router->m_socket->m_deleted_sockets);
    ListItr next;

	while(it != end && ListSize(deleted_sockets(router->m_socket)) != 0)
	{
        next = ListItrNext(it);

        //action in other modules that need to know that cliend deleted		
        delete_from_deleted_sockets(router->m_socket, it);

        it = next; 
	}
}

static void take_care_exists_clients(Router* router)
{

    ListItr next;
    ListItr it = ListItrBegin(router->m_socket->m_connected_sockets);
	ListItr end = ListItrEnd(router->m_socket->m_connected_sockets);
	
	while((it != end) && (router->m_activity > 0)) 
	{	
        next = ListItrNext(it);

        int client_socket = *(int*)ListItrGet(it);
		if(is_in_active_fd(router->m_socket, client_socket))
		{
			if(!receive_from_client(client_socket, router->m_buffer, router->m_mutex))
				delete_client(router->m_socket, it);

            else
            {
                move_client_to_front(router->m_socket, it);
                get_buffer(router->m_buffer, client_socket, router->m_mutex);
            }
			
			--router->m_activity;
		}

		it = next; 
	} 
}

static void new_client(Router* router)
{
	if (num_of_clients(router->m_socket) > LISTEN_QUEUE_SIZE)
		delete_less_active_client(router->m_socket);

	int client_socket = accept_new_client(router->m_socket, router->m_mutex);
	if(client_socket == ACCEPT_FAIL)
    {
		fatal_error(router, "accept fail: \n");
        return;
    }

    if(client_socket == UNINITIALIZED_ARGS)
    {
        printf("accept unintialized arguments\n");
        return;
    }

    if(client_socket == MUTEX_FAIL)
    {
		printf("accept mutex fail\n");
        return;
    }

	insert_client(router->m_socket, client_socket);
}

void run_router(Router* router)
{
    printf("+ router up\n");
    
    while(!router->m_stop) 
	{
        printf("+ enter select\n");	

		router->m_activity = select(MAX_SOCKET_AMOUNT_TO_LISTEN, copy_of_source_fd(router->m_socket), NULL, NULL, NULL);
		if((router->m_activity < 0) && (errno != EINTR))
			fatal_error(router, "select fail: \n");

        printf("+ exit select\n");

		if(is_in_active_fd(router->m_socket, listen_socket(router->m_socket)))
		{
			new_client(router);
			router->m_activity--;
		}

		take_care_exists_clients(router);
		delete_deleted(router);
	}

    printf("+ router down\n");
}

static void wake_up(Router* router)
{
    int socket_num = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_num < 0)
		perror("wake_up socket fail: \n");
    
    struct sockaddr_in sin;
    memset (&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr =  inet_addr(router->m_socket->m_server_ip);
	sin.sin_port = htons(router->m_socket->m_server_port);

    if(connect(socket_num, (struct sockaddr*)&sin, sizeof(sin)) < 0)
		perror("wake_up connect fail: \n");
}

void stop_router(Router* router)
{
    router->m_stop = ON;
    wake_up(router);
}
