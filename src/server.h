#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <unistd.h>
#include <openssl/err.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netdb.h>
#ifndef SERVER_H
#define SERVER_H

int InitializeSocket(int port);
SSL_CTX * InitializeSSL(char certificate[]);

#endif