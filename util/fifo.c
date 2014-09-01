/*
 * File:   fifo.c
 * Author: Jared
 *
 * Created on 31 August 2014, 11:09 AM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "fifo.h"
//#include "fifo.h"


void fifo_init(fifo_t* fifo, size_t fifo_size) {
    fifo->count = 0;
    fifo->i_first = 0;
    fifo->i_last = 0;
    fifo->_flags = 0;

    fifo->buffer = malloc(fifo_size);  // Allocate an array of empty pointers
    fifo->size = fifo_size;
}

void fifo_push(fifo_t* fifo, void* value) {
    // Drop the oldest message if buffer is full
    if (fifo->count == fifo->size) {
        msg_pop();
    }

    fifo->buffer[fifo->i_last] = value;

    // Update indices
    if (fifo->i_last++ == fifo->size)
        fifo->i_last = 0;
    fifo->count++;
}

void* fifo_pop(fifo_t* fifo) {
    // Check if there are any messages in the FIFO
    if (fifo->count > 0) {

        void* value = fifo->buffer[fifo->i_first];

        // Update indices
        if (fifo->i_first++ == fifo->size)
            fifo->i_first = 0;
        fifo->count--;

        return value;
    } else {
        return 0; // No messages to be popped
    }
}
