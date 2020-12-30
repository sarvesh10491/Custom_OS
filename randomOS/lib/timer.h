#ifndef TIMER_H
#define TIMER_H

#include "../include/types.h"
#include "../include/port.h"
#include "../drivers/screen.h"
#include "string.h"
#include "../kernel/cpu/interrupt.h"

void init_timer(u32int frequency);

#endif