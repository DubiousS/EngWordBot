#include "output.h"


int convert(char *str)
{
    char temp[7];
    char result[strlen(str)];
    bzero(result, strlen(str));
    char *mass[] = {"\\u0410","\\u0411","\\u0412","\\u0413","\\u0414","\\u0415","\\u0416",
                    "\\u0417","\\u0418","\\u0419","\\u041a","\\u041b","\\u041c","\\u041d",
                    "\\u041Ee","\\u041f","\\u0420","\\u0421","\\u0422","\\u0423","\\u0424",
                    "\\u0425","\\u0426","\\u0427","\\u0428","\\u0429","\\u042a","\\u042b",
                    "\\u042Cc","\\u042d","\\u042e","\\u042f","\\u0401", "\0"};

    char *mass_two[] = {"А","Б","В","Г","Д","Е",
                        "Ж","З","И","Й","К","Л","М",
                        "Н","О","П","Р","С","Т","У",
                        "Ф","Х","Ц","Ч","Ш","Щ","Ъ",
                        "Ы","Ь","Э","Ю","Я", "Ё"};

    char *mass_r[] = {"\\u0430","\\u0431","\\u0432","\\u0433","\\u0434","\\u0435","\\u0436",
                      "\\u0437","\\u0438","\\u0439","\\u043a","\\u043b","\\u043c","\\u043d",
                      "\\u043e","\\u043f","\\u0440","\\u0441","\\u0442","\\u0443","\\u0444",
                      "\\u0445","\\u0446","\\u0447","\\u0448","\\u0449","\\u044a","\\u044b",
                      "\\u044c","\\u044d","\\u044e","\\u044f","\\u0451", "\0"};

    char *mass_r_two[] = {"а","б","в","г","д","е","ж","з","и","й","к","л","м","н","о","п",
                          "р","с","т","у","ф","х","ц","ч","ш","щ","ъ","ы","ь","э","ю","я","ё"};


    int i = 0, k = 0, j = 0, f = 0;
    while(i < strlen(str)) {
        if(*(str + i) == '\\' && *(str + i + 1) == 'u' && *(str + i + 2) == '0' && *(str + i + 3) == '4') {
            if(strlen((str + i)) >= 5) {
                temp[0] = *(str + i);
                temp[1] = *(str + i + 1);
                temp[2] = *(str + i + 2);
                temp[3] = *(str + i + 3);
                temp[4] = *(str + i + 4);
                temp[5] = *(str + i + 5);
                temp[6] = '\0';
                k = 0;
                while(*mass[k] != '\0') {
                    if(!strcmp(temp, mass[k])) {
                        strcpy(result + j, mass_two[k]);
                        j += strlen(mass_two[k]);
                        f = 0;
                        i += 6;
                        k++;
                        break;
                    }
                    if(!strcmp(temp, mass_r[k])) {
                        strcpy(result + j, mass_r_two[k]);
                        j += strlen(mass_r_two[k]);
                        f = 0;
                        i += 6;
                        k++;
                        break;
                    }
                    f = 1;
                    k++;
                }
                if(f) {
                    i++;
                    f = 0;
                }
            }
        } else {
            result[j] = *(str + i);
            j++;
            i++;
            continue;
        }
    }
    result[j] = '\0';
    strcpy(str, result);
    return 0;
}
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
    convert(text);
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
                message(word, msg, "rus");
            }
        } else if(!strcmp(temp, "/rus")) {
            i = 5;
            if(strlen(text) > 5) {
                word = text + i;
                message(word, msg, "eng");
            }
        } else strcpy(msg, text);
    }
    printf("Полученное сообщение\n_________________________________________________________\n - %s\n", text);
    return 1;   
}

void SendMessage(int chat_id, char msg[]) 
{
    printf("Ответ\n_________________________________________________________\n - %s\n", msg);
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
