#include <Arduino_FreeRTOS.h>
#define LED_PIN 7

void taskBlink(void *pvParam);

void setup() 
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    xTaskCreate(taskBlink, "Blink", 128, NULL, 2, NULL);
}

void loop() 
{

}

void taskBlink(void *pvParam)
{
    for (;;)
    {
        digitalWrite(LED_PIN, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        digitalWrite(LED_PIN, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        UBaseType_t uxHighWaterMark;
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL); // Check stack highwater mark
        Serial.print("Stack Highwater Mark: ");
        Serial.println(uxHighWaterMark);
    }
}
