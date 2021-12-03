#include "uart.h"

// Define pointers to registers for UART0
unsigned int* PCONP_ptr = PCONP_ADR;
unsigned int* PCLKSEL0_ptr = PCLKSEL0_ADR;
unsigned int* PINSEL0_ptr = PINSEL0_ADR;
unsigned int* U0LCR_ptr = U0LCR_ADR;
unsigned int* U0DLL_ptr = U0DLL_ADR;
unsigned int* U0DLM_ptr = U0DLM_ADR;
unsigned int* U0FDR_ptr = U0FDR_ADR;
unsigned int* U0FCR_ptr = U0FCR_ADR;
unsigned int* U0LSR_ptr = U0LSR_ADR;
unsigned int* U0THR_ptr = U0THR_ADR;
unsigned int* U0RBR_ptr = U0RBR_ADR;

/*----------------------------------------------------------------------------
UART0_Init: setup for UART0 (9600 bps, 8 data bits, 1 stop bit, no parity, no interrupt
*---------------------------------------------------------------------------*/
void UART0_Init(void) {
    //Enable UART0 power: PCON(3) = ‘1’
    *PCONP_ptr |= (1 << 3);

    //Set PCLK for UART0 to CCLK = 100 MHz: PCLKSEL0(7:6) = “01”
    *PCLKSEL0_ptr = (*PCLKSEL0_ptr | (1 << 6)) & ~(1 << 7);

    //8-bit character length, 1 stop bit, no parity, enable divisor latch access via U0LCR
    *U0LCR_ptr = 0x83;

    //U0DLL = least significant byte (LSB) of DL
    *U0DLL_ptr = DL & 0xFF; // or *U0DLL_ptr = 178;

    //U0DLM = most significant byte (MSB) of DL
    *U0DLM_ptr = (DL >> 8) & 0xFF; // or *U0DLM_ptr = 1;

    //Set DIVADDVAL and MULVAL value via U0FDR
    *U0FDR_ptr = ((MULVAL & 0x0F) << 4) + (DIVADDVAL & 0x0F);

    //Enable FIFOs: U0FCR(0) = ‘1’
    *U0FCR_ptr = 0x1;

    // Configure P0.2 pin to function as UART0 TXD0: PINSEL0(5:4)= “01”
    *PINSEL0_ptr = (*PINSEL0_ptr | (1 << 4)) & ~(1 << 5);

    // Configure P0.3 pin to function as UART0 RXD0: PINSEL0(7:6) = “01”
    *PINSEL0_ptr = (*PINSEL0_ptr | (1 << 6)) & ~(1 << 7);

    //Disable divisor latch access (DLAB bit = 0) to read/write U0RBR/U0THR: U0LCR(7) = 0
    *U0LCR_ptr &= ~(1 << 7);
}

void send_char(char c) {
    // wait until Transmitter Holding Register is empty
    while (~(*U0LSR_ptr & (1<<5))) {} // wait until THRE bit == 1 (bit 5 of U0LSR)
    *U0THR_ptr = c;
}

char read_char(void) {
    // wait until Receiver Data Ready Register is empty
    while (~(*U0LSR_ptr & 1)) {} // wait until RDR bit == 1 (UART FIFO is not empty)
    return (char) *U0RBR_ptr;
}