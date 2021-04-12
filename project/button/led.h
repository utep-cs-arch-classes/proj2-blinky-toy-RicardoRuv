#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

extern unsigned char red_on, green_on;
extern unsigned char led_changed;

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */
void led_100();
void led_75();
void led_50();
void led_25();
void led_0();

void dimming();
void changeDimming();
void function_assembly();

// these are boolean flags
extern unsigned char leds_changed, green_led_state, red_led_state;

#endif
