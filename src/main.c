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
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if (sd < 0) exit(-1);
    struct sockaddr_in s_addr;

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    //s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_addr.s_addr = inet_addr("5.128.229.81:8443");

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
int main(int argc, char const *argv[])
{
	SSL_CTX * sslctx = InitializeSSL("cert.pem"); //Созданный нами файл из приватного ключа и публичного сертификата
    int sd = InitializeSocket(8443);//Порт который вы указали при установке WebHook
    printf("good 0\n");
    listen(sd, 5); //Слушаем подключения на созданном сокете
	while (1) { //Запускаем бесконечный цикл
        printf("good 1\n");
        int client = accept(sd, NULL, NULL); //функция accept ждет новое подключение, в качестве параметров принимает сокет, указатель на структуру sockaddr, и указатель на размер этой структуры и записывает туда данные подключения, так как нам необязательно знать подробности подключения отправим NULL, функция возвращает сетевой дескриптор. 
        printf("good 2\n");
        close(sd);
    }
	return 0;
}