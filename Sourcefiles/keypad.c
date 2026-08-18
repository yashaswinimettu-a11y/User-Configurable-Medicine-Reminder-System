//kpm.c
#include "types.h"
#include "delay.h"
#include "defines.h"
#include <lpc21xx.h>
#include "kpm_defines.h"
#include "lcd.h"
u32 kpmLUT[4][4]={{'1','2','3','A'},
                                                                        {'4','5','6','B'},
                                                                        {'7','8','9','C'},
                                                                        {'*','0','#','D'}};
/*u8 kpmLUT[4][4]={{'7','8','9','/'},^M
                                                                        {'4','5','6','*'},^M
                                                                        {'1','2','3','-'},^M
                                                                        {'C','0','=','+'}};     */

void InitKPM(void)
{
        WNIBBLE(IODIR1,ROW0,15);
}
u32 ColScan(void)
{
        return((RNIBBLE(IOPIN1,COL0)<15)?0:1);
}
u32 RowCheck(void)
{
        u32 rno;
        for(rno=0; rno<4; rno++)
        {
                WNIBBLE(IOPIN1,ROW0,~(1<<rno));
                if(ColScan()==0)
                {
                        break;
                }
        }
        //make rows as default^M
        WNIBBLE(IOPIN1,ROW0,0x0);
        return rno;
}
u32 ColCheck(void)
{
        u32 cno;
        for(cno=0; cno<4; cno++)
        {
                if(RBIT(IOPIN1,(COL0+cno))==0)
                {
                        break;
                }
        }
        return cno;
}
u32 KeyScan(void)
{
        u32 rno,cno,keyv;
        //wait for switch press^M
        while(ColScan());
        //find the row_no^M
        rno=RowCheck();
        //find the col_no^M
        cno=ColCheck();
        //get the key value using kpmLUT^M
        keyv=kpmLUT[rno][cno];
        //wait for switch release^M
        while(!ColScan());
       delay_ms(200);
        return keyv;
}
u32 ReadNum(u8 max_digits)
{
    u8 key;
    u32 sum = 0,c=0;
    //u8 digit_count = 0;

    while(1)
    {
         key = KeyScan();

        if(key >= '0' && key <= '9')
        {
           //if(digit_count < max_digits)   // ? dynamic limit
            //{
                CharLCD(key);
                sum = (sum * 10) + (key - '0');
				c++;
//                digit_count++;
            //}
        }

        else if(key == '*')
        {
            break;
        }

        else if(key == '#' && c)   // Backspace
        {
            //if(digit_count > 0)
            //{
                sum = sum / 10;
               // digit_count--;
					c--;
                CmdLCD(0x10);   // move left
                CharLCD(' ');   // erase
                CmdLCD(0x10);   // move left again
            //}
        }
    }
    return sum;
}
