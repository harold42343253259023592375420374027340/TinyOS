#include "drivers/include/cpu.h"
#include "drivers/include/stdio.h"
#include "drivers/include/strings.h"
#include "drivers/include/filesys.h"

Filesystem fs;

void runCommand(char* buffer) {
    char cmds[10][32];
    splitstr(buffer, ' ', cmds);
    
    if (strcmp(cmds[0],"exit") == 0) {
        halt;
    } else if (strcmp(cmds[0], "help") == 0) {
        puts("exit: exits the os\nhelp: displays this message\nls: list files\ncheck: see if file exists\nclear: clear the screen\ntouch: create a file\n./[filename]: read file");
    } else if (strcmp(cmds[0], "ls") == 0 ) {
        list_files(&fs);
    } else if (strcmp(cmds[0], "check") == 0) {
        if (findFile(&fs,cmds[1]) == 0) {
            puts("file exists\n");
        } else {
            puts("file: '");
            puts(cmds[1]);
            puts("' does not exist\n");
        }
    } else if (strcmp(cmds[0], "clear") == 0) {
        clearScrn();
    } else if (strcmp(cmds[0], "touch") == 0) {
        if (findFile(&fs, cmds[1]) != 0) {
            create_file(&fs, cmds[1], 0);
        } else {
            puts("file: '");
            puts(cmds[1]);
            puts("' already exists\n");
        }
    } else if (cmds[0][0] == '.' && cmds[0][1] == '/') {
        char *filename = &cmds[0][2];
        if (findFile(&fs, filename) == 0) {
            puts(filename);
        }
    } else {
        puts("unknown command: ");
        puts(cmds[0]);
        putc('\n');
    }
    
    return;
}


void kmain(void) {
    char buffer[1024];  
    int writePtr = 0;
    puts("[+] file system initializing...\n");
    init_filesystem(&fs);
    puts("[+] file system initialized!\n");

    
    
    puts("-=-= TINYOS =-=-\n");
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