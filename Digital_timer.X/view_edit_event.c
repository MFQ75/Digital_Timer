#include "main.h"
#include "ext_eeprom.h"

char event = -1;
extern char h,min,m;
static char d_h,d_min,d_sec;

void store()
{
    char log[12];
    log[0] = h/10 + '0';
    log[1] = h%10 + '0';
    log[2] = min/10 + '0';
    log[3] = min%10 + '0';
    if(m == 1)
    {
       log[4] = 'P';
       log[5] = 'M';
    }
    else
    {
        log[4] = 'A';
        log[5] = 'M';
    }
    log[6] = d_h/10 + '0';
    log[7] = d_h%10 + '0';
    log[8] = d_min/10 + '0';
    log[9] = d_min%10 + '0';
    log[10] = d_sec/10 + '0';
    log[11] = d_sec%10 + '0';
    if(++event == 5)
        event = 0;   
    for(char i=0 ; i < 12; i++)
    {
        write_external_eeprom(event*12+i,log[i]);
    }
}
unsigned char set_ev(unsigned char key)
{
    char num,*mode[] = {"AM","PM"};
    static unsigned int long_press,t;
    static char j = 0;
    if(key == 2)
    {
        t=0;
        long_press = 0;
        while(read_key(LEVEL) == 2)
        {
            if(++long_press == 50000)
            return DASHBOARD;
        }
        if(j!= 6)
        j++;
        else
            j=0;
    }
    else if(key == 1)
    {
        long_press = 0;
        while(read_key(LEVEL) == 1)
        {
            if(++long_press == 50000)
            {
                store();
                return DASHBOARD;
            }
        }
        if(j == 0)
        {
            if(++m == 2)
                m=0;
        }
        else if(j == 1)
        {
            if(++min == 60)
                min = 0;
        }
        else if(j == 2)
        {
            if(++h == 12)
                h = 0;
        }
        else if(j == 3)
        {
            if(++d_h == 12)
                d_h = 0;
        }
        else if(j == 4)
        {
            if(++d_min == 60)
                d_min = 0;
        }
        else if(j == 5)
        {
            if(++d_sec == 60)
                d_sec = 0;
        }
    }
    if(j == 0)
    {
        if(++t < 150)
        {
            clcd_print("  ",LINE1(12));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print(mode[m],LINE1(12));
        }
        
    }
    else
    {
        clcd_print(mode[m],LINE1(12));
    }
    if(j == 1)
    {
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE1(9));
            clcd_print_ch(' ',LINE1(10));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(min/10 + '0',LINE1(9));
            clcd_print_ch(min%10 + '0',LINE1(10));
        }
    }
    else
    {
        clcd_print_ch(min/10 + '0',LINE1(9));
        clcd_print_ch(min%10 + '0',LINE1(10));
    }
    if(j == 2)
    {
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE1(6));
            clcd_print_ch(' ',LINE1(7));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(h/10 + '0',LINE1(6));
            clcd_print_ch(h%10 + '0',LINE1(7));
        }
    }  
    else
    {
        clcd_print_ch(h/10 + '0',LINE1(6));
        clcd_print_ch(h%10 + '0',LINE1(7));
    }
    if(j == 3)
    {
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(6));
            clcd_print_ch(' ',LINE2(7));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(d_h/10 + '0',LINE2(6));
            clcd_print_ch(d_h%10 + '0',LINE2(7));
        }       
    }
    else if(j==4)
    {
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(9));
            clcd_print_ch(' ',LINE2(10));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(d_min/10 + '0',LINE2(9));
            clcd_print_ch(d_min%10 + '0',LINE2(10));
        }
    }
    else if(j == 5)
    {
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(12));
            clcd_print_ch(' ',LINE2(13));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(d_sec/10 + '0',LINE2(12));
            clcd_print_ch(d_sec%10 + '0',LINE2(13));
        }
    }
    
    if(j != 5)
    {
        clcd_print_ch(d_sec/10 + '0',LINE2(12));
        clcd_print_ch(d_sec%10 + '0',LINE2(13));
    }
    if(j != 4)
    {
        clcd_print_ch(d_min/10 + '0',LINE2(9));
        clcd_print_ch(d_min%10 + '0',LINE2(10));
    }
    clcd_print_ch(':',LINE2(11));
    if(j != 3)
    {
        clcd_print_ch(d_h/10 + '0',LINE2(6));
        clcd_print_ch(d_h%10 + '0',LINE2(7));
    }
    clcd_print_ch(':',LINE2(8));
    clcd_print_ch(':',LINE1(8));
    clcd_print_ch(' ',LINE1(11));
    return SET_EVENT;
}

void view_event(unsigned char key)
{
    static char i; 
    if(event == 0)
    {
        clcd_print("No event",LINE1(4));
    }
    else
    {
        if(key == 1 && i != 0)
            i--;
        else if(key == 2 && event >= i)
            i++;
        char log[12];
        for(char j=0; j<12; j++)
        {
            log[j] = read_external_eeprom(i*12+j);
        }
        clcd_print("TIME-",LINE1(0));
        clcd_print_ch(log[0],LINE1(6));
        clcd_print_ch(log[1],LINE1(7));
        clcd_print_ch(':',LINE1(8));
        clcd_print_ch(log[2],LINE1(9));
        clcd_print_ch(log[3],LINE1(10));
        clcd_print_ch(' ',LINE1(11));
        clcd_print_ch(log[4],LINE1(12));
        clcd_print_ch(log[5],LINE1(13));
        clcd_print("DUR -",LINE2(0));
        clcd_print_ch(log[6],LINE2(6));
        clcd_print_ch(log[7],LINE2(7));
        clcd_print_ch(':',LINE2(8));
        clcd_print_ch(log[8],LINE2(9));
        clcd_print_ch(log[9],LINE2(10));
        clcd_print_ch(':',LINE2(11));
        clcd_print_ch(log[10],LINE2(12));
        clcd_print_ch(log[11],LINE2(13));
    }
}