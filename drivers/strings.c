#include "include/strings.h"


int strcmp(char *str1, int len, char *str2) {
    for (int ptr = 0; ptr < len; ptr++) {
        if (str1[ptr] != str2[ptr]) {
            return 1;
        }
    }
    return 0;
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