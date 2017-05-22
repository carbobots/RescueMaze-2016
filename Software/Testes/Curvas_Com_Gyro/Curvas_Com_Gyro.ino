// Funciona em 3.3V (5V tolerant)
// Obtem os RAW data e calcula angulos (Não usa DMP)
// Usa integração simples, ocasionando drift significativo

#include <Wire.h>

// Motor ESQUERDO DIANETEIRO
#define MotorEsquerdoDianteiroFrente 5
#define MotorEsquerdoDianteiroTras 4

// Motor DIREITO DIANTEIRO
#define MotorDireitoDianteiroFrente 3
#define MotorDireitoDianteiroTras 2


// Motor ESQUERDO TRASEIRO
#define MotorEsquerdoTraseiroFrente 9
#define MotorEsquerdoTraseiroTras 8

// Motor DIREITO TRASEIRO
#define MotorDireitoTraseiroFrente 6
#define MotorDireitoTraseiroTras 7

float ligarMotores() {
  // MOTOR ESQUERDO DIANTEIRO
  pinMode(MotorEsquerdoDianteiroFrente, OUTPUT);
  pinMode(MotorEsquerdoDianteiroTras, OUTPUT);

  
  // MOTOR DIREITO DIANTEIRO
  pinMode(MotorDireitoDianteiroFrente, OUTPUT);
  pinMode(MotorDireitoDianteiroTras, OUTPUT);

  
  // MOTOR ESQUERDO TRASEIRO
  pinMode(MotorEsquerdoTraseiroFrente, OUTPUT);
  pinMode(MotorEsquerdoTraseiroTras, OUTPUT);


  // MOTOR DIREITO TRASEIRO
  pinMode(MotorDireitoTraseiroFrente, OUTPUT);
  pinMode(MotorDireitoTraseiroTras, OUTPUT);

}


void pararMotores() {
  analogWrite(MotorEsquerdoDianteiroFrente, 0);
  analogWrite(MotorDireitoDianteiroFrente, 0);            
  analogWrite(MotorEsquerdoDianteiroTras, 0);
  analogWrite(MotorDireitoDianteiroTras, 0);    

  /*** traseiros ***/
  analogWrite(MotorEsquerdoTraseiroFrente, 0);
  analogWrite(MotorDireitoTraseiroFrente, 0);        
  analogWrite(MotorEsquerdoTraseiroTras, 0);
  analogWrite(MotorDireitoTraseiroTras, 0);
}

void mover(int a, int b){
  if (a>0){
    a=a*2.55;
    //a=a+compensacao;
    analogWrite(MotorEsquerdoDianteiroFrente,a);
    analogWrite(MotorEsquerdoTraseiroFrente,a);
    analogWrite(MotorEsquerdoDianteiroTras,0);
    analogWrite(MotorEsquerdoTraseiroTras,0);
  }
  else if(a==0){
    analogWrite(MotorEsquerdoDianteiroFrente,0);
    analogWrite(MotorEsquerdoTraseiroFrente,0);
    analogWrite(MotorEsquerdoDianteiroTras,0);
    analogWrite(MotorEsquerdoTraseiroTras,0);
  }
  else{
    a=a*-2.55;
    analogWrite(MotorEsquerdoDianteiroFrente,0);
    analogWrite(MotorEsquerdoTraseiroFrente,0);
    analogWrite(MotorEsquerdoDianteiroTras,a);
    analogWrite(MotorEsquerdoTraseiroTras,a);
  }
  if (b>0){
    b=b*2.55;
       analogWrite(MotorDireitoDianteiroFrente,b);
    analogWrite(MotorDireitoTraseiroFrente,b);
    analogWrite(MotorDireitoDianteiroTras,0);
    analogWrite(MotorDireitoTraseiroTras,0);
  }
  else if(b==0){
       analogWrite(MotorDireitoDianteiroFrente,0);
    analogWrite(MotorDireitoTraseiroFrente,0);
    analogWrite(MotorDireitoDianteiroTras,0);
    analogWrite(MotorDireitoTraseiroTras,0);
  }
  else{
    b=b*-2.55;
       analogWrite(MotorDireitoDianteiroFrente,0);
    analogWrite(MotorDireitoTraseiroFrente,0);
    analogWrite(MotorDireitoDianteiroTras,b);
    analogWrite(MotorDireitoTraseiroTras,b);
  }  
};


