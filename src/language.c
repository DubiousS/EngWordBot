#include "language.h"

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
        if(word == L'\n') {
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
    if(in == NULL) return NULL;
    int i = 0, fixed = 0;
    while(fscanf(in,"%C", &tmp) != EOF) {
        if(isascii(tmp)) {
            fixed++;
        } else fixed += 2;

        if(tmp == L'|') {
            word[i] = L'\0';
            i++;
            if(w_strcmp(word, input_word)) {
                fseek(in, -(fixed), SEEK_CUR);
                return in;
            } else {
                fixed = 0;
                i = 0;
                if(skip_string(in) == NULL) return NULL;
                continue;
            }
        }
        word[i] = tmp;
        i++;
    }
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

int read_words(FILE *in, char *rus, char *eng) 
{
    int i = 0;
    wchar_t word;
    wchar_t str[64];
    while(1) {
        fscanf(in,"%C", &word);
        if(word == L'|') {
            str[i] = L'\0';
            break;
        }
        str[i] = word;
        i++;
    }
    sprintf(rus, "%S", str);
    i = 0;
    while(1) {
        fscanf(in,"%C", &word);
        if(word == L'\n') {
            str[i] = L'\0';
            break;
        }
        str[i] = word;
        i++;
    }
    sprintf(eng, "%S", str);
    return 1;
}

int message(char const *input_word, char *msg, char const *type)
{
    char rus[1024];
    char eng[1024];
    FILE *input = fopen("../src/rus-eng.txt", "rt");
    if(!input){
        perror("error");
        return -1;
    }
    wchar_t word[1024];
    swprintf(word, 1024, L"%s", input_word);
    printf("%S\n", word);
    if(!strcmp(type, "rus")) {
        input = translate_rus(input, word);
        if(input != NULL) {
            read_words(input, rus, msg);
        } else strcpy(msg, "Not Found");
    } else if(!strcmp(type, "eng")) {
        input = translate_eng(input, word);
        if(input != NULL) {
            read_words(input, msg, eng);
        } else strcpy(msg, "Not Found");
    }
    if(input != NULL) {
        fclose(input);
    }
    return 0;
}