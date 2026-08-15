#include <lpc21xx.h>


//include LCD header files

#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "types.h"


// System clock and peripheral clock Macros

#define FOSC 12000000

#define CCLK (5*FOSC)    

#define PCLK (CCLK/4)


// RTC Prescaler Calculation Macros

// RTC requires 32.768 kHz clock for 1-second increment.

// PREINT and PREFRAC registers divide PCLK to generate 32.768 kHz.


// PREINT = int (PCLK / 32768) - 1;

// PREFRAC = PCLK -((PREINT + 1) * 32768);

// Note: This information collected from LPC2129 Manual


#define PREINT_VAL (int) ((PCLK / 32768) - 1)

#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768))


//RTC Control Register (CCR) Bit Definitions

// Bit 0 ? Clock Enable --> 1 = Enable RTC counters  0 = Disable RTC counters

#define RTC_ENABLE (1<<0)


// Bit 1 ? Clock Reset --> 1 = Reset RTC counters    0 = Normal operation

#define RTC_RESET (1<<1)

 


//only for LPC2148

// Bit 4 ? Clock Source Select 

// 1 = Use external 32.768 kHz oscillator

// 0 = Use internal PCLK as RTC clock source

#define RTC_CLKSRC (1<<4)




#define SUN 0

#define MON 1

#define TUE 2

#define WED 3

#define THU 4

#define FRI 5

#define SAT 6

//s32 hour,min,sec,date,month,year,day;


// Array to hold names of days of the week

char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

void RTC_Init(void) 
{
// Disable and reset the RTC
    CCR=RTC_RESET;
//  #ifndef _LPC2148

	PREINT = PREINT_VAL;

	PREFRAC = PREFRAC_VAL;

  
	
// Enable the RTC
    CCR = RTC_ENABLE;  // Enable the RTC with external clock source
//  #else
//CCR = RTC_ENABLE | RTC_CLKSRC;	
//#endif
}



void GetRTCTimeInfo(u32 *hour, u32 *minute, u32 *second)

{

	*hour = HOUR;

	*minute = MIN;

	*second = SEC;

}



void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

	CmdLCD(GOTO_LINE1_POS0);

	CharLCD(hour/10+48);

	CharLCD(hour%10+48);

	CharLCD(':');

	CharLCD(minute/10+48);

	CharLCD(minute%10+48);

	CharLCD(':');

	CharLCD(second/10+48);		

	CharLCD(second%10+48);	

}



void GetRTCDateInfo(u32 *date, u32 *month, u32 *year)

{

	*date = DOM;

	*month = MONTH;

	*year = YEAR;

}




void DisplayRTCDate(u32 date, u32 month, u32 year)

{

	CmdLCD(GOTO_LINE2_POS0);

	CharLCD(date/10+48);

	CharLCD(date%10+48);

	CharLCD('/');

	CharLCD(month/10+48);

	CharLCD(month%10+48);

	CharLCD('/');

	U32LCD(year);

}




void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;

}


void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

	DOM = date;

	MONTH = month;

	YEAR = year;

}



void GetRTCDay(s32 *dow)

{

	*dow = DOW; 

}




void DisplayRTCDay(s32 dow)

{

	CmdLCD(GOTO_LINE1_POS0+10);

	StrLCD(week[dow]);

  

}

void SetRTCDay(s32 dow)

{

	DOW = dow;

}
