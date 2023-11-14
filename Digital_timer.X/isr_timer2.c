#include "main.h"

void init_timer()
{
    PR2 = 249;
    
    TMR2ON = 1;
    TMR2IF = 0;
    TMR2IE = 1;
}
