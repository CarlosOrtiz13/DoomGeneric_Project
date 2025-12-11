#include "doomgeneric.h"
#include "doomkeys.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/classic.h"
#include "../timer/timer.h"
#include <stdint.h>

// Mode 13h is 320x200, 256 colors, framebuffer at 0xA0000
static uint8_t* framebuffer = (uint8_t*)0xA0000;
static const int screen_width = 320;
static const int screen_height = 200;

// Doom key mapping (same as before)
static unsigned char scancode_to_doom_key(uint8_t scancode)
{
    switch (scancode)
    {
        case DVK_ESCAPE:     return KEY_ESCAPE;
        case DVK_ENTER:      return KEY_ENTER;
        case DVK_SPACE:      return KEY_FIRE;
        case DVK_W:          return KEY_UPARROW;
        case DVK_S:          return KEY_DOWNARROW;
        case DVK_A:          return KEY_LEFTARROW;
        case DVK_D:          return KEY_RIGHTARROW;
        case DVK_UPARROW:    return KEY_UPARROW;
        case DVK_DOWNARROW:  return KEY_DOWNARROW;
        case DVK_LEFTARROW:  return KEY_LEFTARROW;
        case DVK_RIGHTARROW: return KEY_RIGHTARROW;
        case DVK_LCTRL:      return KEY_FIRE;
        case DVK_LSHIFT:     return KEY_RSHIFT;
        case DVK_Q:          return KEY_STRAFE_L;
        case DVK_E:          return KEY_STRAFE_R;
        case DVK_1:          return '1';
        case '2':            return '2';
        case '3':            return '3';
        case '4':            return '4';
        case '5':            return '5';
        case '6':            return '6';
        case '7':            return '7';
        case DVK_T:          return KEY_TAB;
        default:             return 0;
    }
}

void DG_Init()
{
    // Mode 13h is already set by bootloader
    // Framebuffer is at 0xA0000
}

void DG_DrawFrame()
{
    // Doom renders at DOOMGENERIC_RESX x DOOMGENERIC_RESY (should be 320x200)
    // DG_ScreenBuffer is the Doom screen buffer (indexed color)
    
    // Simply copy Doom's buffer to Mode 13h framebuffer
    for (int i = 0; i < screen_width * screen_height; i++)
    {
        framebuffer[i] = DG_ScreenBuffer[i];
    }
}

void DG_SleepMs(uint32_t ms)
{
    if (ms == 0) return;
    uint32_t ticks32 = (ms + 9) / 10;
    uint64_t target_tick = timer_ticks + (uint64_t)ticks32;
    while (timer_ticks < target_tick)
    {
        asm volatile("sti; hlt");
    }
}

uint32_t DG_GetTicksMs()
{
    return (uint32_t)(timer_ticks * 10);
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    // Stub - no keyboard input for now
    // Just return 0 (no key pressed)
    return 0;
}

void DG_SetWindowTitle(const char* title)
{
    (void)title;
}