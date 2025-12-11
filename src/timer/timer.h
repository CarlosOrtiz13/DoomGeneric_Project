#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define PIT_COMMAND_PORT 0x43
#define PIT_CHANNEL0_DATA_PORT 0x40

#define ISR_TIMER_INTERRUPT 0x20

// 100 Hz → 1 tick every 10 ms
#define TARGET_FREQUENCY 100
#define PIT_DIVISOR (1193180 / TARGET_FREQUENCY)

extern volatile uint64_t timer_ticks;

void timer_init(void);

// DoomGeneric sleep implementation
void DG_SleepMs(uint32_t ms);

uint32_t DG_GetTicksMs(void);

#endif

