#include "uart.h"

typedef unsigned char BYTE;

typedef struct Frame {
    BYTE start;
    BYTE data;
    BYTE stop;

} Frame;

Frame* define_frame(Frame* f, char c) {
    f->start = 0;
    f->data = c;
    f->stop = 1;
    return f;
}