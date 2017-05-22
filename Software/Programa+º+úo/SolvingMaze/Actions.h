#include <Arduino.h>
#include <Servo.h>
/*
  FUNÇÕES de Ação DO ROBÔ
*/

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
/*** bloco okk ****/
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

/*** bloco ok ***/
void CurvaGyro(double angulo, int forca_curva){
  //MostrarLCD(CIMA, 0, "                ");
 // MostrarLCD(BAIXO, 0, "                ");
      
  if (angulo > 0) {
    grz = 0;
    while(lendoMpuGyro() <= angulo) {
      //MostrarLCD(CIMA, 0, "ANGULO: " + String(lendoMpuGyro()));
      mover(forca_curva * -1, forca_curva);
    }
  }
  if (angulo < 0) {
    grz = 0;
    while(lendoMpuGyro() >= angulo) {
      //MostrarLCD(CIMA, 0, "ANGULO: " + String(lendoMpuGyro()));
      mover(forca_curva, forca_curva * -1);
    }
    
  }
  //MostrarLCD(CIMA, 0, "                ");
  //MostrarLCD(BAIXO, 0, "                ");
  pararMotores();
}

void AjeitarNaParede() {
  pararMotores();
  delay(300);
  while(lerSharp(3) < 7) {
    mover(forca * -1, forca * -1);
  }
  mover(forca * -1, forca * -1);
  delay(600);
  pararMotores();
}

void Frente() {

    pararMotores();
    mover(forca_Baixa, forca_Baixa);
    delay(tempoandar);

    
  if(lerSharp(1) < 30) {
     while(lerSharp(1) <= 13) {
      mover(forca * -1, forca * -1);
    }
    while(lerSharp(1) >= 13) {
      mover(forca, forca);
    }
  }
  
  pararMotores();
 
}

void Direita() {
  CurvaGyro(-85, forca);
  AjeitarNaParede();
  Frente();
}
void Esquerda() {
  CurvaGyro(85, forca);
  AjeitarNaParede();
  Frente();
}



void droparVitima(int ladodrop) {
  if (ladodrop == 1) {
    myservo2.write(120);
    delay(1300);
    myservo2.write(20);
  }
}

void alertasVitima() {
  Buzzer.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  LED4.turnOn();
  delay(300);
  Buzzer.turnOff();
  LED2.turnOff();
  LED3.turnOff();
  LED4.turnOff();
  delay(600);
  Buzzer.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  LED4.turnOn();
  delay(300);
  Buzzer.turnOff();
  LED2.turnOff();
  LED3.turnOff();
  LED4.turnOff();
}

void Vitima(int ladodavitima) {
  if (ladodavitima == 1) { // Frente
    delay(1500);
    while(lerSharp(1) > 10) {
      mover(forca, forca);
    }
    delay(500);
    pararMotores();
    delay(600);
    while(lerSharp(1) < 12) {
      mover(forca_Baixa * -1, forca_Baixa * -1);
    }
    pararMotores();
    delay(600);
    alertasVitima();
    droparVitima(1);
    
  }
  if (ladodavitima == 2) { // Direita
    
  }
   if (ladodavitima == 3) { // Tras
    
  }
   if (ladodavitima == 4) { // Esquerda
    
  }
}

