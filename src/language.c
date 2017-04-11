#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

FILE *skip_string(FILE *in) 
{
    wchar_t word;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '\n') {
            break;
        }
    }
    return in;
}

int search_rus(FILE *in, wchar_t *input_word, int length) 
{
    wchar_t word;
    int i = 0;
    while(fscanf(in,"%C", &word) != EOF) {
        if(word == '|') {
            in = skip_string(in);
        }
        if(word = *input_word) {
            printf("good\n");
            break;
        }
    }
    return 1;
}



int search_eng(FILE *in, wchar_t *input_word) 
{
    wchar_t word;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '|') {
            break;
        }
    }
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '\n') {
            break;
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
    search_rus(in, L"авиапочтa", sizeof(L"авиапочта")/sizeof(wchar_t));
    printf("\n");
    search_eng(in, L"р");
    printf("\n");
    fclose(in);
    return 0;
}