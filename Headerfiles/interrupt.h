#include "types.h"
#ifndef INTERRUPT_H
#define INTERRUPT_H

void interrupt_init(void);
void EINT0_ISR(void) __irq;
void EINT1_ISR(void) __irq;
void check_medicine(void);
void setup_menu(void);
void rtc_edit(void);
void med_edit(void);

//extern volatile int config_flag;
//extern volatile int stop_flag;
extern volatile int flag0;
extern volatile int flag1;
#endif
