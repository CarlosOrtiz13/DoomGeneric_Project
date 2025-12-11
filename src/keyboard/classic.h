#ifndef CLASSIC_KEYBOARD_H
#define CLASSIC_KEYBOARD_H

#include "keyboard.h"
#include <stdint.h>

#define PS2_PORT 0x64
#define PS2_COMMAND_ENABLE_FIRST_PORT 0xAE
#define KEYBOARD_INPUT_PORT 0x60

#define ISR_KEYBOARD_INTERRUPT 0x21

#define CLASSIC_KEYBOARD_KEY_RELEASED 0x80
#define CLASSIC_KEYBOARD_EXTENDED 0xE0

struct keyboard* classic_init();
int classic_keyboard_init(void);


#define DVK_ESCAPE      0x01
#define DVK_1           0x02
#define DVK_Q           0x10
#define DVK_W           0x11
#define DVK_E           0x12
#define DVK_T           0x14
#define DVK_A           0x1E
#define DVK_S           0x1F
#define DVK_D           0x20
#define DVK_F           0x21
#define DVK_LSHIFT      0x2A
#define DVK_LCTRL       0x1D
#define DVK_SPACE       0x39
#define DVK_UPARROW     0x48
#define DVK_DOWNARROW   0x50
#define DVK_LEFTARROW   0x4B
#define DVK_RIGHTARROW  0x4D
#define DVK_ENTER       0x1C

#endif
