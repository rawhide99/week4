const int pot_pin = A0;    // Pin connected to the potentiometer
const int pwm_pin = 9;     // Pin connected to the LED
int pot_value = 0; 
int pwm_value = 0;

void setup() 
{
    pinMode(pwm_pin, OUTPUT);
    Serial.begin(9600);
}

void loop() 
{
    pot_value = analogRead(pot_pin);

    // Map the potentiometer value to PWM range (0-255)
    pwm_value = map(pot_value, 0, 1023, 0, 255);
    analogWrite(pwm_pin, pwm_value);

    Serial.print("Potentiometer Value: ");
    Serial.print(pot_value);
    Serial.print(" - PWM Value: ");
    Serial.println(pwm_value);

    delay(100);
}
