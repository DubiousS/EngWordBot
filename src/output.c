#include "output.h"


int output(char *body, char *msg)
{
    int i = 0;
    char *text = strstr(body, "\"text\":\"") + strlen("\"text\":\"");
    while(*text != '\0') {
        if(*(text + i) == '\"') {
            *(text + i) = '\0';
            break;
        } else {
            i++;
        }
    }
    if(!strcmp(text, "/start")) {
        strcpy(msg, "Привет, меня завут Арнольд и я не бот, но перевожу слова. Я сижу гуглю каждое слово чтобы помочь тебе заучить слова.\nВот мой функционал: \n\n1. /start\n2. /rus <english word>\n3. /eng <русское слово>\n4. /start_eng\n Кроме этого я ничего не умею, а нет, еще могу повторять за тобой.\n");
    } else if(!strcmp(text, "/start_eng")) {
        strcpy(msg, "Игра");
    } else {
        char temp[5];
        temp[4] = '\0';
        strcpy(temp, text);
        if(!strcmp(temp, "/rus")) {
            strcpy(msg, "translate eng");
        } else if(!strcmp(temp, "/eng")) {
            strcpy(msg, "translate rus");
        } else strcpy(msg, text);
    }
    printf("input - ");
    return 1;
}

void SendMessage(int chat_id, char msg[]) 
{
    printf("send\n");
    int port = 443;
    char host[] =  "api.telegram.org";
    char header[] = "POST /bot361959180:AAFYVP6qweMx-3hd-eS0-fZEaLdCnkhE9GI/sendMessage HTTP/1.1\r\nHost: files.ctrl.uz\r\nContent-Type: application/json\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s";

    char tpl[] = "{\"chat_id\":%d,\"text\":\"%s\"}";
    char body[strlen(tpl)+strlen(msg)+16];
    bzero(body, strlen(tpl)+strlen(msg)+16);
    sprintf(body,tpl,chat_id,msg);
    char request[strlen(header)+strlen(body)+4];
    bzero(request,strlen(header)+strlen(body)+4);
    sprintf(request, header, strlen(body), body);
    struct hostent *server; 
    struct sockaddr_in serv_addr;
    int sd;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sd < 0) exit(-5);
    
    server = gethostbyname(host);
    
    if (server == NULL) exit(-6); 
    
    bzero(&serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    
    if (connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        exit(-6);
    }

    SSL_CTX * sslctx = SSL_CTX_new(TLSv1_client_method());
    SSL * cSSL = SSL_new(sslctx);
    SSL_set_fd(cSSL, sd);
    SSL_connect(cSSL); 
    SSL_write(cSSL,request,(int)strlen(request));
    char str[1024];
    SSL_read(cSSL, str, 1024);
    SSL_clear(cSSL);
    SSL_CTX_free(sslctx);
    close(sd);
}
