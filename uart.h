#ifndef _UART_H_
#define _UART_H_

#define start_bit 0
#define stop_bit 1

typedef unsigned char BYTE;

struct Frame {
    BYTE start;
    BYTE data;
    BYTE stop;
};

typedef struct Frame Frame;

extern Frame* define_frame(Frame* f, char c);

#endif