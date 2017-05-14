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
#include "server.h"
#include "output.h"

int main() {
    SSL_CTX * sslctx = InitializeSSL("../ssl/cert.pem");
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
        char msg[4096];
        output(body, msg);//формирование ответного сообщения

        SSL_write(ssl, response, (int)strlen(response));
        SSL_clear(ssl);
        SSL_free(ssl);
        close(client);  
        int chat_id = atoi(strstr(body, "\"chat\":{\"id\":") + strlen("\"chat\":{\"id\":"));
        SendMessage(chat_id, msg);
    exit(0);
    }
}
