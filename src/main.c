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
#include <locale.h>
#include "server.h"
#include "output.h"

int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");
    SSL_CTX * sslctx = InitializeSSL("../ssl/cert.pem");
    int sd = InitializeSocket(8443);
    listen(sd, 5);
    while (1) {
        int client = accept(sd, NULL, NULL);

        printf("Пришел запрос.\n");

        SSL * ssl = SSL_new(sslctx);
        SSL_set_fd(ssl, client);
        if (SSL_accept(ssl) <= 0) { 
            SSL_clear(ssl);
            close(client);
            continue;
        }
      int pid = fork();
        if (pid != 0) { 
            SSL_clear(ssl);
            close(client);
            continue;
        }
        char response[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n";
        char header[1024];
        bzero(header,1024);
        int s = 0;
        int n = 0;
        while (strcmp(header + s - strlen("\r\n\r\n"), "\r\n\r\n") != 0) {
            n = SSL_read(ssl,header+s,1);
            s += n;
        }
        
        if (strstr(header,"POST /361959180:AAFYVP6qweMx-3hd-eS0-fZEaLdCnkhE9GI/ HTTP/1.1\r\n") == NULL) {
                    SSL_clear(ssl);
                    close(client);
                    exit(0);
        }
        if (strstr(header, "Content-Type: application/json") == NULL) {
            SSL_clear(ssl);
            close(client);
            exit(0);
        }
        
        int len = atoi(strstr(header, "Content-Length: ") + strlen("Content-Length: "));

        char body[len+2]; 
        bzero(body, len+2);
        n = 0;
        s = 0;
        while (len - s > 0) {
            n = SSL_read(ssl, body + s, len - s);
            s += n;
        }
        char msg[4096];
        int chat_id = atoi(strstr(body, "\"chat\":{\"id\":") + strlen("\"chat\":{\"id\":"));

        
        
        if(!game(msg, body, chat_id)) {
            output(body, msg);
        }
        
        SSL_write(ssl, response, (int)strlen(response));
        SSL_clear(ssl);
        SSL_free(ssl);
        close(client);  
        
        SendMessage(chat_id, msg);
        printf("Ответ отправлен.\n\n\n");
    exit(0);
    }
}
