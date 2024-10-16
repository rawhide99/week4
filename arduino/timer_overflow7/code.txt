#include <TimerOne.h>
#define MS 1000000

volatile unsigned long seconds_count = 0;
unsigned long delay_set = 5000;

void setup() 
{
    Serial.begin(9600);
    Timer1.initialize(MS);
    Timer1.attachInterrupt(timer_overflow_ISR);
    Timer1.start();
}

void loop() 
{
    if (seconds_count >= (delay_set / 1000)) 
    {
        Serial.println("Delay period has passed!");
        seconds_count = 0;
    }

    delay(1000);
    Serial.print("Seconds Counted: ");
    Serial.println(seconds_count);
}

void timer_overflow_ISR() 
{
    seconds_count++; // Increment the seconds count
}
