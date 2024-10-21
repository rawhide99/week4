#include <Arduino_FreeRTOS.h>
#define LED_PIN 7
#define BUTTON_PIN 2

volatile bool buttonPressed = false;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  xTaskCreate(blinkPeriodic1, "blink", 128, NULL, 3, NULL);
  xTaskCreate(buttonLog2, "readButton", 512, NULL, -3, NULL);
  xTaskCreate(printMsg3, "status", 128, NULL, -2, NULL);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() 
{
  // put your main code here, to run repeatedly:

}

void blinkPeriodic1(void *pvParam)
{
  (void) pvParam;
  for(;;)
  {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay (1000 / portTICK_PERIOD_MS);
    Serial.println("The led is blinking with least priority.");
  }
}

void buttonLog2(void *pvParam)
{
  (void) pvParam;
  for(;;)
  {
    if(buttonPressed)
    {
      Serial.println("Button is Pressed as task2 with highest priority");
      buttonPressed = false;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void buttonISR() 
{
    buttonPressed = true;
}

void printMsg3(void *pvParam)
{
  (void) pvParam;
  for(;;)
  {
    Serial.println("This is message from Task3 with priority 2.");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  
}
