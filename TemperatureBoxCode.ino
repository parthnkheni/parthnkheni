#include <Wire.h> // allows the Arduino to communicate with I2C devices (LCD)
#include <LiquidCrystal_I2C.h> // Library for LCD

int warning_led_pin = 3;  // Red Led
int temp_sensor_pin = A0; // Temp Sensor. The analog pin the TMP36's Vout (sense) pin is connected to the resolution is 10 mV / degree centigrade with a 500 mV offset to allow for negative temperatures
int buzzer = 5; //Buzzer
LiquidCrystal_I2C lcd(0x20,16,2); // LCD

void setup() {
  Serial.begin(9600); // Initalizing Serial Monitor (used for testing)
  pinMode(warning_led_pin, OUTPUT); // Initalizing the pin for the warning led (Red LED)
  pinMode(buzzer, OUTPUT); // Initalizing the pin for the buzzer
  lcd.init(); // Initalizing the LCD 
}

void loop() {
     int reading = analogRead(temp_sensor_pin); //getting the voltage reading from the temperature sensor
     
     float voltage = reading * 5.0;
     voltage /= 1024.0; // converting that reading to voltage
     
     float temperatureC = (voltage - 0.5) * 100; // converting the voltage to Celsius 
     
     float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; // converting Celsius to Fahrenheit

     lcd.backlight();
     lcd.print(" ");
     // lcd.print("Temperature: "); 
     lcd.print(temperatureC); lcd.println(" degrees C"); // Print variable value to LCD
     lcd.setCursor(1,1);
     lcd.print(temperatureF); lcd.println(" degrees F"); // Print variable value to LCD
     delay(1000); //waiting a second

     // The if statement below is saying that if the temperature is less than 70 or higher than 75, then the warning led is going to blink and the buzzer is going to make a noise. 
     // If the temperature is out of the predetermined bounds, then the warning led is not going to blink and the buzzer is not going to make a noise.
     if(temperatureF < 70 || temperatureF > 75) { 
      digitalWrite(warning_led_pin, HIGH);
      delay(100);
      digitalWrite(warning_led_pin, LOW);
      delay(100);
      tone(buzzer, 1000);
      delay(1000);
      noTone(buzzer);
      delay(1000);
     } else {
      digitalWrite(warning_led_pin, LOW);
      digitalWrite(buzzer, LOW);
     }
}
