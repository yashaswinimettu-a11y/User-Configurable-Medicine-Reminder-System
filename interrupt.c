#include <lpc21xx.h>
#include "interrupt.h"
#include "delay.h"
#include "keypad.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "buzzer.h"

#define SWITCH2 3
extern u32 b;
int n;
int med_hour=10,med_min=41;
u32 hour,min,sec;
u32 date,month,year;
s32 day;
#define EINT0_INPUT_PIN 0x0000000C
#define EINT0_VIC_CHNO  14

#define EINT0_STATUS_LED 16//@p1.16^M
//volatile int flag0=0;
//volatile int flag1=0;


#define EINT1_INPUT_PIN 0x000000C0
#define EINT1_VIC_CHNO  15

#define EINT1_STATUS_LED 17//@p1.17
void EINT0_ISR(void) __irq
{
	flag0=1;

EXTINT = 1<<0;
VICVectAddr = 0;
}
void EINT1_ISR(void) __irq
{
buzzer_off();
flag1=1;
//CmdLCD(0x01);
EXTINT = 1<<1;
VICVectAddr = 0;
}
void interrupt_init(void)
{

        PINSEL0&=((u32)~3<<2)|((u32)~3<<4);

        PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;
		EXTMODE=((1<<1)|(1<<0));
		EXTPOLAR=0X00;

        VICIntEnable=(1<<EINT0_VIC_CHNO)|(1<<EINT1_VIC_CHNO);

        VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;

        VICVectAddr0=(u32 ) EINT0_ISR;

        VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;

        VICVectAddr1=(u32 ) EINT1_ISR;

      
}
void setup_menu()
{
                                                 label: CmdLCD(0x01);
                                                 CmdLCD(GOTO_LINE1_POS0);
                                                 StrLCD("----Menu---");
                                                 CmdLCD(0XC0);
                                                 StrLCD("1RTC 2MED 3EXIT");
                                                 n=KeyScan();
	                                               //CmdLCD(0x01);
	                                               //delay_ms(200);
                                                 if(n=='1')
                                                 {
                                                        rtc_edit();
                                                 }
                                                 else if(n=='2')
                                                 {
                                                     med_edit();
                                                 }
                                                 else if(n=='3')
                                                 {
                                                     return;
                                                 }
                                                 else
                                                 {
                                                         CmdLCD(0x01);
                                                                 StrLCD("Invalid choice");
                                                                 delay_ms(1000);
                                                                 goto label; 
                                                 }
}
void rtc_edit(void)
{
                label: CmdLCD(0x01);
                                                 StrLCD("1.TIME 2.DATE");
                                                 CmdLCD(0xc0);
                                                 StrLCD("3.DAY 4.EXIT");
                                                 n=KeyScan();
	                                              // delay_ms(200);
                                                 if(n=='1')
                                                 {
                                                        Timelabel:CmdLCD(0x01);
                                                        StrLCD("1.HOUR 2.MIN");
                                                        CmdLCD(0xc0);
                                                        StrLCD("3.SEC 4.EXIT");

                                                        n=KeyScan();
																									      //delay_ms(200);
                                                        if(n=='1')
                                                        {
                                                            hour:CmdLCD(0x01);
                                                                StrLCD("Hour(0-23):");
                                                                n=ReadNum();
                                                                if(n>23)
                                                                {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto hour;
                                                                }
                                                                HOUR=n;
																goto Timelabel;
                                                    }
                                                        else if(n=='2')
                                                        {
                                                                min:CmdLCD(0x01);
                                                                StrLCD("Min(0-59):");
                                                                n=ReadNum();
                                                                if(n>59)
                                                                {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto min;
                                                                }
                                                                MIN=n;
																	goto Timelabel;
                                                    }
                                                        else if(n=='3')
                                                        {
                                                            sec:CmdLCD(0x01);
                                                                StrLCD("Sec(0-59):");
                                                                n=ReadNum();
                                                                if(n>59)
                                                                {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto sec;
                                                                }
                                                                SEC=n;
																	goto Timelabel;
                                                    }
                                                        else if(n=='4')
                                                        {
                                                           setup_menu();
                                                        }
                                                        else
                                                        {
                                                            CmdLCD(0x01);
                                                                StrLCD("Invalid choice");
                                                                goto Timelabel;
                                                        }
                                        }
                                                     else  if(n=='2')
                                                    {
                                                        Datelabel:CmdLCD(0x01);
                                                        StrLCD("1.Date 2.Mon");
                                                        CmdLCD(0xc0);
                                                        StrLCD("3.Year 4.EXIT");
																											  
                                                        n=KeyScan();
                                                        if(n=='1')
                                                        {
                                                            Date:CmdLCD(0x01);
                                                                StrLCD("Date(1-31):");
                                                                n=ReadNum();
                                                                if(n>31)
                                                                {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto Date;
                                                                }
                                                                DOM=n;
																goto Datelabel;
                                                    }
                                                        else if(n=='2')
                                                        {
                                                            mon:CmdLCD(0x01);
                                                                StrLCD("Mon(1-12):");
                                                                n=ReadNum();
                                                                if(n>12)
                                                                {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto mon;
                                                                }
                                                                MONTH=n;
																goto Datelabel;
                                                    }
                                                        else if(n=='3')
                                                        {
                                                            CmdLCD(0x01);
                                                                StrLCD("year(yyyy):");
                                                    n=ReadNum();
													YEAR=n;
													goto Datelabel;
                                                    }
                                                        else if(n=='4')
                                                        {
                                                           setup_menu();
                                                        }
                                                        else
                                                        {
                                                            CmdLCD(0x01);
                                                                StrLCD("Invalid choice");
																delay_ms(200);
                                                                goto Datelabel;
                                                        }
                                        }
                           else if(n=='3')
                                                    {
                                                        daylabel:CmdLCD(0x01);
                                                        StrLCD("Enter day(0-7)");
                             n=ReadNum();
                                                        if(n>7)
                                                        {
                                                            CmdLCD(0x01);
                                                                StrLCD("Invalid choice");
																delay_ms(200);
                                                                goto daylabel;
                                                        }
														DOW=n;
														goto label;
                                                        }
                                                        else
                                                        {
                                                            CmdLCD(0x01);
                                                                StrLCD("Invalid choice");
                                                                goto label;
                                                    }
													}
                                                       //CCR=(1<<1);
