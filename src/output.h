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
#include <wchar.h>
#include <string.h>
#include "language.h"

#ifndef OUTPUT_H
#define OUTPUT_H

int convert(char *str);
void SendMessage(int chat_id, char msg[]);
int output(char *body, char *msg);
int game(char *msg);


#endif