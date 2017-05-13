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
void SendMessage(int chat_id, char msg[]) {
    printf("send\n");
    int port = 443;
    char host[] =  "api.telegram.org"; //Адрес и порт всегда одинаковые
   //Создадим шаблон HTTP запроса для отправки сообщения, в виде форматированной строки
    char header[] = "POST /bot361959180:AAFYVP6qweMx-3hd-eS0-fZEaLdCnkhE9GI/sendMessage HTTP/1.1\r\nHost: files.ctrl.uz\r\nContent-Type: application/json\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s";
    //Шаблон тела для отправки сообщения
    char tpl[] = "{\"chat_id\":%d,\"text\":\"%s\"}";
    char body[strlen(tpl)+strlen(msg)+16];
    bzero(body, strlen(tpl)+strlen(msg)+16);
    sprintf(body,tpl,chat_id,msg); //Как printf, только печатаем в char[] 
    char request[strlen(header)+strlen(body)+4];
    bzero(request,strlen(header)+strlen(body)+4);
    sprintf(request, header, strlen(body), body);
   //Подготовили наш запрос, теперь создаем подключение
    struct hostent *server; 
    struct sockaddr_in serv_addr;
    int sd;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sd < 0) exit(-5);
    
    server = gethostbyname(host); //Данная функция получает ip и еще некоторые данные по url
    
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
    SSL_write(cSSL,request,(int)strlen(request)); //Отправляем наш запрос, в идеале его надо отправлять так же как мы считывали данные, то есть с проверкой на кол-во отправленных байт
    char str[1024];
    SSL_read(cSSL, str, 1024); //Считываем ответ и закрываем соединение
    SSL_clear(cSSL);
    SSL_CTX_free(sslctx);
    close(sd);
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


int main() {
    SSL_CTX * sslctx = InitializeSSL("cert.pem"); //Созданный нами файл из приватного ключа и публичного сертификата
    int sd = InitializeSocket(8443);  //Порт который вы указали при установке WebHook
    listen(sd, 5); //Слушаем подключения на созданном сокете
    while (1) { //Запускаем бесконечный цикл
        int client = accept(sd, NULL, NULL); //функция accept ждет новое подключение, в качестве параметров принимает сокет, указатель на структуру sockaddr, и указатель на размер этой структуры и записывает туда данные подключения, так как нам необязательно знать подробности подключения отправим NULL, функция возвращает сетевой дескриптор. 
        SSL * ssl = SSL_new(sslctx); //Cоздаем ssl дескриптор
        SSL_set_fd(ssl, client); //Переключаем обычный дескриптор на защищенный 
        if (SSL_accept(ssl) <= 0) { //Пытаемся принять подключение, если ошибка то закрываем соединение и возвращаемся к началу цикла
            SSL_clear(ssl);
            close(client);
            continue;
        }
        //Для увеличения производительности будем использовать fork() и обрабатывать соединение в дочернем процессе, а родительский процесс вернем к ожиданию новых подключений
     int pid = fork();
        if (pid != 0) { //Если это родитель, то закрываем подключение и возвращаемся к началу цикла
            SSL_clear(ssl);
            close(client);
            continue;
        }
        char response[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n"; //Наш HTTP response
        char header[1024];
        bzero(header,1024); //Выделили массив для записи в него заголовков запроса и на всякий случай занулили там все записи.
        int s = 0;
        int n = 0;
        while (strcmp(header + s - strlen("\r\n\r\n"), "\r\n\r\n") != 0) { //strcmp Сравнивает две строки и если они равны возвращает 0, в нашем случае сравниваем последние strlen("\r\n\r\n") байт с "\r\n\r\n", то есть ищем конец заголовка
            n = SSL_read(ssl,header+s,1); //Считываем данные по одному байту в header + s, s - общее кол-во считанных байт
            s += n; //n - кол-во считанных байт за раз
        }
        //Все, заголовки считаны, теперь нам надо проверить метод, uri, content-type и вытащить content-length запроса.
        if (strstr(header,"POST /361959180:AAFYVP6qweMx-3hd-eS0-fZEaLdCnkhE9GI/ HTTP/1.1\r\n") == NULL) { //Ищем вхождение строки POST .... в header, если его нет то возвращается NULL, значит пришел неверный запрос, закрываем подключение и завершаем дочерний процесс
                    SSL_clear(ssl);
                    close(client);
                    exit(0);
        }
        //Также проверим тип данных, должен быть application/json;
               if (strstr(header, "Content-Type: application/json") == NULL) {
                    SSL_clear(ssl);
                    close(client);
                    exit(0);
                }
        //Если все нормально, то узнаем размер тела
        int len = atoi(strstr(header, "Content-Length: ") + strlen("Content-Length: ")); //strstr возвращает указатель не первое вхождение указанной строки, то есть на "Content-Length: ", а кол-во байт записано дальше после этой строки, поэтому прибавляем длину строки "Content-Length: " и приводим строку к типу int функцией atoi(char *);

        char body[len+2]; 
        bzero(body, len+2); //Создаем массив для тела, на этот раз мы точно знаем сколько байт нам понадобится, но создаем с запасом, дабы не оказалось что в памяти сразу после нашей строки что-то записано
        n = 0;
        s = 0;
        while (len - s > 0) { //Так как мы четко знаем сколько данных нам надо считать просто считываем пока не считаем нужное кол-во
            n = SSL_read(ssl, body + s, len - s); //Конечно можно было считать целиком все данные, но бывают случаи при плохом соединении, за раз все данные не считываеются, и функция SSL_read возвращает кол-во считанных байт
            s += n;
        }
        printf("%s\n", body);
        SSL_write(ssl, response, (int)strlen(response));
        SSL_clear(ssl);
        SSL_free(ssl);
        close(client);  
        int chat_id = atoi(strstr(body, "\"chat\":{\"id\":") + strlen("\"chat\":{\"id\":"));
        char msg[] = "Fuck this ssl server!ЫЫ!!!";
        SendMessage(chat_id, msg);
    exit(0);
    }
}
