#include "timer.h"
#include "io/io.h"
#include "idt/idt.h"
#include "kernel.h"

volatile uint64_t timer_ticks = 0;

void timer_handle_interrupt()
{
    // Do absolutely NOTHING except EOI
    asm volatile("mov $0x20, %al; outb %al, $0x20");
}

void timer_init()
{
    // Register the handler for ISR 0x20 (PIT)
    idt_register_interrupt_callback(ISR_TIMER_INTERRUPT, timer_handle_interrupt);
    
    // Program PIT for mode 2 (rate generator), binary, channel 0
    // Use inline assembly instead of outb function
    asm volatile("outb %0, %1" : : "a"((uint8_t)0x34), "Nd"((uint16_t)PIT_COMMAND_PORT));
    
    uint16_t divisor = PIT_DIVISOR;
    asm volatile("outb %0, %1" : : "a"((uint8_t)(divisor & 0xFF)), "Nd"((uint16_t)PIT_CHANNEL0_DATA_PORT));
    asm volatile("outb %0, %1" : : "a"((uint8_t)((divisor >> 8) & 0xFF)), "Nd"((uint16_t)PIT_CHANNEL0_DATA_PORT));
}

