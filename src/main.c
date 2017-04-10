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


int InitializeSocket(int port) {
    int sd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sd < 0) exit(-1);
    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(port);
    if (bind(sd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        printf("Binding Error!\n");
        exit(-3);
    }
    return sd;
}

SSL_CTX * InitializeSSL(char certificate[]) {
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_library_init();
    SSL_CTX * sslctx = SSL_CTX_new(TLSv1_2_server_method());
    if (SSL_CTX_use_certificate_file(sslctx, certificate , SSL_FILETYPE_PEM) <= 0) {
        exit(-2);
    }
    if (SSL_CTX_use_PrivateKey_file(sslctx,  certificate, SSL_FILETYPE_PEM) <= 0) {
        exit(-2);
    }
    if (!SSL_CTX_check_private_key(sslctx)) {
       exit(-2);
    }
    return sslctx;
}

int main()
{
	SSL_CTX * sslctx = InitializeSSL("cert.pem"); //Create sertificate
    int sd = InitializeSocket(443);  //port initialized
    listen(sd, 5); //Check socket
    while (1) {//infinity cycle
    	int client = accept(sd, NULL, NULL);//wait new connect
    	SSL * ssl = SSL_new(sslctx);//ssl descript
    	SSL_set_fd(ssl, client);//change standart descript to security
    	if (SSL_accept(ssl) <= 0) { //Trying to get connection if false close connection and location to begining cycle
            SSL_clear(ssl);
            close(sd);
            continue;
        }
    }
    return 0;
}