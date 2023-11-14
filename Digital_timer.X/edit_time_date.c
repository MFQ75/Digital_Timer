#include "main.h"

extern char h,min,sec,d,month,year,m;

unsigned char set_time(unsigned char key)
{
    char num;
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
        if(j!= 2)
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
                num = ((sec/10)<<4) | (sec%10);
                write_ds1307(SEC_ADDR,num);
                num = ((min/10)<<4) | (min%10);
                write_ds1307(MIN_ADDR,num);
                num = ((h/10)<<4) | (h%10);
                write_ds1307(HOUR_ADDR,num);
                return DASHBOARD;
            }
        }
    }
    if(j == 0)
    {
        if(key == 1)
        if(++sec == 60)
        sec = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(10));
            clcd_print_ch(' ',LINE2(11));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(sec/10 + '0',LINE2(10));
            clcd_print_ch(sec%10 + '0',LINE2(11 ));
        }
        
    }
    else if(j == 1)
    {
        if(key == 1)
        if(++min == 60)
           min = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(7));
            clcd_print_ch(' ',LINE2(8));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(min/10 + '0',LINE2(7));
            clcd_print_ch(min%10 + '0',LINE2(8));
        }
    }
    else if(j == 2)
    {
        if(key == 1)
        if(++h == 12)
           h = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(4));
            clcd_print_ch(' ',LINE2(5));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(h/10 + '0',LINE2(4));
            clcd_print_ch(h%10 + '0',LINE2(5));
        }
    }    
    
    if(j != 2)
    {
        clcd_print_ch(h/10 + '0',LINE2(4));
        clcd_print_ch(h%10 + '0',LINE2(5));
    }
    clcd_print_ch(':',LINE2(6));
    if(j != 1)
    {
        clcd_print_ch(min/10 + '0',LINE2(7));
        clcd_print_ch(min%10 + '0',LINE2(8));
    }
    clcd_print_ch(':',LINE2(9));
    if(j != 0)
    {
        clcd_print_ch(sec/10 + '0',LINE2(10));
        clcd_print_ch(sec%10 + '0',LINE2(11));
    }
    return EDIT_TIME;
}

unsigned char set_date(unsigned char key)
{
    char num;
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
        if(j!= 2)
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
                num = ((year/10)<<4) | (year%10);
                write_ds1307(YEAR_ADDR,num);
                num = ((month/10)<<4) | (month%10);
                write_ds1307(MONTH_ADDR,num);
                num = ((d/10)<<4) | (d%10);
                write_ds1307(DATE_ADDR,num);
                return DASHBOARD;
            }
        }
    }
    if(j == 0)
    {
        if(key == 1)
        if(++year == 100)
            year = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(10));
            clcd_print_ch(' ',LINE2(11));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(year/10 + '0',LINE2(10));
            clcd_print_ch(year%10 + '0',LINE2(11 ));
        }      
    }
    else if(j == 1)
    {
        if(key == 1)
        if(++month == 13)
            month = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(7));
            clcd_print_ch(' ',LINE2(8));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(month/10 + '0',LINE2(7));
            clcd_print_ch(month%10 + '0',LINE2(8));
        }
    }
    else if(j == 2)
    {
        if(key == 1)
        if(++d == 30)
           d = 0;
        if(++t < 150)
        {
            clcd_print_ch(' ',LINE2(4));
            clcd_print_ch(' ',LINE2(5));
        }
        else if(t == 300)
            t = 0;
        else
        {
            clcd_print_ch(d/10 + '0',LINE2(4));
            clcd_print_ch(d%10 + '0',LINE2(5));
        }
    }
    if(j != 2)
    {
        clcd_print_ch(d/10 + '0',LINE2(4));
        clcd_print_ch(d%10 + '0',LINE2(5));
    }
    clcd_print_ch('-',LINE2(6));
    if(j != 1)
    {
        clcd_print_ch(month/10 + '0',LINE2(7));
        clcd_print_ch(month%10 + '0',LINE2(8));
    }
    clcd_print_ch('-',LINE2(9));
    if(j != 0)
    {
        clcd_print_ch(year/10 + '0',LINE2(10));
        clcd_print_ch(year%10 + '0',LINE2(11));
    }    
    return EDIT_DATE;
}