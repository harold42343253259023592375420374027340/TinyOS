#include "vga.h"
void kmain(void);
void kmain(void){
    // Reset();
    // newLine();
    if (testVGAMemory()) {
        print("VGA memory test passed!\n");
    } else {
        print("VGA memory test failed!\n");
    }
    print("Hello, World!\n");
}