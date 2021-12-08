#ifndef _UART_H_
#define _UART_H_

// values to set the baud rate to 9600
#define DL          434
#define DIVADDVAL   1
#define MULVAL      2

// define register addresses for UART0
#define PCONP_ADR 0x400FC0C4;
#define PCLKSEL0_ADR 0x400FC1A8;
#define PINSEL0_ADR 0x4002C000;
#define U0LCR_ADR 0x4000C00C;
#define U0DLL_ADR 0x4000C000;
#define U0DLM_ADR 0x4000C004;
#define U0FDR_ADR 0x4000C028;
#define U0FCR_ADR 0x4000C008;
#define U0LSR_ADR 0x4000C014;
#define U0THR_ADR 0x4000C000;
#define U0RBR_ADR 0x4000C000;

extern unsigned int* U0LSR_ptr;
extern unsigned int* U0THR_ptr;

void UART0_Init(void);

int send_char(char c);
void send_string(char* msg, int length);

char read_char(void);

void joystick_init(void);
int get_joystick(void);

int* message_to_control(char *msg);

#endif
