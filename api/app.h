/* 
 * File:   app.h
 * Author: Jared
 *
 * Created on 9 July 2013, 2:40 PM
 *
 * User-mode application definitions
 */

#ifndef APP_H
#define	APP_H

typedef void (*proc_t)(void);

typedef struct {
    proc_t init;
    proc_t process;
} application_t;

#define APP(init, process) {init, process}

extern void RegisterUserApplication(application_t* app);

#endif	/* APP_H */

