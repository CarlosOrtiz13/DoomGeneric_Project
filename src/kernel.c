// ============================================================================
// FILE: src/kernel.c
// ============================================================================
#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
//#include "memory/memory.h"
#include "keyboard/keyboard.h"
#include "string/string.h"
#include "disk/disk.h"
#include "gdt/gdt.h"
#include "config.h"
#include "timer/timer.h"
#include "graphics/vga_palette.h"

// VBE Mode Info Structure
typedef struct {
    uint16_t attributes;
    uint8_t window_a;
    uint8_t window_b;
    uint16_t granularity;
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;
    uint16_t pitch;
    uint16_t width;
    uint16_t height;
    uint8_t w_char;
    uint8_t y_char;
    uint8_t planes;
    uint8_t bpp;
    uint8_t banks;
    uint8_t memory_model;
    uint8_t bank_size;
    uint8_t image_pages;
    uint8_t reserved0;
    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;
    uint32_t framebuffer;
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;
    uint8_t reserved1[206];
} __attribute__((packed)) vbe_mode_info_t;

// Text-mode VGA terminal
uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < (int)len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while (1) { }
}

// Simplified GDT (no TSS, no user segments)
struct gdt gdt_real[PEACHOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[PEACHOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00,       .type = 0x00},  // NULL
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},  // Kernel code
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},  // Kernel data
    {.base = 0x00, .limit = 0x00,       .type = 0x00},  // Unused
    {.base = 0x00, .limit = 0x00,       .type = 0x00},  // Unused
    {.base = 0x00, .limit = 0x00,       .type = 0x00}   // Unused
};

// Forward declaration for DoomGeneric
extern void doomgeneric_Create(int argc, char** argv);

void set_color(uint8_t color)
{
    uint8_t* fb = (uint8_t*)0xA0000;
    for(int i=0; i<64000; i++)
    {
        fb[i] = color;
    }
    for(volatile int i=0; i<100000000; i++);
}

#include "graphics/vga_palette.h"

void kernel_main()
{
    set_color(2);
    kheap_init();
    
    set_color(5);
    idt_init();
    
    set_color(6);
    timer_init();
    
    set_color(11);  // About to enable interrupts
    for(volatile int i=0; i<100000000; i++);
    
    asm volatile("sti");
    
    set_color(0);  // Interrupts enabled
    
    // Tight loop - if we survive 1 second, timer works
    for(volatile long long i=0; i<1000000000LL; i++);
    
    set_color(10);  // Light green - SUCCESS!
    while(1) {}
}