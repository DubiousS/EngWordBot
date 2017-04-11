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

FILE *skip_string_to_bukva(FILE *in, wchar_t *input_word) 
{
    wchar_t word;
    fseek(in, 0, SEEK_SET);
    while(fscanf(in,"%C", &word) != EOF) {
        if(word == *input_word) {
            fseek(in, -sizeof(wchar_t) + 2, SEEK_CUR);
            return in;
        } else {
            skip_string(in);
        }
    }
   return NULL;
}

int search_rus(FILE *in, wchar_t *input_word, int length) 
{
    wchar_t word;
    int i = 0;
    while(fscanf(in,"%C", &word) != EOF) {
        if(word == '|') {
            break;
        }
        printf("%C", word);
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
    in = skip_string_to_bukva(in, L"а");
    search_rus(in, L"авиапочтa", sizeof(L"авиапочта")/sizeof(wchar_t));
    printf("\n");
    search_eng(in, L"р");
    printf("\n");
    fclose(in);
    return 0;
}