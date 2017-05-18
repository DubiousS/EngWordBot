#ifndef OUTPUT_H
#define OUTPUT_H

int convert(char *str);
void SendMessage(int chat_id, char msg[]);
int output(char *body, char *msg);
int game(char *msg, char *body, int id);


#endif