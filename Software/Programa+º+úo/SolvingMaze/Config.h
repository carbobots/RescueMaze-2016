#include <Arduino.h>

/*
  ROBOT GENERAL CONFIGURATION
*/

/************************ MOTORES ************************/
// Motores: Pololu 75:1 Metal Gearmotor 25Dx54L mm MP 12V 2.1A


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


/************************ SENSORES ************************/
// Sensores: Pololu QTR-8A reflectance sensor, Sharp 4-30cm, Sharp 10-80cm, Divisor de Tensão, GY906 Temperature, GY521 IMU, Botões Laterais
// PORTAS ANÁLOGICAS

// SENSORES ARRAY QTR-8-A
#define luminosidade1     A5 // SENSOR Frente
#define luminosidade2     A6 // SENSOR TRPAS

int QTR[] = {
  0,
  luminosidade1,
  luminosidade2,
};
int lerQTR(int pino) {
  return analogRead(QTR[pino]);
}

/*// SENSORES SHARP PEQUENO 4-30cm
#define sharp_pequeno1     A11 // SENSOR DA ESQUERDA
#define sharp_pequeno2     A12 // SENSOR DA DIREITA
#define sharp_pequeno3     A13 // SENSOR DA FRENTE
#define sharp_pequeno4     A14 // SENSOR DA TRÁS

int Sharp_Pequeno[] {
  0,
  sharp_pequeno1,
  sharp_pequeno2,
  sharp_pequeno3,
  sharp_pequeno4
};
*/
// SENSORES SHARP GRANDE 10-80cm
#define sharp_grande1     A7 // SENSOR DA Frente
#define sharp_grande2     A13 // SENSOR DA Direito
#define sharp_grande3     A8 // SENSOR DA Tras
#define sharp_grande4     A9  // SENSOR DA Esquerdo

int Sharp_Grande[] {
  0,
  sharp_grande1,
  sharp_grande2,
  sharp_grande3,
  sharp_grande4
};
int lerSharp(int pino) {
  int i = analogRead(Sharp_Grande[pino]);
  
  int val =(6762/(i-9))-4;
  
  return val;
  
}

// Tensão Bateria
#define VBAT    A0 // SENSOR DE TENSÃO DA BATERIA
#define VOLTAGE_LOW   11.5 // Tensão mínima
#define VOLTAGE_HIGH  14 // Tensão maxima

// 0 in ADC now means -5v. full ADC (1024) means 10v
AnalogVoltage myCustomVoltimeter(VBAT, 0, 16);
// Turns LED on
float pinVoltage = myCustomVoltimeter.readVoltage();

// Giroscópio e AcelerometrO Gy 521
#define imu_gyro 0x68

const int MPU = imu_gyro;            // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int i;
double gyroScale = 131;           // From datasheet
double timeStep, time, timePrev;
double arx, ary, arz, grx, gry, grz, gsx, gsy, gsz, rx, ry, rz;

// Sensor de temperatura Gy 906
#define temp1 0x5B // Frente
#define temp2 0x5A // Direita
#define temp3 0x5D // Trás
#define temp4 0x5C // Esquerda

int Temperatura_Sensor[] {
  0,
  temp1,
  temp2,
  temp3,
  temp4 
};
IRTherm therm1; // Create an IRTherm object to interact with throughout
IRTherm therm2; // Create an IRTherm object to interact with throughout
IRTherm therm3; // Create an IRTherm object to interact with throughout
IRTherm therm4; // Create an IRTherm object to interact with throughout

void ligarTemps() {
  therm1.begin(Temperatura_Sensor[1]); // Initialize thermal IR sensor
  therm1.setUnit(TEMP_C); // Set the library's units to Farenheit
  
  therm2.begin(Temperatura_Sensor[2]); // Initialize thermal IR sensor
  therm2.setUnit(TEMP_C); // Set the library's units to Farenheit
  
  therm3.begin(Temperatura_Sensor[3]); // Initialize thermal IR sensor
  therm3.setUnit(TEMP_C); // Set the library's units to Farenheit
  
  therm4.begin(Temperatura_Sensor[4]); // Initialize thermal IR sensor
  therm4.setUnit(TEMP_C); // Set the library's units to Farenheit
  
}
#define OBJ 20
#define ABT -20