const int MPU = 0x68;						// I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int i;
double gyroScale = 131;						// From datasheet
double timeStep, time, timePrev;
double arx, ary, arz, grx, gry, grz, gsx, gsy, gsz, rx, ry, rz;

void setup(){
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B);						// PWR_MGMT_1 register
	Wire.write(0);							// set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);

	Serial.begin(9600);

	time = millis();
	i = 1;
  ligarMotores();
}

void loop(){
	 timePrev = time;
  	time = millis();
  	timeStep = (time - timePrev) / 1000;	// time-step in s

	Wire.beginTransmission(MPU);
	Wire.write(0x3B);						// starting with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,14,true);			// request a total of 14 registers
	
	AcX=Wire.read()<<8|Wire.read();			// 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
	AcY=Wire.read()<<8|Wire.read();			// 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ=Wire.read()<<8|Wire.read();			// 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	
	Tmp=Wire.read()<<8|Wire.read();			// 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	Tmp = Tmp/340.00 + 36.53;				// Equation for temperature in Celsius (datasheet)
	
	GyX=Wire.read()<<8|Wire.read();			// 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY=Wire.read()<<8|Wire.read();			// 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ=Wire.read()<<8|Wire.read();			// 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
	
	// RAW data saved in AcX, AcY, AcZ, GyX, GyY and GyZ (Tmp isn't RAW)

	/*Serial.print("AcX = ");
	Serial.println(AcX);
	
	Serial.print("AcY = ");
	Serial.println(AcY);
	
	Serial.print("AcZ = ");
	Serial.println(AcZ);
	
	Serial.print("Tmp = ");
	Serial.println(Tmp/340.00+36.53);
	
	Serial.print("GyX = ");
	Serial.println(GyX);

	Serial.print("GyY = ");
	Serial.println(GyY);
	
	Serial.print("GyZ = ");
	Serial.println(GyZ);
	Serial.print("\n");*/

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

	// calculate accelerometer angles
  	arx = (180/3.141592) * atan(AcY / sqrt(square(AcX) + square(AcZ))); 
  	ary = -(180/3.141592) * atan(AcX / sqrt(square(AcY) + square(AcZ)));
  	arz = (180/3.141592) * atan(sqrt(square(AcY) + square(AcX)) / AcZ); 

  	// set initial values equal to accel values
	/*if (i == 1) {
		grx = arx;
		gry = ary;
		grz = arz;
	}
	// integrate to find the gyro angle
	else{*/
		grx = grx + (timeStep * gsx);
    	gry = gry + (timeStep * gsy);
    	grz = grz + (timeStep * gsz);
  	/*}*/

  	// apply filter
  	rx = (0.1 * arx) + (0.9 * grx);
  	ry = (0.1 * ary) + (0.9 * gry);
  	rz = (0.1 * arz) + (0.9 * grz);

  	// print result
  	Serial.println(arx);

  	/*Serial.print(arx);			Serial.print("\t");
  	Serial.print(ary);			Serial.print("\t");
  	Serial.print(arz);			Serial.print("\n");
  	Serial.print(grx);			Serial.print("\t");
    Serial.print(gry);			Serial.print("\t");
  	Serial.print(grz);			Serial.print("\t");
  	Serial.print(rx);			Serial.print("\t");*/
  	//Serial.println(gsz);
  	
   grz = 0;
    while(grz <= 90) {
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
      
      mover(-60,60);
      Serial.println(grz);   
      
    }
   Serial.println("DEU");
   pararMotores();
   delay(4000);
  	i = i + 1;
  	delay(100);

	//delay(333);
}
