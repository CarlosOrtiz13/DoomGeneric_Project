#include "classic.h"
#include "keyboard.h"
#include "io/io.h"
#include "kernel.h"
#include "idt/idt.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CLASSIC_KEYBOARD_CAPSLOCK_SCANCODE 0x3A


static const uint8_t scancode_to_dvk_map[] = {
    
    0x00, DVK_ESCAPE, DVK_1, '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x08,
    0x00, DVK_Q, DVK_W, DVK_E, 'R', DVK_T, 'Y', 'U', 'I', 'O', 'P', '[', ']', DVK_ENTER,
    DVK_LCTRL, DVK_A, DVK_S, DVK_D, DVK_F, 'G', 'H', 'J', 'K', 'L', ';', '\'', 
    '`', DVK_LSHIFT, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',
    0x00, '*', 0x00, DVK_SPACE, CLASSIC_KEYBOARD_CAPSLOCK_SCANCODE
    
};

static const uint8_t scancode_to_char_map[] = {
    0x00, 0x1B, '1', '2', '3', '4', '5',
    '6', '7', '8', '9', '0', '-', '=',
    0x08, '\t', 'Q', 'W', 'E', 'R', 'T',
    'Y', 'U', 'I', 'O', 'P', '[', ']',
    0x0d, 0x00, 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', 
    0x00, '\\', 'Z', 'X', 'C', 'V', 'B',
    'N', 'M', ',', '.', '/', 0x00, '*',
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, '7', '8', '9', '-', '4', '5',
    '6', '+', '1', '2', '3', '0', '.'
};

struct keyboard classic_keyboard = {
    .name = {"Classic"},
    .init = classic_keyboard_init
};

// Driver state
static bool is_extended_key = false;
static bool is_caps_lock_on = false;

uint8_t classic_keyboard_scancode_to_dvk(uint8_t scancode);
char classic_keyboard_scancode_to_char(uint8_t scancode);

uint8_t classic_keyboard_scancode_to_dvk(uint8_t scancode)
{
    if (scancode < sizeof(scancode_to_dvk_map) / sizeof(uint8_t))
    {
        return scancode_to_dvk_map[scancode];
    }
    return 0; 
}


char classic_keyboard_scancode_to_char(uint8_t scancode)
{
    size_t size = sizeof(scancode_to_char_map) / sizeof(uint8_t);
    if (scancode >= size)
    {
        return 0;
    }

    char c = scancode_to_char_map[scancode];
    
    if (is_caps_lock_on)
    {
        if (c >= 'a' && c <= 'z')
        {
            c -= 32; 
        }
    }
    else
    {
        if (c >= 'A' && c <= 'Z')
        {
            c += 32; 
        }
    }

    return c;
}


void classic_keyboard_handle_interrupt()
{
    uint8_t scancode = insb(KEYBOARD_INPUT_PORT);

    if (scancode == CLASSIC_KEYBOARD_EXTENDED)
    {
        is_extended_key = true;
        goto cleanup;
    }

    bool is_released = (scancode & CLASSIC_KEYBOARD_KEY_RELEASED) ? true : false;
    uint8_t raw_scancode = scancode & ~CLASSIC_KEYBOARD_KEY_RELEASED;

    if (raw_scancode == CLASSIC_KEYBOARD_CAPSLOCK_SCANCODE && !is_released)
    {
        is_caps_lock_on = !is_caps_lock_on;
        goto cleanup;
    }

    struct keyboard_event event = {0};
    event.type = is_released ? KEYBOARD_EVENT_RELEASE : KEYBOARD_EVENT_PRESS;
    
    if (is_extended_key)
    {
        switch (raw_scancode)
        {
            case 0x48: event.key_code = DVK_UPARROW;    break;
            case 0x50: event.key_code = DVK_DOWNARROW;  break;
            case 0x4B: event.key_code = DVK_LEFTARROW;  break;
            case 0x4D: event.key_code = DVK_RIGHTARROW; break;
            default: break;
        }
    }
    else
    {
        event.key_code = classic_keyboard_scancode_to_dvk(raw_scancode);
    }
    
    char c = classic_keyboard_scancode_to_char(raw_scancode);
    
    if (event.key_code != 0 || c != 0)
    {
        if (c != 0)
        {
            struct keyboard_event char_event = {
                .type      = KEYBOARD_EVENT_CHARACTER,
                .key_code  = event.key_code,
                .character = c
            };
            keyboard_push_event(&char_event);
        }
        
        keyboard_push_event(&event);
    }

cleanup:
    is_extended_key = false;

    /* Send EOI to PIC */
    outb(0x20, 0x20);
}


struct keyboard* classic_init()
{
    return &classic_keyboard;
}


int classic_keyboard_init()
{
    idt_register_interrupt_callback(ISR_KEYBOARD_INTERRUPT, classic_keyboard_handle_interrupt);

    outb(PS2_PORT, PS2_COMMAND_ENABLE_FIRST_PORT);
    
    return 0;
}
