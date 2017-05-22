#include <Arduino.h>
#include <Wire.h>
/*
  FUNÇÕES de leitura DO ROBÔ
*/

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
/*

int lerSharp(int numero_sensor) {
  return analogRead(Sensores_Sharp[numero_sensor]);  
}

int lerBotao(int numero_sensor) {
  return digitalRead(Botoes[numero_sensor]);  
}

void acenderLED(int numero_led) {
  digitalWrite(LEDS[numero_led], HIGH);
}

void LeituraTodosQTR() {
  // read raw sensor values
  qtra.read(sensorValues);
  
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum reflectance and
  // 1023 means minimum reflectance
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  delay(250);
}

*/



void MostrarLCD(int posicaolcd, int posicaocentral, String mensagem) {
  if (posicaolcd == CIMA) {
      lcd.setCursor(posicaocentral,0);   
  } else {
      lcd.setCursor(posicaocentral,1);
  }
  lcd.print(mensagem);
}

double lendoMpuGyro() {
   timePrev = time;
    time = millis();
    timeStep = (time - timePrev) / 1000;  // time-step in s

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);           // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);      // request a total of 14 registers
  
  AcX=Wire.read()<<8|Wire.read();     // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();     // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();     // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  Tmp=Wire.read()<<8|Wire.read();     // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp = Tmp/340.00 + 36.53;       // Equation for temperature in Celsius (datasheet)
  
  GyX=Wire.read()<<8|Wire.read();     // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();     // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();     // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // offset from MPU6050_calibration.ino
  AcX = AcX - 1398;
  AcY = AcY - 962;
  AcZ = AcZ + 1117;
  GyX = GyX + 57;
  GyY = GyY + 35;
  GyZ = GyZ - 26;

  // apply gyro scale from datasheet
  gsx = GyX/gyroScale;
  gsy = GyY/gyroScale;
  gsz = GyZ/gyroScale;

      grx = grx + (timeStep * gsx);
      gry = gry + (timeStep * gsy);
      grz = grz + (timeStep * gsz);

      return grz;
}
double lendoMpuAccel() {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);           // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);      // request a total of 14 registers
  
  AcX=Wire.read()<<8|Wire.read();     // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();     // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();     // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  Tmp=Wire.read()<<8|Wire.read();     // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp = Tmp/340.00 + 36.53;       // Equation for temperature in Celsius (datasheet)
  
  GyX=Wire.read()<<8|Wire.read();     // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();     // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();     // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // offset from MPU6050_calibration.ino
  AcX = AcX - 1398;
  AcY = AcY - 962;
  AcZ = AcZ + 1117;

  // apply gyro scale from datasheet
 arx = (180/3.141592) * atan(AcY / sqrt(square(AcX) + square(AcZ))); 
   ary = -(180/3.141592) * atan(AcX / sqrt(square(AcY) + square(AcZ)));
    arz = (180/3.141592) * atan(sqrt(square(AcY) + square(AcX)) / AcZ); 

      return arx;
}


bool lerProximoQuadrado (int valordocampo) {

  //if(lerQTR(
}
void I2CScanner() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  delay(5000);           // wait 5 seconds for next scan
}

