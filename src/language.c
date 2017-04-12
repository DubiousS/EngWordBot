#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int w_strcmp(const wchar_t *one, const wchar_t *two) 
{

    while(1) {
        if(*one == *two) {
            if(*one == L'\0' && *two == L'\0') {
                break;
            }
            if(*one == L'\0' || *two == L'\0') {
                return 0;
            }
            one++;
            two++;
        } else return 0;
    }
    return 1;
}

FILE *skip_string(FILE *in) 
{
    wchar_t word;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == '\n') {
            return in;
        }
    }
    return NULL;
}

FILE *skip_str_to_rus_sym(FILE *in, const wchar_t *input_word) 
{
    wchar_t word;
    fseek(in, 0, SEEK_SET);
    while(fscanf(in,"%C", &word) != EOF) {
        if(word == *input_word) {
            fseek(in, -2, SEEK_CUR);
            return in;
        } else {
            skip_string(in);
        }
    }
   return NULL;
}

FILE *translate_rus(FILE *in, const wchar_t *input_word) 
{
    wchar_t tmp;
    wchar_t word[64];
    fseek(in, 0, SEEK_SET);
    in = skip_str_to_rus_sym(in, input_word);
    int i = 0;
    while(fscanf(in,"%C", &tmp) != EOF) {
        if(tmp == '|') {
            word[i] = '\0';
            if(w_strcmp(word, input_word)) {
                fseek(in, i * -2 - 1, SEEK_CUR);
                return in;
            } else {
                i = 0;
                skip_string(in);   
                continue;
            }
        }
        word[i] = tmp;
        i++;
    }
    return NULL;
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