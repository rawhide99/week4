#include <avr/io.h>
#include <avr/interrupt.h>

#define LED1_PIN 7
#define LED2_PIN 2

#define LED1_INTV 1000  // LED1 interval in milliseconds
#define LED2_INTV 800   // LED2 interval in milliseconds

#define LED1_CNT  5     // Number of blinks for LED1
#define LED2_CNT 10     // Number of blinks for LED2

volatile uint8_t led1_count = 0; 
volatile uint8_t led2_count = 0; 

void setup() 
{
  Serial.begin(9600); // Start serial communication
  DDRD |= (1 << LED1_PIN) | (1 << LED2_PIN); // Set LED pins as outputs

  // Timer 1 setup for LED1 (1 second)
  TCCR1A = 0; 
  TCCR1B = 0; 
  TCCR1B |= (1 << WGM12); // Set CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  OCR1A = 15624; // Set compare value for 1 second
  TIMSK1 |= (1 << OCIE1A); // Enable Timer 1 Compare A Match interrupt

  // Timer 2 setup for LED2 (300 ms)
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= (1 << WGM21); // Set CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS20); // Set prescaler to 1024
  OCR2A = 12499; // Set compare value for 800 ms
  TIMSK2 |= (1 << OCIE2A); // Enable Timer 2 Compare A Match interrupt

  sei(); // Enable global interrupts
}

void loop() 
{
  // Main code can run here, if needed
}

// ISR for Timer 1 (LED1)
ISR(TIMER1_COMPA_vect)
{
  static uint8_t led1_state = 0; // State for LED1 (0: OFF, 1: ON)

  if (led1_count < LED1_CNT * 2) // Each toggle counts as ON and OFF
  {
    led1_state = !led1_state; // Toggle state
    PORTD = (PORTD & ~(1 << LED1_PIN)) | (led1_state << LED1_PIN); // Update LED1 state
    Serial.println("Hello from LED1");
    led1_count++;
  }
}

// ISR for Timer 2 (LED2)
ISR(TIMER2_COMPA_vect)
{
  static uint8_t led2_state = 0; // State for LED2 (0: OFF, 1: ON)

  if (led2_count < LED2_CNT * 2) // Each toggle counts as ON and OFF
  {
    led2_state = !led2_state; // Toggle state
    PORTD = (PORTD & ~(1 << LED2_PIN)) | (led2_state << LED2_PIN); // Update LED2 state
    Serial.println("Hello from LED2");
    led2_count++;
  }
}