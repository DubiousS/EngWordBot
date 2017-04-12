#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "language.h"

int main(int argc, char const *argv[])
{ 
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t word;
    FILE *in = fopen("rus-eng.txt", "r");
    if(!in){
        perror("error");
        return -1;
    }
    in = translate_rus(in, L"авеню");
    if(in != NULL) {
        while(1) {
            fscanf(in,"%C", &word);
            if(word == '\n') {
                break;
                break;
            }
            printf("%C", word);
        }
    } else printf("Not Found\n");
    fclose(in);
    return 0;
}