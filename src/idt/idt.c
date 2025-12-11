#include "idt/idt.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
#include "io/io.h"
#include "status.h"

/*
 * Global IDT and IDTR
 */
struct idt_desc idt_descriptors[PEACHOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

/*
 * This table is usually defined in your assembly file that builds the
 * interrupt stubs (one stub per vector). Each stub eventually calls
 * interrupt_handler(int interrupt, struct interrupt_frame* frame).
 */
extern void* interrupt_pointer_table[PEACHOS_TOTAL_INTERRUPTS];

/*
 * C callbacks for each interrupt vector.
 */
static INTERRUPT_CALLBACK_FUNCTION interrupt_callbacks[PEACHOS_TOTAL_INTERRUPTS];

extern void idt_load(struct idtr_desc* ptr);

/* -------------------------------------------------------------------------- */
/*  Default handlers                                                          */
/* -------------------------------------------------------------------------- */

static void no_interrupt_handler(struct interrupt_frame* frame)
{
    (void)frame;
    /* Just send EOI; no extra logging to avoid spam. */
    outb(0x20, 0x20);
}

static void divide_by_zero_handler(struct interrupt_frame* frame)
{
    (void)frame;
    print("Divide by zero error\n");
    /* You may want to halt here in a debug build. */
}

/* -------------------------------------------------------------------------- */
/*  C-level interrupt dispatcher (called from assembly stubs)                 */
/* -------------------------------------------------------------------------- */

/*
 * Called by the common interrupt stub.
 * 'interrupt' is the vector number (0–PEACHOS_TOTAL_INTERRUPTS-1).
 */
void interrupt_handler(int interrupt, struct interrupt_frame* frame)
{
    if (interrupt < 0 || interrupt >= PEACHOS_TOTAL_INTERRUPTS)
    {
        outb(0x20, 0x20);
        return;
    }

    INTERRUPT_CALLBACK_FUNCTION cb = interrupt_callbacks[interrupt];
    if (cb)
    {
        cb(frame);
    }
    else
    {
        /* If nothing registered, at least send EOI. */
        outb(0x20, 0x20);
    }
}

/* -------------------------------------------------------------------------- */
/*  IDT descriptor setup                                                      */
/* -------------------------------------------------------------------------- */

static void idt_set(int interrupt_no, void* address)
{
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1  = (uint32_t)address & 0xFFFF;
    desc->selector  = KERNEL_CODE_SELECTOR;
    desc->zero      = 0;
    desc->type_attr = 0x8E;  // Present, DPL=0, 32-bit interrupt gate
    desc->offset_2  = (uint32_t)address >> 16;
}

void idt_init(void)
{
    set_color(7);  // Light gray - starting idt_init
    
    // Clear just what we need
    for (int i = 0; i < 48; i++)
    {
        idt_descriptors[i].offset_1 = 0;
        idt_descriptors[i].selector = 0;
        idt_descriptors[i].zero = 0;
        idt_descriptors[i].type_attr = 0;
        idt_descriptors[i].offset_2 = 0;
    }
    
    set_color(8);  // Dark gray - cleared descriptors
    
    // Set up timer (IRQ0 = interrupt 32)
    if (interrupt_pointer_table[32] != NULL)
    {
        idt_set(32, interrupt_pointer_table[32]);
    }
    
    // Set up keyboard (IRQ1 = interrupt 33)
    if (interrupt_pointer_table[33] != NULL)
    {
        idt_set(33, interrupt_pointer_table[33]);
    }
    
    set_color(9);  // Light blue - set descriptors
    
    // Set IDTR
    idtr_descriptor.limit = (48 * 8) - 1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;
    
    set_color(10);  // Light green - about to load IDT
    
    // Load IDT with inline assembly instead of calling function
    asm volatile("lidt %0" : : "m"(idtr_descriptor));
    
    set_color(11);  // Light cyan - IDT loaded!
    
    // Register handlers
    idt_register_interrupt_callback(32, no_interrupt_handler);
    idt_register_interrupt_callback(33, no_interrupt_handler);
}

/* -------------------------------------------------------------------------- */
/*  Public API                                                                */
/* -------------------------------------------------------------------------- */

int idt_register_interrupt_callback(int interrupt,
                                    INTERRUPT_CALLBACK_FUNCTION interrupt_callback)
{
    if (interrupt < 0 || interrupt >= PEACHOS_TOTAL_INTERRUPTS)
    {
        return -EINVARG;
    }

    interrupt_callbacks[interrupt] = interrupt_callback;
    return 0;
}


