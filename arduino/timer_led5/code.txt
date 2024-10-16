#include <TimerOne.h>

#define LED_PIN 7 
#define BLINK_INTERVAL 1000000 

volatile bool ledState = false;

void setup() 
{
    pinMode(LED_PIN, OUTPUT);
    Timer1.initialize(BLINK_INTERVAL); 
    Timer1.attachInterrupt(toggleLED); 
}

void loop() 
{
    // Main loop can be used for other tasks
}


void toggleLED() 
{
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
}
