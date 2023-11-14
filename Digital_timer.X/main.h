/* 
 * File:   main.h
 * Author: mdfai
 *
 * Created on 12 October, 2023, 2:27 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "i2c.h"
#include "rtc.h"
#include "digital_timer.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "edit_time_date.h"
#include "view_edit_event.h"

#define DASHBOARD             1
#define EDIT                  2
#define EDIT_VIEW_EVENT       3
#define EDIT_DATE_TIME        4
#define EDIT_TIME             5
#define EDIT_DATE             6
#define SET_EVENT            7
#define VIEW_EVENT            8

void init_timer();
#endif	/* MAIN_H */

