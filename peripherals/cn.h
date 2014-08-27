/* 
 * File:   cn.h
 * Author: Jared
 *
 * Created on 27 August 2014, 9:21 PM
 */

#ifndef CN_H
#define	CN_H

typedef void (*cn_cb)(bool value);

// Register a pin-change interrupt callback
void cn_register_cb(uint cn_pin, pinref_t pinref, cn_cb callback);

#endif	/* CN_H */

