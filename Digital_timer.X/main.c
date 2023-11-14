#include "main.h"
extern char i;
void init_config()
{
    //intializing the perifeferral
    init_clcd();
    init_i2c();
    init_ds1307();
    init_timer();
    init_matrix();
    TRISB0 = 0;            
    RB0 = 0;                
}

void main()
{
    init_config();
    unsigned char key, s_flag = DASHBOARD;
    while(1)
    {
        
        key = read_key(EDGE);
        if((key == 1 || key == 2) && s_flag == DASHBOARD)  
        {
                s_flag = EDIT;
                key = 0;
                i = 0;
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                     
        }
        switch(s_flag)
        {
            case DASHBOARD :   i=0;
                               read_rtc();
            break;
            case EDIT : if((s_flag = edit_screen(key)) != EDIT)
            {
                i = 0;
                CLEAR_DISP_SCREEN;
                __delay_us(500);
            }                  
            break;
            case EDIT_DATE_TIME : if((s_flag = date_time(key)) != EDIT_DATE_TIME)
            {
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                get_time();
            }
            break;
            case EDIT_VIEW_EVENT : if((s_flag = edit_view_event(key)) != EDIT_VIEW_EVENT)
            {
                CLEAR_DISP_SCREEN;
                __delay_us(500);
                get_time();
            }
            break;
            case EDIT_TIME : clcd_print("HH:MM:SS", LINE1(4));
                             s_flag = set_time(key);
            break;
            case EDIT_DATE : clcd_print("DD:MM:YY", LINE1(4));
                             s_flag = set_date(key);
            break;
            case VIEW_EVENT : view_event(key);
            break;
            case SET_EVENT : clcd_print("Time",LINE1(0));
                             clcd_print("Dur",LINE2(0));
                             set_ev(key);
            break;
        }
    }
}
