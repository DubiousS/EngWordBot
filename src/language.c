#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>

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
        if(fscanf(in,"%C", &word) == EOF) {
            return NULL;
        }
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
    if(in == NULL) {
        fseek(in, 0, SEEK_SET);
        return NULL;
    }
    int i = 0, fixed = 0;
    while(fscanf(in,"%C", &tmp) != EOF) {
        if(isascii(tmp)) {
            fixed++;
        } else fixed += 2;

        if(tmp == '|') {
            word[i] = '\0';
            i++;
            if(w_strcmp(word, input_word)) {
                fseek(in, -(fixed), SEEK_CUR);
                return in;
            } else {
                fixed = 0;
                i = 0;
                if(skip_string(in) == NULL) {
                    fseek(in, 0, SEEK_SET);
                    return NULL;
                }   
                continue;
            }
        }
        word[i] = tmp;
        i++;
    }
    fseek(in, 0, SEEK_SET);
    return NULL;
}



FILE *translate_eng(FILE *in, const wchar_t *input_word) 
{
    wchar_t tmp;
    wchar_t word[64];
    fseek(in, 0, SEEK_SET);
    int i = 0, f = 0, fixed = 0;
    while(fscanf(in,"%C", &tmp) != EOF) {
        if(isascii(tmp)) {
            fixed++;
        } else fixed += 2;

        if(f == 0) {
            if(tmp == L'|') {
                f = 1;
                fscanf(in,"%C", &tmp);
               } else {
                continue;
            }
        }
        if(tmp == L'\n' && f == 1) {
            word[i] = L'\0';
            i++;
            if(w_strcmp(word, input_word)) {
                fseek(in, -(fixed + 1), SEEK_CUR);
                return in;
            } else {
                fixed = 0;
                f = 0;
                i = 0;
                continue;
            }
        }
        word[i] = tmp; 
        i++;
    }
    return NULL;

}