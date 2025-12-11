#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_EVENT_QUEUE_SIZE 128

enum KEYBOARD_EVENT_TYPE
{
    KEYBOARD_EVENT_NONE = 0,
    KEYBOARD_EVENT_PRESS = 1,
    KEYBOARD_EVENT_RELEASE = 2,
    KEYBOARD_EVENT_CHARACTER = 3
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

typedef int (*KEYBOARD_INIT_FUNCTION)();

struct keyboard
{
    KEYBOARD_INIT_FUNCTION init;
    char name[20];
    
    uint8_t key_states[256 / 8];
    struct keyboard* next;
};

void keyboard_init();

void keyboard_push_event(const struct keyboard_event* event);

int keyboard_pop_event(struct keyboard_event* event);

int keyboard_insert(struct keyboard* keyboard);

#endif
