//#include "uart.h"

//void send_char(char c);

int main(void) {

	UART0_Init();
	
	char message[] = "hello world";
	int length = sizeof message / sizeof message[0];

	while (1){
//         int status;
//         do {
//             status = send_char(message[i]);
//         } while (status);
//		 		i++;
//		 		if (i > length-1) break;

		send_string(message, length);
	} // main loop
}


