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