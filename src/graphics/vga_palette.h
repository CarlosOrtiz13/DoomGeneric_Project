#ifndef VGA_PALETTE_H
#define VGA_PALETTE_H

#include <stdint.h>

void vga_set_palette_entry(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void vga_set_doom_palette(const uint8_t* palette);
void vga_set_default_palette(void);

#endif