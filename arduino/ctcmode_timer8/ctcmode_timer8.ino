#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 7

void setup() 
{
  DDRD |= (1 << LED_PIN);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);   // Set CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);    //Setting prescalar value to 1024
  OCR1A = 31249;          // Delay of 2 seconds (Blinking/ toogling of an LED)
  TIMSK1 |= (1 << OCIE1A);
  sei();                // Enable all global interrupts

}

void loop() 
{
  // put your main code here, to run repeatedly:

}

ISR (TIMER1_COMPA_vect)
{
  PORTD ^= (1 << LED_PIN);
}