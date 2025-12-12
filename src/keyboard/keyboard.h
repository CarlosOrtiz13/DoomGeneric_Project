#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_EVENT_QUEUE_SIZE 128

enum KEYBOARD_EVENT_TYPE
{
    KEYBOARD_EVENT_NONE = 0,
    KEYBOARD_EVENT_PRESS = 1,      /*Key down*/
    KEYBOARD_EVENT_RELEASE = 2,    /*Key up*/
    KEYBOARD_EVENT_CHARACTER = 3    /*Text input*/
};

struct keyboard_event
{
    enum KEYBOARD_EVENT_TYPE type;
    uint8_t key_code;
    char character;
};

//struct process;
//struct task;
//struct keyboard;

typedef int (*KEYBOARD_INIT_FUNCTION)();    /*Driver init hook*/

struct keyboard
{
    KEYBOARD_INIT_FUNCTION init;
    char name[20];
    
    uint8_t key_states[256 / 8];
    struct keyboard* next;
};

void keyboard_init();    /*Initialize keyboard subsystem + event queue*/

void keyboard_push_event(const struct keyboard_event* event);    /*Queue event*/

int keyboard_pop_event(struct keyboard_event* event);    /*Dequeue next event*/

int keyboard_insert(struct keyboard* keyboard);    /*Register keyboard driver*/

#endif
