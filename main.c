//main.c
#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "keypad.h"
#include "buzzer.h"
#include "interrupt.h"
#include "delay.h"

u32 h,m,s,b=0;
u32 dt,mon,yr;
s32 dy;
volatile int flag0;
volatile int flag1;
int main()

{
     InitLCD();
     RTC_Init(); 
     InitKPM();
     buzzer_init();
         interrupt_init();
     CmdLCD(GOTO_LINE1_POS0);
     StrLCD("MEDICINE");
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("ALARM");
         delay_ms(500);
         CmdLCD(CLEAR_LCD);
         SetRTCTimeInfo(12,30,0);
         SetRTCDateInfo(26,03,2026);
         SetRTCDay(1);
     while(1)
     {
            GetRTCTimeInfo(&h,&m,&s);
                DisplayRTCTime(h,m,s);
            GetRTCDateInfo(&dt,&mon,&yr);
                DisplayRTCDate(dt,mon,yr);
            GetRTCDay(&dy);
        DisplayRTCDay(dy);
                if(flag0)
                {
                     setup_menu();
                                                CmdLCD(0X01);
                         flag0=0;

                }
check_medicine();
		 }
	 }
