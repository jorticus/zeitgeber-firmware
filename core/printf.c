/*
 * File:   printf.c
 * Author: Jared
 *
 * Created on 28 August 2014, 6:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdio.h>
#include "system.h"
#include "drivers/usb/usb.h"
#include "background/comms.h"
#include "printf.h"

#define MESSAGE_FIFO_SIZE 16

typedef struct {
    char message[DEBUG_MESSAGE_MAXLEN];
} message_t;

struct {
    message_t buffer[MESSAGE_FIFO_SIZE];
    uint i_first;   // index of oldest message in buffer
    uint i_last;    // index of newest message in buffer
    uint count;     // number of messages currently in buffer
} message_fifo;

void msg_init() {
    message_fifo.i_first = 0;
    message_fifo.i_last = 0;
    message_fifo.count = 0;
}

void msg_push(const char* msg) {
    // Drop the oldest message if buffer is full
    if (message_fifo.count == MESSAGE_FIFO_SIZE-1) {
        msg_pop(NULL);
    }

    // Get a pointer to the message, and copy the data
    char* entry = message_fifo.buffer[message_fifo.i_last].message;
    strncpy(entry, msg, DEBUG_MESSAGE_MAXLEN-1);

    // Add a null char to the end for safety
    entry[DEBUG_MESSAGE_MAXLEN-1] = '\0';

    // Update indices
    if (message_fifo.i_last++ == MESSAGE_FIFO_SIZE-1)
        message_fifo.i_last = 0;
    message_fifo.count++;

}

bool msg_isempty() {
    return (message_fifo.count == 0);
}

bool msg_pop(char* buf) {
    // Check if there are any messages in the FIFO
    if (message_fifo.count > 0) {

        // Get a pointer to the message, and copy the data
        const char* entry = message_fifo.buffer[message_fifo.i_first].message;
        strncpy(buf, entry, DEBUG_MESSAGE_MAXLEN);

        // Update indices
        if (message_fifo.i_first++ == MESSAGE_FIFO_SIZE-1)
            message_fifo.i_first = 0;
        message_fifo.count--;

        return true;
    } else {
        return false; // No messages to be popped
    }
}

#define STDIN   0
#define STDOUT  1
#define STDERR  2

void msg_putc(char c) {
    static char buf[DEBUG_MESSAGE_MAXLEN];
    static uint len = 0;

    buf[len++] = c;

    if (c == '\n' || c == '\0' || len == DEBUG_MESSAGE_MAXLEN-1) {
        buf[len] = '\0';
        msg_push(buf);
        len = 0;
    }
}

// printf() override
int __attribute__((__weak__, __section__(".libc")))
write(int handle, void * buffer, unsigned int len)
{
    int i = 0;
    switch (handle)
    {
        case STDOUT:
        case STDERR:
            while (i < len)
                msg_putc(((char*)buffer)[i++]);
            break;
    }
    return (len);  // number of characters written
}