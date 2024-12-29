#include "drivers/include/io.h"
#include "drivers/include/cpu.h"

void kmain(void);
void kmain(void){
    puts("Hello, World!");
    char key;
    while (1) {
        key = readKey();
        putchar(key);
    }
    
}