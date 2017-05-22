/****************************************************************************** 
MLX90614_Serial_Demo.ino
Serial output example for the MLX90614 Infrared Thermometer

This example reads from the MLX90614 and prints out ambient and object 
temperatures every half-second or so. Open the serial monitor and set the
baud rate to 9600.

Hardware Hookup (if you're not using the eval board):
MLX90614 ------------- Arduino
  VDD ------------------ 3.3V
  VSS ------------------ GND
  SDA ------------------ SDA (A4 on older boards)
  SCL ------------------ SCL (A5 on older boards)
  
An LED can be attached to pin 8 to monitor for any read errors.

Jim Lindblom @ SparkFun Electronics
October 23, 2015
https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library

Development environment specifics:
Arduino 1.6.5
SparkFun IR Thermometer Evaluation Board - MLX90614
******************************************************************************/

#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library

#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


IRTherm therm; // Create an IRTherm object to interact with throughout
IRTherm therm2; // Create an IRTherm object to interact with throughout
IRTherm therm3; // Create an IRTherm object to interact with throughout
IRTherm therm4; // Create an IRTherm object to interact with throughout

const byte LED_PIN = 13; // Optional LED attached to pin 8 (active low)

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output
  lcd.begin(16,2);               // initialize the lcd 

  therm.begin(0x5A); // Initialize thermal IR sensor
  therm.setUnit(TEMP_C); // Set the library's units to Farenheit

  therm2.begin(0x5B); // Initialize thermal IR sensor
  therm2.setUnit(TEMP_C); // Set the library's units to Farenheit

    therm3.begin(0x5C); // Initialize thermal IR sensor
  therm3.setUnit(TEMP_C); // Set the library's units to Farenheit

    therm4.begin(0x5D); // Initialize thermal IR sensor
  therm4.setUnit(TEMP_C); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
}

void loop() 
{
  
  //setLED(HIGH); //LED on
  
  // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read() && therm2.read() && therm3.read() && therm4.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
	// temperatures.
	// They'll be floats, calculated out to the unit you set with setUnit().
    lcd.setCursor(0,0);
    lcd.print("D:" + String(therm.object(), 2) + " F:" + String(therm2.object(), 2));
    lcd.setCursor(0,1);
    lcd.print("E:" + String(therm3.object(), 2) + " T:" + String(therm4.object(), 2));
  }
  delay(500);
}
