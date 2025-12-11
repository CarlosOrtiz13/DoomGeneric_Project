// VGA Palette functions for Mode 13h
#include <stdint.h>

// Inline assembly helper for outb
static inline void outb_inline(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Set a single VGA palette entry (for 256-color mode)
void vga_set_palette_entry(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
    outb_inline(0x3C8, index);      // Select palette index
    outb_inline(0x3C9, r >> 2);     // Red (6-bit, so divide by 4)
    outb_inline(0x3C9, g >> 2);     // Green (6-bit)
    outb_inline(0x3C9, b >> 2);     // Blue (6-bit)
}

// Load the Doom palette (from PLAYPAL lump)
void vga_set_doom_palette(const uint8_t* palette)
{
    for (int i = 0; i < 256; i++)
    {
        uint8_t r = palette[i * 3 + 0];
        uint8_t g = palette[i * 3 + 1];
        uint8_t b = palette[i * 3 + 2];
        vga_set_palette_entry(i, r, g, b);
    }
}

// Default VGA palette (similar to DOS default)
void vga_set_default_palette(void)
{
    // Set a basic grayscale palette so we can at least see something
    for (int i = 0; i < 256; i++)
    {
        uint8_t c = i;
        vga_set_palette_entry(i, c, c, c);
    }
}