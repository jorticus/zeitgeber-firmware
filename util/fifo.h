/* 
 * File:   fifo.h
 * Author: Jared
 *
 * Created on 31 August 2014, 11:09 AM
 */

#ifndef FIFO_H
#define	FIFO_H


typedef struct {
    void**   buffer;
    uint    i_first;   // index of oldest message in buffer
    uint    i_last;    // index of newest message in buffer
    uint    count;     // number of messages currently in buffer
    uint    size;
    
    union {
        byte _flags;
        struct {
            unsigned overflow: 1;
            unsigned underflow: 1;
        };
    };
} fifo_t;

void fifo_init(fifo_t* fifo, size_t fifo_size);

// Push a new value onto the FIFO
void fifo_push(fifo_t* fifo, void* value);

// Pop a value from the FIFO
void* fifo_pop(fifo_t* fifo);

// Returns true if the FIFO is empty
static inline bool fifo_isempty(fifo_t* fifo) {
    return (fifo->count == 0);
}

#endif	/* FIFO_H */

