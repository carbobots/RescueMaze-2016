

/*
 * Programacao para o torneio CBR Rescue Maze 2016
 * Desenvolvido por Felipe Silva e Felipe Tiozo;
 * Time Carbobots;
 * Apoio: Engenhoteca, Raos Cursos, Sianinha Corte e Costura, Porto Windows, 100% Pizza, Bem+Mais Publicidade & Design, Carpe Diem Revisões; 
 * http://facebook.com/carbobots
 */

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Thread.h>
#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include <ArduinoSensors.h>
#include <sensors/AnalogVoltage.h>

#include <SparkFunMLX90614.h>

/// Basic robot definitions
#include "Config.h"

#include "Readings.h" // lê
#include "Verifications.h" // verifica
#include "Actions.h" // age
#include "Controllers.h" // controla


void setup() {
  Serial.begin(9600);
  
  // SETUP DE TUDO
  ligarMotores(); // ligar motores
  ligarTemps(); // ligar temps
  lcd.begin (16,2); // ligar lcd
  myservo.attach(servo_frente);
  myservo2.attach(servo_tras);
 
  //myservo.write(0); // zera posicionamneto dos servos
  //myservo2.write(20);
  
  // Ligando MPU
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);           // PWR_MGMT_1 register
  Wire.write(0);              // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);


  // Acender Todos LEDs
  // Dar Beep no buzzer
  Buzzer.turnOn();
  LED1.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  LED4.turnOn();
  delay(150);
  Buzzer.turnOff();
  LED1.turnOff();
  LED2.turnOff();
  LED3.turnOff();
  LED4.turnOff();
  delay(300);
  Buzzer.turnOn();
  LED1.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  LED4.turnOn();
  delay(150);
  Buzzer.turnOff();
  LED2.turnOff();
  LED3.turnOff();
  LED4.turnOff();
  
  
  // Mostrar no LCD 'Inicializando...'
  MostrarLCD(CIMA, 0, "Inicializando...");
  delay(800);
  MostrarLCD(CIMA, 0, "                ");
  
}


void loop() {
  
  
  // Se a bateria estiver baixa, leds piscando, beep no buzzer e mensagem na tela "Bateria Baixa"       
  checarBateria();  

  // Mostrar no LCD Nível da Bateria
  MostrarLCD(CIMA, 0, String(myCustomVoltimeter.readVoltage()) + "V");
  MostrarLCD(CIMA, 8, String(blackspace_value));

  // Menu
  MostrarLCD(BAIXO, 9, "MENU");
  MostrarLCD(BAIXO, 0, "INI TES CAL RES");
  // Botões:
    // 1. Iniciar a programação do Maze
    // 2. Iniciar Testes
    // 3. Calibrar o QTR
    // 4. Sair de um Menu


  
  if(Botao1.readValue() == HIGH) {
    rodar(true);
    calibrar(false);
  }
  if(Botao2.readValue() == HIGH) {
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");
    while(Botao4.readValue() != HIGH){
    
    delay(3000);
    mover(60,60);
    delay(tempoandar);
     pararMotores();
    delay(2000); 
    }
    delay(300);
    //CurvaGyro(85, 40);
   
  }
  if(Botao3.readValue() == HIGH) {
    rodar(false);
    calibrar(true);
  }
  if(Botao4.readValue() == HIGH) {
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");
    delay(300);
    while(Botao4.readValue() != HIGH){
       //MostrarLCD(CIMA, 0, checarBytesQuadrado());
      MostrarLCD(CIMA, 0, "                ");
      MostrarLCD(BAIXO, 0, "                ");
      MostrarLCD(CIMA, 0, "F:" + String(lerSharp(1)) + "  T:" + String(lerSharp(3)));
      MostrarLCD(BAIXO, 0, "D:" + String(lerSharp(2)) + "  E:" + String(lerSharp(4)));
      delay(100);
    }
    delay(300);
    while(Botao4.readValue() != HIGH){
      MostrarLCD(CIMA, 0, "                ");
      MostrarLCD(BAIXO, 0, "                ");
      delay(50);
      MostrarLCD(CIMA, 0, "F:" + String(lerTemp(1, OBJ)) + "  T:" + String(lerTemp(3, OBJ)));
      MostrarLCD(BAIXO, 0, "D:" + String(lerTemp(2, OBJ)) + "  E:" + String(lerTemp(4, OBJ)));
    }
    delay(300);

    
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");
  }

                
  // Mostrar no LCD Valores Sharp 4-30

  // Mostrar no LCD valores Sharp 10-80

  // Mostrar no LCD valores Temp.

  // Mostrar no LCD valores LDR

  // Mostrar no LCD valores da IMU




     // INICIAR PROGRAMACAO
     
        // cria variaveis e arrays
         
        // RUN (REPETIR)
            
            // mostrar quadrado atual
            
            // verificaBateria
            
            // verificarRampa
                // Modo Rampa
                    // PID na parede
                    // Verificar Vitimas
                    
            // se nao
            
            // VERIFICAR QUADRADO ATUAL
                // verificarBlackSpace
                // verificarCheckpoint
                // verificarParedesProximas
                    // Esquerda, Direita, Trás e Frente
                // verificarParedesDistantes
                    // Esquerda, Direita, Trás e Frente
                // verificarVitima
                    // Esquerda, Direita, Trás e Frente
                // GUARDA TUDO
            
            // Deixar Rescue Kit
            
            // Voltar do Black Space
                // se nao for blackspace vem o algortimo
                
            // VEM O ALGORITMO PARA A TOMADA DE AÇÕES
                // andar frente
                // andar direita
                // andar esquerda
                // andar trás
                
            // PSEUDOCODE: http://www.alexhadik.com/micromau5/


}

