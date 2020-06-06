#include "UART.h"

void UART_INIT(void){
SYSCTL_RCGCUART_R |= 0x0001; // activate UART0
SYSCTL_RCGCGPIO_R |= 0x0001; // activate port A
UART0_CTL_R &= ~0x0001; // disable UART
UART0_IBRD_R = 27; // IBRD=int(50000000/(16*115,200)) = int(27.1267)
UART0_FBRD_R = 8; // FBRD = round(0.1267 * 64) = 8
UART0_LCRH_R = 0x0070; // 8-bit word length, enable FIFO
UART0_CTL_R = 0x0301; // enable RXE, TXE and UART
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011; 
GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog
GPIO_PORTA_AFSEL_R |= 0x03; // enable alt 
GPIO_PORTA_DEN_R |= 0x03; // enable digital 
}

void UART_TransmitChar(unsigned char D ){
	while((UART1_FR_R&UART_FR_TXFF) !=0);  // wait until TXFF is 0
	UART1_DR_R = D ;
}

unsigned char UART_ReceiveChar(void){
	while((UART1_FR_R&UART_FR_RXFE) !=0);  
	return UART1_DR_R;	
}

void UART_TransmitString(char* str){
	int i = 0 ;
	while(str[i] != '\0'){
		UART_TransmitChar(str[i]);
		i++;
	}
}	

