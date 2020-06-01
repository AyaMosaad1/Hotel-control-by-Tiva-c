#include <stdint.h>
#include "tm4c123gh6pm.h"

#define Num_col 4
#define Num_row 4


void keypad_Init(void);
unsigned char keypad_getkey(void);
