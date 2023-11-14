#include "main.h"

char time[9],date[9];
char i;
char h,min,sec,d,month,year,m;

void get_time()
{
    h = ((time[0] <<4) | (time[1]&0x0F));
    min = ((time[3]<<4) | time[4]);
    sec = ((((read_ds1307(SEC_ADDR) >> 4) & 0x07) + '0') | ((read_ds1307(SEC_ADDR) >> 4) & 0x0F + '0'));
    if(time[6] == 'A' && time[7] == 'M')
        m = 0;
    else
        m = 1;
    d = ((date[0]<<4) | date[1]);
    h = ((date[3]<<4) | date[4]);
    h = ((date[6]<<4) | date[7]);    
}
void read_rtc()
{
    time[0] = ((read_ds1307(HOUR_ADDR)>> 4) & 0x01) + '0';
    time[1] = (read_ds1307(HOUR_ADDR) & 0x0F) + '0';
    time[2] = ':';
    time[3] = ((read_ds1307(MIN_ADDR) >> 4) & 0x07) + '0';
    time[4] = (read_ds1307(MIN_ADDR) & 0x0F) + '0';
    time[5] = ' ';
    if((read_ds1307(HOUR_ADDR)) & 0x20)
    {
        time[6] = 'A';
        time[7] = 'M';
    }
    else
    {
        time[6] = 'P';
        time[7] = 'M';
    }
    time[8] = '\0'; 
    clcd_print("TIME ",LINE2(0));
    clcd_print(time, LINE2(5));
    date[0] = ((read_ds1307(DATE_ADDR)>> 4) & 0x03) + '0';
    date[1] = (read_ds1307(DATE_ADDR) & 0x0F) + '0';
    date[2] = '-';
    date[3] = ((read_ds1307(MONTH_ADDR) >> 4) & 0x01) + '0';
    date[4] = (read_ds1307(MONTH_ADDR) & 0x0F) + '0';
    date[5] = '-';
    date[6] = ((read_ds1307(YEAR_ADDR)>> 4)& 0x0F) + '0';
    date[7] = (read_ds1307(YEAR_ADDR)&0x0F) + '0';
    date[8] = '\0'; 
    clcd_print("DATE ",LINE1(0));
    clcd_print(date, LINE1(5));
}

unsigned char edit_screen(unsigned char key)
{
    static unsigned int long_press;
    static char ch[][15]={"SET/VIEW EVENT","SET DATE/TIME"};
    if(key == 1)
    {
        RB0 = !RB0;
        long_press =0;
        while(read_key(LEVEL) == 1)
        {
            if(++long_press == 50000)
                return i+3; 
        }
        if(i == 1)
        i--;
    }
    else if(key == 2)
    {
        RB0 = !RB0;
        long_press =0;
        while(read_key(LEVEL) == 2)
        {
            if(++long_press == 50000)
                return DASHBOARD; 
        }
        if(i == 0)
        i++;
    }
    if(i == 0)
    {
        clcd_print_ch(' ',LINE2(0));
        clcd_print(ch[i],LINE1(2));
        clcd_print_ch('*',LINE1(0));
        clcd_print(ch[i+1],LINE2(2));
    }
    else
    {
        clcd_print_ch(' ',LINE1(0));
        clcd_print(ch[i-1],LINE1(2));
        clcd_print_ch('*',LINE2(0));
        clcd_print(ch[i],LINE2(2));
    }
    return EDIT;
}

unsigned char date_time(unsigned char key)
{
    static unsigned int long_press;
    static char ch[][15]={"SET TIME      ","SET DATE      "};
    if(key == 1)
    {
        long_press =0;
        while(read_key(LEVEL) == 1)
        {
            if(++long_press == 50000)
                return i+5; 
        }
        if(i == 1)
        i--;
    }
    else if(key == 2)
    {
        long_press =0;
        while(read_key(LEVEL) == 2)
        {
            if(++long_press == 50000)
                return DASHBOARD; 
        }
        if(i == 0)
        i++;
    }
    if(i == 0)
    {
        clcd_print_ch(' ',LINE2(0));
        clcd_print(ch[i],LINE1(2));
        clcd_print_ch('*',LINE1(0));
        clcd_print(ch[i+1],LINE2(2));
    }
    else
    {
        clcd_print_ch(' ',LINE1(0));
        clcd_print(ch[i-1],LINE1(2));
        clcd_print_ch('*',LINE2(0));
        clcd_print(ch[i],LINE2(2));
    }
    return EDIT_DATE_TIME;
}

unsigned char edit_view_event(unsigned char key)
{
    static unsigned int long_press;
    static char ch[][15]={"SET EVENT     ","VIEW EVENT    "};
    if(key == 1)
    {
        long_press =0;
        while(read_key(LEVEL) == 1)
        {
            if(++long_press == 50000)
                return i+7; 
        }
        if(i == 1)
        i--;
    }
    else if(key == 2)
    {
        long_press =0;
        while(read_key(LEVEL) == 2)
        {
            if(++long_press == 50000)
                return DASHBOARD; 
        }
        if(i == 0)
        i++;
    }
    if(i == 0)
    {
        clcd_print_ch(' ',LINE2(0));
        clcd_print(ch[i],LINE1(2));
        clcd_print_ch('*',LINE1(0));
        clcd_print(ch[i+1],LINE2(2));
    }
    else
    {
        clcd_print_ch(' ',LINE1(0));
        clcd_print(ch[i-1],LINE1(2));
        clcd_print_ch('*',LINE2(0));
        clcd_print(ch[i],LINE2(2));
    }
    return EDIT_VIEW_EVENT;
}