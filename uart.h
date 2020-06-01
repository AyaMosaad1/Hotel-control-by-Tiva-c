#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART_INIT(void); 

void UART_TransmitChar(unsigned char x); //to write one char by UART
unsigned char UART_ReceiveChar(void);    // Read one char by UART

void UART_TransmitString(char* str);    //Write string by UART

