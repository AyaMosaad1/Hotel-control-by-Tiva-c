#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad.h"
#include "UART.h"

#define PASSWORD_SIZE 4

enum state{Free = '0' , Occupied = '1' , Room_Cleaning = '2'}; 

struct Room {
   char  no_of_room ;
   char  password_of_room[PASSWORD_SIZE];
   enum state state_of_room;
};


unsigned char get_no_of_room (void);
unsigned char set_state_of_room(void);
void set_init_password(char *init_pw);
uint8_t check_password(char* client_pw);
void close_lock(void);
void open_lock(void);


int main(){
	
	UART_INIT();
	keypad_Init();
	
	struct Room hotel_room;
	
	UART_TransmitString("Set data of the room");
	
	hotel_room.no_of_room = get_no_of_room();
	hotel_room.state_of_room = set_state_of_room();
  set_init_password(hotel_room.password_of_room);
	close_lock();
	
	UART_TransmitString("WELCOME");
	
	
	while(1){
		if (hotel_room.state_of_room ==  Occupied ){
			if (check_password(hotel_room.password_of_room)) {open_lock();}
			else
			{
			close_lock();
			UART_TransmitString("Password room is wrong , check if need help!");
			}
		}
		else if (hotel_room.state_of_room == Room_Cleaning){
			open_lock();
		}
		
		else if (hotel_room.state_of_room ==  Free ){
			close_lock();
		}
   }	
}

unsigned char get_no_of_room (void){
	return UART_ReceiveChar();
}

unsigned char set_state_of_room(void){
	return UART_ReceiveChar();
}

void set_init_password(char *init_pw){
	int i ;
	for (  i = 0 ; i < PASSWORD_SIZE ; i++){
		init_pw[i]= UART_ReceiveChar();
	}
}


//getting password from the client by keypad and check if it's valid or not
uint8_t check_password(char* pw){
	int i ;
		for( i=0; i < PASSWORD_SIZE ; i++){
		uint8_t client_pw = keypad_getkey();
			
/*convert the char password to int to compare it with the input from keypad*/
	  int pw_to_Int = pw[i]-'0';
		if(client_pw != pw_to_Int) return 0;
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

