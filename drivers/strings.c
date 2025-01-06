#include "include/strings.h"


int strcmp(char *str1, char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}



void strcpy(char *to, int len,char *from) {
    for (int i = 0; i < len | from[i] != '\0'; i++) {
        to[i] = from[i];
    }
    return;
}

int strlen(char *array) {
    int counter = 0;
    for (int i = 0; array[i] != '\0'; i++) {
        counter++;
    }
    return counter;
}
void splitstr(char *str, char token, char cmds[10][32]) {
    int word_count = 0;
    int char_count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == token) {
            if (char_count > 0) {
                cmds[word_count][char_count] = '\0';
                word_count++;
                char_count = 0;
            }
        } else {
            if (char_count < 31) {
                cmds[word_count][char_count] = str[i];
                char_count++;
            }
        }
        
        if (word_count >= 10) break;  
    }

    if (char_count > 0) {
        cmds[word_count][char_count] = '\0';
        word_count++;
    }

    for (int i = word_count; i < 10; i++) {
        cmds[i][0] = '\0';
    }
}


void memset(char* str, char value, int amount) {
    for (int i = 0; i < amount; i++) {
        str[i] = value;
    }
    return;
}