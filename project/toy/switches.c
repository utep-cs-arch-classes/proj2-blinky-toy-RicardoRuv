#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed; /* effectively boolean */
char switch1, switch2, switch3, switch4;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch1 = (p2val & SW1); /* 0 when SW1 is up */
  switch2 = (p2val & SW2);
  switch3 = (p2val & SW3);
  switch4 = (p2val & SW4);


  if(switch1==0){
    switch_state_changed =0;
     buzzer_set_period(10000);
  }
  else if(switch2==0){
    switch_state_changed =1;
     buzzer_set_period(3000);
  }
  else if(switch3==0){
    switch_state_changed=2;
     buzzer_set_period(5000);
  }
  else if(switch4==0){
    switch_state_changed =3;
    buzzer_set_period(6666);
  }
  switch_update_interrupt_sense();
}