#define TEMP_MINIMA 25
#define TEMP_MAXIMA 40

float lerTemp(int number, int tipo) {
  if(number == 1) {
    therm1.read();
    if(tipo == OBJ)
    return therm1.object();

    if(tipo == ABT)
    return therm1.ambient();
  }
  if(number == 2) {
    therm2.read();
    if(tipo == OBJ)
    return therm2.object();

    if(tipo == ABT)
    return therm2.ambient();
  }
  if(number == 3) {
    therm3.read();
    if(tipo == OBJ)
    return therm3.object();

    if(tipo == ABT)
    return therm3.ambient();
  }
  if(number == 4) {
    therm4.read();
    if(tipo == OBJ)
    return therm4.object();

    if(tipo == ABT)
    return therm4.ambient();
  }
  
}
//float temperatura_ambiente = (therm1.ambient()+therm2.ambient()+therm3.ambient()+therm4.ambient()) / 4;

/************************ SERVOS ************************/
// SERVO MOTORES PARA A GARRA - 180 graus - Servo 9g
// PORTAS PWM
#define servo_frente 12 // PORTA PWM
#define servo_tras 11 // PORTA PWM

Servo myservo;
Servo myservo2;
 
/************************ INTERFACE ************************/
// Botões para iniciar ações 
// PORTAS DIGITAIS
#define btn1 30 // LED Robô ligado
#define btn2 31 // LED Tensão bateria
#define btn3 37 // LED Teste do robô
#define btn4 36 // LED Calibração

int Botoes[] {
  0,
  btn1,
  btn2,
  btn3,
  btn4
};
DigitalIn Botao1(btn1);
DigitalIn Botao2(btn2);
DigitalIn Botao3(btn3);
DigitalIn Botao4(btn4);


// LEDs para identificação de ações 
#define led1  39 // LED Robô ligado
#define led2  32 // LED Tensão bateria - correto
#define led3  34 // LED Teste do robô - correto
#define led4  35 // LED Calibração - correto

int LEDs[] {
  0,
  led1,
  led2,
  led3,
  led4
};
DigitalOut LED1(led1);
DigitalOut LED2(led2);
DigitalOut LED3(led3);
DigitalOut LED4(led4);

// LCD I2C
#define lcd_i2c 0x27
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(lcd_i2c,2,1,0,4,5,6,7,3, POSITIVE);


// Buzzer para fazer barulinho
#define buzzer 22
DigitalOut Buzzer(buzzer);


/*** ARRAYS DO MAZE ***/


/************************ ESTADOS *********************/
#define ESQUERDA -1
#define DIREITA   1
#define ST_PRINCIPAL 2
#define ST_RAMPA     4
#define CIMA 1
#define BAIXO 0

#define NORTE 1
#define LESTE 2
#define SUL 3
#define OESTE 4

/************************ VARIÁVEIS DO ROBÔ ************************/
#define tempoandar ( 3050 * myCustomVoltimeter.readVoltage() ) / VOLTAGE_HIGH
int distancia_parede = 20;
int andou;
int situacao;
int numero;

int norte; // 1
int leste; // 2
int sul; // 3
int oeste; // 4


int forca = 60;
int forca_Baixa = 40;
unsigned long tempoinicial = millis();

int xatual;
int yatual;
int xinicial = 30;
int yinicial = 30;
String coordenadaatual;


int Historico[] = {0};
int Encruzilhada[] = {0};
int BlackSpace[20];

//int branco_default = 700;
int checkpoint_default = 350;
int blackspace_default = 180;

//int branco_value;
int checkpoint_value;
int blackspace_value;





int forca_Curva = 55;

//float KP = 0.03; // Constante do Proporcional
float KP = 0.04; // Constante do Proporcional
float KI = 0.1;
float KD = 0.7; // Constante do Proporcional
//float KD = 0.5; // Constante do Proporcional


int branco = 100; // Força normal para seguir linha
int preto = 650; // Força para rampa


int offset = ((branco + preto) / 2); // media seguidor

int setPoint = 3500;


