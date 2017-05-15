#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>

#ifndef LANGUAGE_H
#define LANGUAGE_H

int w_strcmp(const wchar_t *one, const wchar_t *two);
int read_words(FILE *in, char *rus, char *eng);
FILE *skip_string(FILE *in);
FILE *skip_str_to_rus_sym(FILE *in, const wchar_t *input_word);
FILE *translate_rus(FILE *in, const wchar_t *input_word);
FILE *translate_eng(FILE *in, const wchar_t *input_word);
int message(char const *input_word, char *msg, char const *type);

#endif