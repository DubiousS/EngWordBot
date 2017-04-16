#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "language.h"

int main(int argc, char const *argv[])
{ 
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wchar_t word;
    FILE *in = fopen("rus-eng.txt", "rt");
    if(!in){
        perror("error");
        return -1;
    }
    in = translate_rus(in, L"дом");
    //in = translate_eng(in, L"accident costs");
    if(in != NULL) {
        while(1) {
            fscanf(in,"%C", &word);
            if(word == '\n') {
                break;
            }
            printf("%C", word);
        }
    } else printf("Not Found\n");
    if(in != NULL) {
        fclose(in);
    }
    return 0;
}