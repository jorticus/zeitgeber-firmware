/* 
 * File:   printf.h
 * Author: Jared
 *
 * Created on 29 August 2014, 2:27 PM
 */

#ifndef PRINTF_H
#define	PRINTF_H

void msg_init();
void msg_push(const char* msg);
bool msg_isempty();
bool msg_pop(char* buf);

#endif	/* PRINTF_H */

