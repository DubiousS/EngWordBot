#ifndef LANGUAGE_H
#define LANGUAGE_H

int w_strcmp(const wchar_t *one, const wchar_t *two);
FILE *skip_string(FILE *in);
FILE *skip_str_to_rus_sym(FILE *in, const wchar_t *input_word);
FILE *translate_rus(FILE *in, const wchar_t *input_word);
FILE *translate_eng(FILE *in, const wchar_t *input_word);


#endif