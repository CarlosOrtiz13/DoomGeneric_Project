#include "keyboard.h"
#include "status.h"
#include "kernel.h"
#include "classic.h"

static struct keyboard* keyboard_list_head = 0;
static struct keyboard* keyboard_list_last = 0;

/* Global keyboard event queue (single-task kernel). */
static struct keyboard_event g_event_queue[KEYBOARD_EVENT_QUEUE_SIZE];
static int g_event_head = 0;  /* index of next event to pop  */
static int g_event_tail = 0;  /* index of next slot to write */

/* Helper: check if queue is full */
static int keyboard_queue_full(void)
{
    int next_tail = (g_event_tail + 1) % KEYBOARD_EVENT_QUEUE_SIZE;
    return (next_tail == g_event_head);
}

/* Helper: check if queue is empty */
static int keyboard_queue_empty(void)
{
    return (g_event_head == g_event_tail);
}

void keyboard_init(void)
{
    /* Insert the classic PS/2 keyboard driver */
    keyboard_insert(classic_init());
}

int keyboard_insert(struct keyboard* keyboard)
{
    if (!keyboard)
    {
        return -EIO;
    }

    if (!keyboard->init)
    {
        return -EIO;
    }

    /* Append to linked list */
    if (keyboard_list_last)
    {
        keyboard_list_last->next = keyboard;
        keyboard_list_last = keyboard;
    }
    else
    {
        keyboard_list_head = keyboard;
        keyboard_list_last = keyboard;
    }

    /* Call its init() */
    return keyboard->init();
}

/*
 * Push an event into the global keyboard queue.
 * Called from the keyboard interrupt handler in classic.c.
 */
void keyboard_push_event(const struct keyboard_event* event)
{
    if (!event)
    {
        return;
    }
    
    if (keyboard_queue_full())
    {
        /* Queue full: drop this event. For Doom this is fine (worst case: key lost). */
        return;
    }

    g_event_queue[g_event_tail] = *event;
    g_event_tail = (g_event_tail + 1) % KEYBOARD_EVENT_QUEUE_SIZE;
}

/*
 * Pop one event from the global keyboard queue.
 * Returns 0 on success, or -EIO if the queue is empty.
 */
int keyboard_pop_event(struct keyboard_event* event)
{
    if (!event)
        return -EIO;

    if (keyboard_queue_empty())
    {
        event->type = KEYBOARD_EVENT_NONE;
        event->key_code = 0;
        event->character = 0;
        return -EIO;
    }

    *event = g_event_queue[g_event_head];
    g_event_head = (g_event_head + 1) % KEYBOARD_EVENT_QUEUE_SIZE;

    return 0;
}
