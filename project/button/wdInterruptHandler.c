#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char state_count =0;
  
  if (++blink_count == 1) {
    // state_advance();
    dimming();
    // function_assembly();
    //  binary_count();
     blink_count = 0;
  }
  
   if(++state_count ==250){
   changeDimming();
   state_count =0;
   }
  
}
