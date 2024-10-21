// Cre
#include <Arduino_FreeRTOS.h>
#define LED_PIN 7

void taskBlink(void *pvParam);

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  xTaskCreate(taskBlink, "Blink", 128, NULL, 2, NULL);
}

void loop() 
{
  // put your main code here, to run repeatedly:

}

void taskBlink(void *pvParam)
{
  (void) pvParam;
  for (;;)
  {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_PIN, LOW);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
