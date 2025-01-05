#include "drivers/include/cpu.h"
#include "drivers/include/stdio.h"
#include "drivers/include/strings.h"

void runCommand(char* buffer) {
    if (strcmp(buffer,"exit") == 0) {
        halt;
    } else if (strcmp(buffer, "help") == 0) {
        puts("exit: exits the os\nhelp: displays this message\n");
    }
    
    return;
}


void kmain(void) {
    puts("-=-= TINYOS =-=-\n");
    char buffer[1024];  
    int writePtr = 0;
    char exit[1024] = {'e'};
    strcpy(exit,4,"exit");
    puts(exit);
    while (1) {
        puts("\n>");
        writePtr = 0;  
        for (int i = 0; i < 1024; i++) {
            buffer[i] = '\0';
        }

        while (writePtr < 1024 - 1) {
            char c = getc();
            if (c == 0) continue;

            if (c == '\b') {
                if (writePtr > 0) {
                    writePtr--;
                    buffer[writePtr] = '\0';  
                    puts("\b \b");  
                }
            } else if (c == '\n') {
                putc(c);
                buffer[writePtr] = '\0';
                break;
            } else {
                buffer[writePtr++] = c;
                putc(c);
            }
        }
        runCommand(buffer);

    }   
    
    halt;
}