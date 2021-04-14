#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char control = 0;

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}


/*char toggle_green()    /* only toggle green if red is on!  
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}
*/
char toggle_green()/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    green_on = 1;
    state = 1;
    break;

  case 1:
    green_on = 0;
    state = 0;
    break;
  }
  return 1;
}



void state_advance()/* alternate between toggling red & green */ 
{
  char changed = 0;
  static enum {R=0, G=1} color = G;

  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();

}

void binary_count() 
{
  static char state = 0;
  switch (state) {

  case 0: red_on = 0; green_on = 0; break;

  case 1: red_on = 1; green_on = 0; break;

  case 2: red_on = 0; green_on = 1; break;

  case 3: red_on = 1; green_on = 1; state = -1;
    // switch back to case 0, since update will increment it to 0
  }
  state++; 
  led_changed=1;
  led_update();
}

static char dim =0;
void dimming(){

  // static char state =0;

  switch(dim){
  case 0: led_25(); break;
  case 1: led_50(); break;
  case 2: led_75(); break;
  case 3: led_100(); break;
  case 4: led_0(); break;
  }
}

void changeDimming(){
  if (dim ==0){
      dim =1;
      // buzzer_set_period(6666);
    }
  else if (dim == 1){
    dim =2;
    // buzzer_set_period(4000);
  }
  else if(dim ==2){
    // buzzer_set_period(5000);
    dim =3;
  }
  else if (dim == 3){
    // buzzer_set_period(4500);
    dim =4;
  }
  else if(dim ==4){
    // buzzer_set_period(3400);
    dim =0;
  }
}


void led_100(){

  red_on = 1;
  green_on =1;
  led_changed = 1;
  led_update();
}

void led_75(){

  static char state = 0;

  int i;

  if(state == 0){

    red_on = 0;
    green_on = 0;
    state = 1;
     led_update();

  } else if(state == 1){
    red_on = 1;
    green_on = 1;
    state = 2;
    led_update();

  } else if(state == 2){
    red_on = 1;
    green_on = 1;
    state = 3;
   led_update();

  } else if(state == 3){
    red_on = 1;
    green_on = 1;
    state = 0;
     led_update();
  }

  led_changed = 1;
   led_update();
}

void led_50(){

  static char state = 0;

  if(state == 0){
    red_on = 0;
    green_on = 0;
    state = 1;
    led_update();

  } else {
    red_on = 1;
    green_on = 1;
    state = 0;
    led_update();
  }
  led_changed = 1;
   led_update();

}

void led_25(){

  static char state = 0;

  if(state == 0){
    red_on = 0;
    green_on = 0;
    state = 1;
    led_update();
  } else if(state == 1){

    red_on = 0;
    green_on = 0;
    state = 2;
    led_update();
  } else if(state == 2){
    red_on = 0;
    green_on = 0;
    state = 3;
    led_update();
  } else if(state == 3){
    red_on = 1;
    green_on = 1;
    state = 0;
    led_update();
  }
  led_changed = 1;
   led_update();
}
void led_0(){
  green_on=0;
  red_on=0;
  led_changed =1;
  led_update();
}
