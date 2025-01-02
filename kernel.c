#include "drivers/include/cpu.h"
#include "drivers/include/stdio.h"
#include "drivers/include/strings.h"




void cmd(char *buffer) {
    buffer[1023] = '\0';
    puts(buffer);
    if (strcmp(buffer, 4, "exit") == 0) { 
        halt; 
    }
}

void kmain(void) {
    puts("-=-= TINYOS =-=-\n");
    char buffer[1024] = {0};  
    int writePtr = 0;

    while (1) {
        puts("\n>");
        writePtr = 0;  
        for (int i = 0; i < 1024; i++) {
            buffer[i] = 0;
        }

        while (writePtr < sizeof(buffer) - 1) {  
            char c = getc();
            
            switch(c) {
                case '\b':  
                    if (writePtr > 0) {
                        writePtr--;
                        buffer[writePtr] = 0;
                        putc('\b');
                    }
                    break;
                
                case '\n':  
                    buffer[writePtr] = '\0';  
                    goto checkCommand;
                    break;                
                default:
                    buffer[writePtr++] = c;
                    putc(c);
                    break;
            }
        }
        checkCommand:
            cmd(buffer);

    }   
    
    halt;
}