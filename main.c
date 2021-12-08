//#include "uart.h"

//void send_char(char c);

int main(void) {

	UART0_Init();
	joystick_init();
	LEDs_Init();
	
	char *message = "hello world ";
	int length = 12;//sizeof message / sizeof message[0];

	//char c;
	
	int joystick;
	
	const char *commands[4];
	commands[0] = "u5E";
	commands[1] = "r5E";
	commands[2] = "d5E";
	commands[3] = "l5E";

	// int i = 0;
	// int status = 0;
	// int m_dir[2];

	while (1){
		joystick = get_joystick();
		if (joystick != -1) {
			message = commands[joystick];
			LEDs(joystick);
			send_string(message, 3);
		}
		
		// while (status != 1) {
		// 	// Check to make sure U0RBR has an unread character
		// 	if (*U0LSR_ptr & (1))		// if bit 0 (or RDR bit) == 1
		// 	{
		// 		received[i] = *U0RBR & 0xFF;
		// 		if (received[i] == 'E') { status = 1; }
		// 		i++;
		// 		if (i==MESSAGE_SIZE_MAX) 
		// 			i = 0;
		// 	}
		// }
		// status = 0;
		
		// m_dir = message_to_control(received);
	} // main loop
}


