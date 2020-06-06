#include "Keypad.h"       

uint8_t keypad_symbol[Num_row][Num_col] = {{ '1', '2',  '3', 'A'} ,      
												     				{ '4', '5',  '6', 'B'} ,      
															     	{ '7', '8',  '9', 'C'} ,      
                                    { '*', '0',  '#', 'D'}}; 

																
void keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x02;            //Enable clk in port B
  while ((SYSCTL_RCGCGPIO_R&0x02)==0);  //wait for clock to be enabled
	
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTB_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTB_PDR_R |= 0x0F;             //pull down resistor on Raws
  GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E
}

unsigned char keypad_getkey(void)
{
	uint8_t i,k;
  while(1)
  {
    for(i = 0; i < Num_col; i++)                        //to determine the column
    {
      GPIO_PORTC_DATA_R = (1 << (i+4) );
      for(k = 0; k < Num_row; k++)                     //to determine the row
      {
        if((GPIO_PORTE_DATA_R & 0x1E) & (1U << (k+1))) 
          return keypad_symbol[k][i];
      }
    }
  }
}

