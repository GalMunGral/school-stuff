/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:   Wenqi He	
* PROJECT:	CS 3251 Project 1 - Professor Ellen Zegura 
* DESCRIPTION:	Network Client Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>		    /* for printf() and fprintf() */
#include <sys/socket.h>		    /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>		    /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
/* Constants */
#define RCVBUFSIZE 512		    /* The receive buffer size */
#define SNDBUFSIZE 512		    /* The send buffer size */
#define REPLYLEN 32

void handle_command(int argc, char *argv[], char *buffer);
void handle_response(char *argv[], int resVal);
void fprint_time(FILE *file);
time_t cur_time;
FILE *log_file;

/* The main function */
int main(int argc, char *argv[])
{
    int clientSock;		    /* socket descriptor */
    struct sockaddr_in serv_addr;   /* server address structure */

    // char *accountName;		    /* Account Name  */
    char *servIP;		    /* Server IP address  */
    unsigned short servPort;	    /* Server Port number */
    

    char sndBuf[SNDBUFSIZE];	    /* Send Buffer */
    char rcvBuf[RCVBUFSIZE];	    /* Receive Buffer */
    
    int balance;		    /* Account balance */
    int resVal;         /* Account balance or error code */

    /* Get the Account Name from the command line */
    // if (argc != 6 && argc != 8) 
    // {
	// printf("Incorrect number of arguments. The correct format is:\n\taccountName serverIP serverPort");
	// exit(1);
    // }
    // accountName = argv[1];
    memset(&sndBuf, 0, SNDBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Get the addditional parameters from the command line */
    if (argc < 4)
    {
        printf("Too few arguments.\n");
        exit(1);
    }
    servIP = argv[1];

    if (0 == sscanf(argv[2], "%hu", &servPort))
    {
        printf("Incorrect format: \'%s\' is not a valid port number\n", argv[2]);
        exit(1);
    }

    /* Create a new TCP socket*/
    clientSock = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct the server address structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(servPort);
    if (0 == inet_aton(servIP, &(serv_addr.sin_addr)))
    {
        printf("Invalid server IP \'%s\'.\n", servIP);
        exit(1);
    }


    /* Establish connecction to the server */
    if (-1 == connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        perror("\'connect\' failed");
        exit(1);
    }
    
    handle_command(argc, argv, sndBuf);

    /* Send the string to the server */
    if (-1 == send(clientSock, sndBuf, SNDBUFSIZE, 0))
    {
        perror("\'send\' failed");
        exit(1);
    }

    /* Receive and print response from the server */
    if (-1 == recv(clientSock, rcvBuf, RCVBUFSIZE, 0))
    {
        perror("\'recv\' failed");
        exit(1);
    }
    // printf("%s\n", accountName);
    sscanf(rcvBuf, "%d", &resVal);
    handle_response(argv, resVal);
    
    return 0;
}

void fprint_time(FILE *file)
{
    time(&cur_time);
    char *time_str = ctime(&cur_time);
    fprintf(file, "[");
    fwrite(time_str, strlen(time_str)-1, 1, file);
    fprintf(file, "]\n");
}

void handle_response(char *argv[], int resVal)
{
    char *res_msg;

    /* Open a log file */
    log_file = fopen("he-output.txt", "a"); 
    fprintf(log_file, "RESPONSE ");
    fprint_time(log_file);

    if (-1 == resVal)
    {
        res_msg = "ERROR: Account does not exist!\n";
        printf("%s", res_msg);
        fprintf(log_file, "\t%s\n", res_msg);
        exit(1);
    }
    else if (-2 == resVal)
    {
        res_msg = "ERROR: Insufficient fund!\n";
        printf("%s", res_msg);
        fprintf(log_file, "\t%s\n", res_msg);
        exit(1);
    }
    else if (-3 == resVal)
    {
        res_msg = "ERROR: Too Many withdrawals in a minute!\n";
        printf("%s", res_msg);
        fprintf(log_file, "\t%s\n", res_msg);
        exit(1);
    }
    if (0 == resVal)
    {
        res_msg = "OK\n";
        printf("%s", res_msg);
        fprintf(log_file, "\t%s\n", res_msg);
        exit(1);
    }

    if (0 == strncmp(argv[3], "BAL", 3))
    {
        printf("Balance is: %i\n", resVal);
        fprintf(log_file, "\tBalance is: %i\n\n", resVal);
    }
    fclose(log_file);
}

void handle_command(int argc, char *argv[], char *buffer)
{
    /* Open a log file */
    log_file = fopen("he-output.txt", "a"); 

    if (0 == strncmp(argv[3], "BAL", 3))
    {
        if (argc != 5)
        {
            printf("Incorrect number of arguments. The correct format is:\n\tBAL [account-name]\n");
            exit(1);
        }
        sprintf(buffer, "%s %s", argv[3], argv[4]);
    }
    else if (0 == strncmp(argv[3], "WITHDRAW", 8))
    {
        if (argc != 6)
        {
            printf("Incorrect number of arguments. The correct format is:\n\tWITHDRAW [account-name] [amount]\n");
            exit(1); 
        }
        if (0 == strtol(argv[5], NULL, 10))
        {
            printf("Incorrect format: \'%s\' is not a number\n", argv[5]);
            exit(1);
        }
        sprintf(buffer, "%s %s %s", argv[3], argv[4], argv[5]);
    }
    else if (0 == strncmp(argv[3], "TRANSFER", 8))
    {
        if (argc != 7)
        {
            printf("Incorrect number of arguments. The correct format is:\n\tTRANSFER [from-account] [to-account] [amount]\n");
            exit(1); 
        }
        if (0 == strtol(argv[6], NULL, 10))
        {
            printf("Incorrect format: \'%s\' is not a number\n", argv[6]);
            exit(1);
        }
        sprintf(buffer, "%s %s %s %s", argv[3], argv[4], argv[5], argv[6]);
    }
    else
    {
        printf("No command named \'%s\'\n", argv[3]);
        exit(1);
    }

    fprintf(log_file, "REQUEST ");
    fprint_time(log_file);
    fprintf(log_file, "\t%s\n", buffer);
    fclose(log_file);
}