/* 
 * File:   digital_timer.h
 * Author: mdfai
 *
 * Created on 12 October, 2023, 2:42 PM
 */

#ifndef DIGITAL_TIMER_H
#define	DIGITAL_TIMER_H

void read_rtc();
unsigned char edit_screen(unsigned char key);
unsigned char date_time(unsigned char key);
unsigned char edit_view_event(unsigned char key);

#endif	/* DIGITAL_TIMER_H */

