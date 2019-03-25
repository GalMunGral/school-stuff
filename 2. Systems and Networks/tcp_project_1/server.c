/*///////////////////////////////////////////////////////////
*
* FILE:		server.c
* AUTHOR:	Wenqi He
* PROJECT:	CS 3251 Project 1 - Professor Ellen Zegura 
* DESCRIPTION:	Network Server Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/*Included libraries*/

#include <stdio.h>	  /* for printf() and fprintf() */
#include <sys/socket.h>	  /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>	  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>	  /* supports all sorts of functionality */
#include <unistd.h>	  /* for close() */
#include <string.h>	  /* support any string ops */

#include <pthread.h>

#define RCVBUFSIZE 512		/* The receive buffer size */
#define SNDBUFSIZE 512		/* The send buffer size */
#define BUFSIZE 40		/* Your name can be as many as 40 chars*/

char reqBuf[RCVBUFSIZE];
char resBuf[SNDBUFSIZE];
int balance[5] = { 999, 199, 299, 399, 499 };  /* Balance of each of the five accounts */
int counters[5] = { 0, 0, 0, 0, 0 };  /* Counter for each of the five accounts */
int hash(char *accountName);
void handle_request(char buffer[]);
void *timer(void *acc_hash);

/* The main function */
int main(int argc, char *argv[])
{

    int serverSock;				/* Server Socket */
    int clientSock;				/* Client Socket */
    struct sockaddr_in changeServAddr;		/* Local address */
    struct sockaddr_in changeClntAddr;		/* Client address */
    unsigned short changeServPort;		/* Server port */
    unsigned int clntLen;			/* Length of address data struct */

    char nameBuf[BUFSIZE];			/* Buff to store account name from client */
    // int  balance;				/* Place to record account balance result */

    if (argc < 2)
    {
        printf("Too few arguments.\n");
        exit(1);
    }
    
    /* Create new TCP Socket for incoming requests*/
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct local address structure*/
    sscanf(argv[1], "%hu", &changeServPort);
    changeServAddr.sin_family = AF_INET;
    changeServAddr.sin_port = htons(changeServPort);
    changeServAddr.sin_addr.s_addr = INADDR_ANY;

    /* Bind to local address structure */
    if(-1 == bind(serverSock, (struct sockaddr *) &changeServAddr, sizeof(changeServAddr)))
    {
        perror("\'bind\' failed");
        exit(1);
    }

    /* Listen for incoming connections */
    if (-1 ==listen(serverSock, 5))
    {
        perror("\'listen\' failed");
        exit(1);
    }

    /* Loop server forever*/
    while(1)
    {

	/* Accept incoming connection */
    clntLen = sizeof(changeClntAddr);
    clientSock = accept(serverSock, (struct sockaddr *) &changeClntAddr, &clntLen);
    if (-1 == clientSock)
    {
        perror("\'accept\' failed");
        exit(1);
    }
	/* Extract the account name from the packet, store in nameBuf */
	/* Look up account balance, store in balance */
    if (-1 == recv(clientSock, reqBuf, RCVBUFSIZE, 0))
    {
        perror("\'recv\' failed");
        exit(1);
    }

    handle_request(reqBuf);

	/* Return account balance to client */
    if (-1 == send(clientSock, resBuf, SNDBUFSIZE, 0))
    {
        perror("\'send\' failed");
        exit(1);
    }
    memset(reqBuf, 0, RCVBUFSIZE);
    close(clientSock);
    }

}

void *timer(void *acc_hash)
{
    int hash = *(int *) acc_hash;
    sleep(60);
    counters[hash]--;
    printf("counter[%d]-- => %d\n", hash, counters[hash]);
    return 0;
}

void start_timer(int acc_hash)
{
    pthread_t timer_id;
    pthread_create(&timer_id, NULL, timer, &acc_hash);
    printf("Counter[%d]++ => %d\n", acc_hash, counters[acc_hash]);
}

void handle_request(char buffer[])
{	
    char *message = buffer;
    char *opcode = strsep(&message, " ");
    memset(resBuf, 0, SNDBUFSIZE);

    if (0 == strncmp(opcode, "BAL", 3))
    {
        char *acc_name = strsep(&message, " ");
        int acc_hash = hash(acc_name);
        if (-1 == acc_hash)
        {
            sprintf(resBuf, "%d", -1);
            return;
        }
        sprintf(resBuf, "%d", balance[acc_hash]);
    }
    else if (0 == strncmp(opcode, "WITHDRAW", 8))
    {
        char *acc_name = strsep(&message, " ");
        int acc_hash = hash(acc_name);
        if (-1 == acc_hash)
        {
            sprintf(resBuf, "%d", -1);
            return;
        }
        if (3 == counters[acc_hash])
        {
            sprintf(resBuf, "%d", -3);
            return;
        }
        int amount;
        sscanf(strsep(&message, " "), "%d", &amount);
        if (amount > balance[acc_hash])
        {
            sprintf(resBuf, "%d", -2);
            return;
        }
        balance[acc_hash] -= amount;
        sprintf(resBuf, "%d", 0);
        counters[acc_hash]++;
        start_timer(acc_hash);
    }
    else if (0 == strncmp(opcode, "TRANSFER", 8))
    {
        char *from_acc_name = strsep(&message, " ");
        int from_acc_hash = hash(from_acc_name); 
        char *to_acc_name = strsep(&message, " ");
        int to_acc_hash = hash(to_acc_name); 
        if (-1 == from_acc_hash || -1 == to_acc_hash)
        {
            sprintf(resBuf, "%d", -1);
            return;
        }
        if (3 == counters[from_acc_hash])
        {
            sprintf(resBuf, "%d", -3);
            return;
        }
        int amount;
        sscanf(strsep(&message, " "), "%d", &amount);
        if (amount > balance[from_acc_hash])
        {
            sprintf(resBuf, "%d", -2);
            return;
        }
        balance[from_acc_hash] -= amount;
        balance[to_acc_hash] += amount;
        sprintf(resBuf, "%d", 0);
        counters[from_acc_hash]++;
        start_timer(from_acc_hash);
    }
}

int hash(char *acc_name)
{
    if (0 == strcmp(acc_name, "mySavings")) return 0;
    if (0 == strcmp(acc_name, "myChecking")) return 1;
    if (0 == strcmp(acc_name, "myCD")) return 2;
    if (0 == strcmp(acc_name, "my401k")) return 3;
    if (0 == strcmp(acc_name, "my529")) return 4;
    return -1;
}

