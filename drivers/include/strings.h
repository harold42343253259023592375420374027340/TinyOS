#ifndef STRINGS_H
#define STRINGS_H

int strcmp(char *str1, char *str2);
void strcpy(char *to, int len,char *from);
int strlen(char *array);
void splitstr(char *str, char token, char cmds[10][32]);
void memset(char* array, char value, int amount);
#endif