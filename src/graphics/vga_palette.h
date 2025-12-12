#ifndef VGA_PALETTE_H
#define VGA_PALETTE_H

#include <stdint.h>

void vga_set_palette_entry(uint8_t index, uint8_t r, uint8_t g, uint8_t b);    /*Set a single VGA palette entry*/
void vga_set_doom_palette(const uint8_t* palette);    /*Load Doom’s color palette*/ 
void vga_set_default_palette(void);    /*Restore standard VGA color palette*/

#endif
