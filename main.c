#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad.h"
#include "UART.h"

#define PASSWORD_SIZE 4

enum state{Free = 0 , Occupied , Room_Cleaning}; 

struct Room {
   char  no_of_room ;
   char  password_of_room[PASSWORD_SIZE];
   enum state state_of_room;
};


unsigned char get_no_of_room (void);
unsigned char set_state_of_room(void);
uint8_t* set_init_password(void);
uint8_t check_password(uint8_t* client_pw);
void close_lock(void);
void open_lock(void);


int main(){
	
	
	while(1){

	}
}
	

unsigned char get_no_of_room (void){
	return UART_ReceiveChar();
}

unsigned char set_state_of_room(void){
	return UART_ReceiveChar();
}

uint8_t* set_init_password(void){
	int i ;
	uint8_t *init_pw;
	for (  i = 0 ; i < PASSWORD_SIZE ; i++){
		init_pw[i]= UART_ReceiveChar();
		//set_pw[i]=0;
	}
	return init_pw;
}


//getting password from the client by keypad and check if it's valid or not
uint8_t check_password(uint8_t* client_pw){
	int i ;
		for( i=0; i < PASSWORD_SIZE ; i++){
		uint8_t pw = keypad_getkey();
		//uint16_t pw=0;
		if(pw != client_pw[i]) return 0;
	}
	return 1;
}

void close_lock(void){
	SYSCTL_RCGCGPIO_R|=0x20; //activate clk in  portF
	while ((SYSCTL_RCGCGPIO_R&0x20)== 0);  //wait for clock to be enabled
	
	GPIO_PORTF_DIR_R|=0x0E;  //pin 1,2,3 output
	GPIO_PORTF_DEN_R|=0X0E;
	GPIO_PORTF_DATA_R=0x00;
}

void open_lock(void){
	SYSCTL_RCGCGPIO_R|=0x20; //activate clk in  portF
	while ((SYSCTL_RCGCGPIO_R&0x20)== 0);  //wait for clock to be enabled
	
	GPIO_PORTF_DIR_R|=0x0E;  //pin 1,2,3 is output
	GPIO_PORTF_DEN_R|=0X0E;
	GPIO_PORTF_DATA_R=0x0E;
}

