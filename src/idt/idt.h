#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* Forward declaration so we can use it in typedefs */
struct interrupt_frame;

/* 
 * C callback type for hardware/exception handlers.
 * This matches what the common interrupt handler will call.
 */
typedef void (*INTERRUPT_CALLBACK_FUNCTION)(struct interrupt_frame* frame);

/* IDT entry descriptor */
struct idt_desc
{
    uint16_t offset_1;   // bits 0-15 of handler function address
    uint16_t selector;   // code segment selector in GDT
    uint8_t  zero;       // always 0
    uint8_t  type_attr;  // type and attributes
    uint16_t offset_2;   // bits 16-31 of handler function address
} __attribute__((packed));

/* IDTR register layout */
struct idtr_desc
{
    uint16_t limit;      // size of IDT - 1
    uint32_t base;       // linear address of IDT
} __attribute__((packed));

/* 
 * CPU-saved state when an interrupt/exception occurs.
 * This matches the layout used in your assembly stubs.
 */
struct interrupt_frame
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t reserved;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));

/* IDT setup */
void idt_init(void);

/* Simple wrappers for cli/sti */
void enable_interrupts(void);
void disable_interrupts(void);

/* Register a C callback for a given interrupt vector (0–PEACHOS_TOTAL_INTERRUPTS-1) */
int idt_register_interrupt_callback(int interrupt,
                                    INTERRUPT_CALLBACK_FUNCTION interrupt_callback);

#endif