// o algoritmo vai pegar a coordenada atual, analisar os vizinhos e RETORNAR uma ação ao robô
void Algoritmo() {

   checarBateria();

   delay(1000);
   
   numero++;
   int nunca = 0;
   
   xatual = (coordenadaatual.substring(0,2)).toInt();
   yatual = (coordenadaatual.substring(2,4)).toInt();
   
   Historico[numero] = coordenadaatual.toInt();
   
   MostrarLCD(CIMA, 0, "X: " + String(xatual));
   MostrarLCD(BAIXO, 0, "Y: " + String(yatual));
  
  
  // Checagem primeiro do black space
  if (verificarBlackSpace() == true) {
    int BlackSpace[] = {coordenadaatual.toInt()};
    
    //voltarPara(Historico[numero - 1]);
     for(int t; t < 2; t++) {
            Buzzer.turnOn();
            delay(100);
            Buzzer.turnOff();
            delay(500);
      }
  } else {

    // se for vitima, ela dropa vitima
    if(verificarVitima() > 0) {
      Vitima(verificarVitima());
    }

    
    if (verificarEncruzilhada() == true) {

      // VerificarEncruzilhadas

        // se tiver mais que um caminho
       
    } else {

       // se nao for encruzilhada

      if(sistemaFechado() == true) {

         // VoltarUltimaEncruzilhada();

         // se tiver 3 paredes ao redor e o outro ja foi visitado

         // se tiver duas paredes e os quadrados em volta ja foram visitados
         

      } else {
        
          // se nao estiver num sistema fechado
          if (norte == 1) {
            // verifica se tem parede, se ja passou e se nao tem black space
            if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarHistorico(xatual, yatual + 1) ==  false) {
              Frente();
              norte = 1; leste = 0; sul = 0; oeste = 0; 
            }
            else if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarHistorico(xatual + 1, yatual) ==  false) {
              Direita();
              norte = 0; leste = 1; sul = 0; oeste = 0;
            }
            else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarHistorico(xatual - 1, yatual) ==  false) {
              Esquerda();
              norte = 0; leste = 0; sul = 0; oeste = 1;
            }
            
          }


          else if (leste == 1) {
            // verifica se tem parede, se ja passou e se nao tem black space
            if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarHistorico(xatual, yatual + 1) ==  false) {
              Frente();
              norte = 0; leste = 1; sul = 0; oeste = 0;
            }
            else if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarHistorico(xatual + 1, yatual) ==  false) {
              Direita();
              norte = 0; leste = 0; sul = 1; oeste = 0;
            }
            else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarHistorico(xatual - 1, yatual) ==  false) {
              Esquerda();
              norte = 1; leste = 0; sul = 0; oeste = 0;
            }
            
          }

          else if (oeste == 1) {
            // verifica se tem parede, se ja passou e se nao tem black space
            if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarHistorico(xatual, yatual + 1) ==  false) {
              Frente();
              norte = 0; leste = 0; sul = 0; oeste = 1;
            }
            else if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarHistorico(xatual + 1, yatual) ==  false) {
              Direita();
              norte = 1; leste = 0; sul = 0; oeste = 0;
            }
            else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarHistorico(xatual - 1, yatual) ==  false) {
              Esquerda();
              norte = 0; leste = 0; sul = 1; oeste = 0;
            }
            
          }
          else if (sul == 1) {
            // verifica se tem parede, se ja passou e se nao tem black space
            if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarHistorico(xatual, yatual + 1) ==  false) {
              Frente();
              norte = 0; leste = 0; sul = 1; oeste = 0;
            }
            else if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarHistorico(xatual + 1, yatual) ==  false) {
              Direita();
              norte = 0; leste = 0; sul = 0; oeste = 1;
            }
            else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarHistorico(xatual - 1, yatual) ==  false) {
              Esquerda();
              norte = 0; leste = 1; sul = 0; oeste = 0;
            }
            
          }

 
      } // termina verifacao do sistema fechado

      
    } // termina verificacao encruzilhada
    
  } // termina a verificacao Black Space

  coordenadaatual = "";

  
  // atualizar coordenadas
   if (norte == 1) {
    coordenadaatual += xatual;
    coordenadaatual += yatual + 1;
   }
   else if (leste == 1) {
    coordenadaatual += xatual + 1;
    coordenadaatual += yatual;
   }
   else if (sul == 1) {
    coordenadaatual += xatual;
    coordenadaatual += yatual - 1;
   }
   else if (oeste == 1) {
    coordenadaatual += xatual - 1;
    coordenadaatual += yatual;
   } 

    
  /*
    // tomada de acao
        if (checarencruzilhada) // nao se esquecer de contar as coordenadas visitadas
            // salva no array
            if(y+1 == ja foi visitado or y+7)
            // return false
            
            if(x+1 == ja foi visitado)
            // return false
            
            if (x-1 == ja foi visitado)
            // return false
            
            // qual retornar true, ele segue por esse
        
        // se nao for encruzilhada
            if (y+1 == disponivel OR BlackSpace == false)
                // vai para frente
            elseif (x+1 == disponivel OR BlackSpace == false)
                // vai para direita
            elseif(x-1 == disponivel OR BlackSpace == false)
                // vai para esquerda
            else
                // volta para a ultima encruzilhada
        
        
    */
    // salva 
    // salvar os bytes
    // funcao que analisa esse byte e da uma ação ao robo

  
  
}


/*
int lastError = 0;

int PID (double kP, double kI, double kD, double tP, int media) {

      int erro = lerTodosQTR() - media;

      //int error = map(media, 0, 7000, -100, 100);

      int nova_media = 0;

      //int desaceleracao = map((error - nova_media), -100, 100, 1, 0);
      
      int P = kP * erro;
      int I = I + (erro * kI);
      int D = kD * (erro - lastError);
      
      int ganho = P+I+D;
      
      lastError = erro;
      
      double motorB = tP + ganho;
      double motorC = tP - ganho;

      mover(motorB, motorC);

      //Serial.println(analogRead(A15));

};
*/
