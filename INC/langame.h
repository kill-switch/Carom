#ifndef LANGAME_H
#define LANGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
void broadcastData();
void *acceptData(void *ptr);
void *acceptClient(void *ptr);
void *transmitData(void *value);
void createServer(int portno);
void createClient(int portno , char *hostname);
int recieveData(void *in,int sizein);
void sendData(void *data , int noofbytes, char client);
#endif
