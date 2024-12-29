#include "include/io.h" 
#include "../stdint.h"
#define halt outw(0x604, 0x2000)


int x = 0, y = 0;
int color = 0x0F00;

void update_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
void scrollUp() {
    uint16_t *vga = (uint16_t *)VGA_ADDRESS;

    // Shift the screen up by one line
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga[(y - 1) * VGA_WIDTH + x] = vga[y * VGA_WIDTH + x];
        }
    }

    // Clear the last line
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = 0x0F00; // Clear to white text on black background
    }

    // Decrease the cursor y position
    y--;
    if (y < 0) {
        y = 0; // Prevent y from going negative
    }
}
void putchar(char c) {
    uint16_t *vga = (uint16_t *)VGA_ADDRESS;
    if (c == '\e') {
        return;
    }
    if (c == '\n') {
        x = 0;
        y++;
        if (y >= VGA_HEIGHT) {
            scrollUp();
        }
        update_cursor(x, y);
        return;
    }

    if (c != '\0') {
        vga[y * VGA_WIDTH + x] = (c | color); // White text on black background
        x++;
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
            if (y >= VGA_HEIGHT) {
                scrollUp();
            }
        }
        update_cursor(x, y);
    }
}
void charputs(char c) {
    uint16_t *vga = (uint16_t *)VGA_ADDRESS;

    if (c != '\0') {
        vga[y * VGA_WIDTH + x] = (c | 0x0F00);
        x++;
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
            if (y >= VGA_HEIGHT) {
                y = 0; // Handle scrolling here
            }
        }
        update_cursor(x, y);
    }
}
void puts(const char* message) {
    int i = 0;
    while (message[i] != 0) {
        putchar(message[i]);
        i++;
    }
}
void mvCursor(int nx, int ny) {
    x = nx;
    y = ny;
    return;
} 
void clearScrn() {
    uint16_t *vga = (uint16_t *)VGA_ADDRESS;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = 0x0F00; // Clear screen to white text on black background
    }
}
char scanCodes[128] = {
    '\0', '\1', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\3', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\6',
    '\4', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\e',
    ' ', 'z', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', ' ', 
    '\t', '\n', ' ', '\t', '\n'
};
char translateScanCode(uint8_t scanCode) {
    return scanCodes[scanCode];
}
char readKey(void) {
    while ((inb(KEYBOARD_STATUS_PORT) & 0x01) == 0);
    return translateScanCode(inb(KEYBOARD_DATA_PORT));
}


void testChar() {
    for (int i = 0; i <= 128; i++) {
        charputs(i);
    }
    return;
}