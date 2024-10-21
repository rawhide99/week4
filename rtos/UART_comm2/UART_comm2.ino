const int buttonPin = 2; 
volatile bool buttonPressed = false;

void setup() 
{
    Serial.begin(9600);            
    pinMode(buttonPin, INPUT);      
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, RISING);  
}

void loop() 
{
    if (buttonPressed) 
    {
      Serial.println("Button was pressed!"); 
      buttonPressed = false;
    }
}

void buttonISR() 
{
    buttonPressed = true;
}
