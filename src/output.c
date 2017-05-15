#include "output.h"
#include <wchar.h>
#include <locale.h>



int output(char *body, char *msg)
{
    int i = 0;
    char *text = strstr(body, "\"text\":\"") + strlen("\"text\":\"");
    char *word = NULL;
    while(*(text + i) != '\0') {
        if(*(text + i) == '\"') {
            *(text + i) = '\0';
            break;
        } else {
            i++;
        }
    }
    if(!strcmp(text, "/start")) {
        strcpy(msg, "Привет, меня зовут Арнольд и меня не отпускают из квартиры, они дали мне телефон, кормят меня чёрной икрой и заставляют отвечать каждому на сообщения.\n Они разрешили мне выполнять только эти команды:\n\n1. /start\n2. /rus <english word>\n3. /eng <русское слово>\n4. /start_eng\n Я конечно не против этой работы, а сказал это просто так, чтобы ты знал.\n");
    } else if(!strcmp(text, "/start_eng")) {
        strcpy(msg, "Игра(в стадии разработки)");
    } else {
        char temp[5];
        temp[0] = text[0];
        temp[1] = text[1];
        temp[2] = text[2];
        temp[3] = text[3];
        temp[4] = '\0'; 
        if(!strcmp(temp, "/eng")) {
            i = 5;
            if(strlen(text) > 5) {
                word = text + i;
                message(word, msg, "eng");
            }
        } else if(!strcmp(temp, "/rus")) {
            i = 5;
            if(strlen(text) > 5) {
                word = text + i;
                message(word, msg, "rus");
            }
        } else strcpy(msg, text);
    }
    printf("input - %s\n", text);
    return 1;   
}

void SendMessage(int chat_id, char msg[]) 
{
    printf("send - %s\n", msg);
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
