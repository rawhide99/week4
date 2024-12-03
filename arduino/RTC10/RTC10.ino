#include<avr/io.h>
#include<avr/interrupt.h>

#define LED_PIN 7
volatile int hrs = 0;
volatile int mins = 0;
volatile int secs = 0;


void setup() 
{
  Serial.begin(9600);
  DDRD |= (1 << LED_PIN);

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);               // Set CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024 
  OCR1A = 15624;                      // Set compare value for 1 second
  TIMSK1 |= (1 << OCIE1A);           

  sei();                           //  Enable global interrupts
}

void loop() 
{
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime >= 3000) 
  {
    lastPrintTime = millis();
    
    // Print the current time in HH:MM:SS format
    Serial.print("Current Time: ");
    Serial.print(hrs < 10 ? "0" : "");  // Leading zero for hours
    Serial.print(hrs);
    Serial.print(":");
    Serial.print(mins < 10 ? "0" : ""); // Leading zero for minutes
    Serial.print(mins);
    Serial.print(":");
    Serial.print(secs < 10 ? "0" : ""); // Leading zero for seconds
    Serial.println(secs);
  }
}

ISR(TIMER1_COMPA_vect)
{
  secs++;
  
  if(secs >= 60)
  {
    secs = 0;
    mins++;
  }

  if(mins >= 60)
  {
    mins = 0;
    hrs++;
  }

  if(hrs >= 24)
  {
    hrs = 0;
  }

}
