#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
int read_rus(FILE *in, wchar_t *input_word) 
{
    wchar_t word;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '|') {
            break;
        } else {

        }
        printf("%C", word);
    }
    return 1;
}

int read_eng(FILE *in, wchar_t *input_word) 
{
    wchar_t word;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '|') {
            break;
        } else {

        }
    }
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '\n') {
            break;
        } else {

        }
        printf("%C", word);
    }
    return 1;
}

int main()
{   
    setlocale(LC_ALL, "ru_RU.UTF-8");

	FILE *in = fopen("rus-eng.txt", "r");
    if(!in){
        perror("error");
        return -1;
    }
    read_rus(in, L"р");
    printf("\n");
    read_eng(in, L"р");
    printf("\n");
    fclose(in);
    return 0;
}