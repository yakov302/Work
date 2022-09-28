#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include "protocol.h"
#include "args.h"

#define SERVER_PORT 5555
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 500
#define FAIL 0
#define SUCCESS 1
#define CLIENTS_NUMBER 1000
#define DISCONNECTED 0
#define TRUE 1


static void SinSetting(struct sockaddr_in *_sin)
{
	memset (_sin, 0, sizeof(*_sin));
	
	_sin -> sin_family = AF_INET;
	_sin -> sin_addr.s_addr =  inet_addr(SERVER_IP);
	_sin -> sin_port = htons(SERVER_PORT);
}

static int ClientInitialization(struct sockaddr_in *_sin)
{
    int socketNum;
    socklen_t sinLen;
    int optval = 1;
    int flags;

	socketNum = socket(AF_INET, SOCK_STREAM, 0);
	if(socketNum < 0)
	{
		perror("Socket fail!\n");
		return FAIL;
	}
		
	if(setsockopt(socketNum, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		perror("Setsockopt fail!\n");
		return FAIL;
	}
		
    return socketNum;
}

static int ConnectToServer(struct sockaddr_in *_sin, int _socketNum)
{
	SinSetting(_sin);
	
	if(connect(_socketNum, (struct sockaddr*)_sin, sizeof(*_sin)) < 0)
	{	
		perror("Connect fail!\n");
		return FAIL;	
	}
	
    printf("+ client %d Connect\n", _socketNum);
    return SUCCESS;
}

static int SendAndReceiveData(int _socketNum)
{
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int receiveBytes;
    int sentByte;

    Args arg;
    args_create(&arg, 1, 1, 0);
    push_int(&arg, _socketNum);
    sprintf(message, "client - %d", _socketNum);
    push_string(&arg, message);
    int size = pack(buffer, &arg, MESSAGES_3);
    args_destroy(&arg);

    sentByte = send(_socketNum, buffer,size, 0);
    if(sentByte < 0)
    {
        perror("Send fail!\n");	
        return FAIL;	
    }

    printf("+ client %d send\n", _socketNum);

    receiveBytes = recv(_socketNum, buffer, sizeof(buffer),0);
    if(receiveBytes == 0)
    {
    	printf("Connection closed!\n");
    	return FAIL;
    }
    if(receiveBytes < 0)
    {
    	perror("Receive fail!\n");
    	return FAIL;	
    }
    printf("+ client %d recv\n", _socketNum);

    Args arg_r;
    args_create(&arg_r, 1, 1, 0);
    unpack(buffer, &arg_r);

    printf("\n-------------------------------------------------------start_message\n");
    printf("string: %s\n", arg_r.m_strings + (0*STRING_SIZE));
    printf("int: %d\n", arg_r.m_ints[0]);
    printf("---------------------------------------------------------end_message\n\n");

    args_destroy(&arg_r);

    return SUCCESS;
}

static void CloseAllClient(int clientStock[])
{
int i;
	for(i = 0; i < CLIENTS_NUMBER; i++)
	{
		close(clientStock[i]);
		clientStock[i] = DISCONNECTED;	
	}

	printf("\nAll client closed!\n");
}

int main()
{
    static int clientStock[CLIENTS_NUMBER] = {DISCONNECTED};
    struct sockaddr_in sin;
    int socketNum;
    int index = 0;
    int random;

	while(TRUE)
	{
		random = rand()%100;
		
		if(clientStock[index] ==  DISCONNECTED)
		{
			if(random < 30)
			{
				if((socketNum = ClientInitialization(&sin)) != FAIL)
				{
					if(ConnectToServer(&sin, socketNum) != FAIL)
					{
						clientStock[index] = socketNum;						
					}
				}				
			}		
		}
		
		if(clientStock[index] !=  DISCONNECTED)
		{
			if(random > 95)
			{
				printf("client socket no. %d disconnects!\n", clientStock[index]);
				close(clientStock[index]);
				clientStock[index] = DISCONNECTED;
			}
			if(random < 30)
			{
				if(SendAndReceiveData(clientStock[index]) == FAIL)
				{
				    printf("client socket no. %d disconnects!\n", clientStock[index]);
					close(clientStock[index]);
					clientStock[index] = DISCONNECTED;
				}
			}
		}
		
		index = (index + 1)%CLIENTS_NUMBER;
        //usleep(1000000);
	}
	
    CloseAllClient(clientStock);
}