//											CmdLCD(0x01);   // ? CLEAR AGAIN
									//return;
                                

void med_edit()
{
        label2:CmdLCD(0x01);
        StrLCD("1.Med_hour");
        CmdLCD(0xc0);
        StrLCD("2.Med_Min 3.EXIT");
        n=KeyScan();
        if(n=='1')
        {
                 medhour:CmdLCD(0x01);
                 StrLCD("Hour(0-23):");
                 n=ReadNum();
                 if(n>23)
                 {
                           CmdLCD(0X01);
                           StrLCD("Invalid choice");
                           delay_ms(200);
                           goto medhour;
                 }
	             med_hour=n;
                 goto label2;				 
        }
        else if(n=='2')
        {
                 medmin:CmdLCD(0x01);
                 StrLCD("Min(0-59):");
                 n=ReadNum();
                 if(n>59)
                 {
                                                                CmdLCD(0X01);
                                                                StrLCD("Invalid choice");
                                                                delay_ms(200);
                                                                goto medmin;
                                                                }
																med_min=n;
																goto label2;
																			
                                                    }
                                                        else if(n=='3')
                                                        {
                                                              setup_menu();
                                                    }
                                                        else
                                                        {
                                                             CmdLCD(0X01);
                                                                 StrLCD("Invalid choice");
                                                             delay_ms(1000);
                                                                 goto label2;
                                                        }
                                                        
}
void check_medicine(void)
{
int i;
//int buzzer_time;
 	/*				if(b == 1)
					{
					    CmdLCD(GOTO_LINE1_POS0);
						StrLCD("Medicine Taken");
						delay_s(1);
						CmdLCD(CLEAR_LCD);
					}	   */

     if(med_hour==HOUR && med_min==MIN && SEC == 0)
         {
	
              buzzer_on();
                  CmdLCD(0X01);
                  StrLCD("Take Medicine");
		 for(i=0;i<60;i++)
		 {
		 if(flag1==1)
		 {
		  b = 1;
		 break;
		 }

	     delay_s(1);
		 }
		  buzzer_off();
		 flag1=0;
		 CmdLCD(CLEAR_LCD);
		 }
		 }  


