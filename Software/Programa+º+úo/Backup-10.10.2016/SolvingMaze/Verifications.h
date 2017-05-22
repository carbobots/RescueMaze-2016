#include <Arduino.h>

/*
  FUNÇÕES DE VERIFICAÇÃO DO ROBÔ
*/

void checarBateria() {

  if(myCustomVoltimeter.readVoltage() < VOLTAGE_LOW && myCustomVoltimeter.readVoltage() > 6) {
    int t = 0;
    while(myCustomVoltimeter.readVoltage() < VOLTAGE_LOW && myCustomVoltimeter.readVoltage() > 6){
      MostrarLCD(CIMA, 0, "Bateria acabando");
      MostrarLCD(BAIXO, 0, "Nivel: " + String(myCustomVoltimeter.readVoltage()) + "V");
      Buzzer.turnOn();
      LED1.turnOn();
      LED2.turnOn();
      LED3.turnOn();
      LED4.turnOn();
      lcd.setBacklight(HIGH);
      delay(500);
      Buzzer.turnOff();
      LED1.turnOff();
      LED2.turnOff();
      LED3.turnOff();
      LED4.turnOff();
      delay(300);
      Serial.println(myCustomVoltimeter.readVoltage());
    }
    
    
  }

  
}

String verificarCoord () {
  if(norte == 1) {
    return "N";
  }
  else if(sul == 1) {
    return "S";
  }
  else if(leste == 1) {
    return "L";
  }
  else if(oeste == 1) {
    return "O";
  }
}

bool verificarParede(int numero_parede) {
  // 1 Frente, 2 Direita, 3 Tras, 4 Esquerda
  if (lerSharp(numero_parede) <= distancia_parede) {
      return true;
    } else {
      return false;
    }

    
}

bool verificarBlackSpace() {
 if (blackspace_value != 0) { // se ja tiver calibrado
      if(lerQTR(1) <= blackspace_value) {
        return true;
      } else{
        return false;
      }
    } else {
      if(lerQTR(1) <= blackspace_default && lerQTR(1) != 0) {
        return true;
      } else {
        return false;
      }
    }
}


bool proximoBlackSpace(int numerodoquadrado) {
  return false;
}


int verificarVitima() {
   if(lerTemp(1, OBJ) > TEMP_MINIMA && lerTemp(1, OBJ) < TEMP_MAXIMA) {
      return 1;
    }
    else if(lerTemp(2, OBJ) > TEMP_MINIMA && lerTemp(2, OBJ) < TEMP_MAXIMA) {
      return 2;
    }
    else if(lerTemp(3, OBJ) > TEMP_MINIMA && lerTemp(3, OBJ) < TEMP_MAXIMA) {
      return 3;
    }
    else if(lerTemp(4, OBJ) > TEMP_MINIMA && lerTemp(4, OBJ) < TEMP_MAXIMA) {
      return 4;
    }
    else {
      return 0;
    }
};

bool verificarCordBlackSpace( int xblack, int yblack) {
 /* int j;
  String coordenadaaverificar;
  coordenadaaverificar += xblack;
  coordenadaaverificar += yblack;
  
  for(j = 0; j < sizeof(BlackSpace); j++) {

    if(BlackSpace[j] == coordenadaaverificar.toInt()) {
      return true;
    }
    
  }*/
  return false;
}
bool verificarHistorico(int xhistorico, int yhistorico) {
  /*int l;
  String coordenadaaverificar;
  coordenadaaverificar += xhistorico;
  coordenadaaverificar += yhistorico;
  
  for(l = 0; l < sizeof(Historico); l++) {

    if(Historico[l] == coordenadaaverificar.toInt()) {
      return true;
    }
    
  }*/
  return false;
}
bool verificarEncruzilhada() {

  return false;
}

bool verificarRampa(int angulacao) {

  if(angulacao == SUBIDA) {
    if(lendoMpuAccel() < angulo_rampa_subida) { // subida
      return true;
    } else {
      return false;
    }
  }
  if(angulacao == DESCIDA) {
    if(lendoMpuAccel() > angulo_rampa_descida) { // descida
      return true;
    } else {
      return false;
    }
  }
}

int verificarNumeroParedes() {
  int numeroparedes;
  numeroparedes = 0;
    if (lerSharp(1) <= distancia_parede) {
      numeroparedes ++;
    }
    if (lerSharp(2) <= distancia_parede) {
      numeroparedes ++;
    }
    if (lerSharp(3) <= distancia_parede) {
      numeroparedes ++;
    }
    if (lerSharp(4) <= distancia_parede) {
       numeroparedes ++;
    }
  
  return numeroparedes;
}


bool sistemaFechado() {

  if(verificarNumeroParedes() >= 3) {
  return true;
  } else {

    return false;
  }
}

int verificarVizinhos(int xvizinho, int yvizinho) {
    int numerovizinhos;
    if(verificarHistorico(xvizinho + 1, yvizinho) == true) {
      numerovizinhos + 1;
    }
    if(verificarHistorico(xvizinho - 1, yvizinho) == true) {
      numerovizinhos + 1;
    }
    if(verificarHistorico(xvizinho, yvizinho + 1) == true) {
      numerovizinhos + 1;
    }
    if(verificarHistorico(xvizinho, yvizinho - 1) == true) {
      numerovizinhos + 1;
    }
  return numerovizinhos;
}









String checarBytesQuadrado() {
    
    /*** PAREDE ***/
    int a = 0; // Frente
    int b = 0; // Direito
    int c = 0; // Tras
    int d = 0; // Esquerda

    /*** Quadrado ***/
    int e = 0; // Check point
    int f = 0; // Black Space

    /*** Vitima ****/
    int g = 0; // Frente
    int h = 0; // Direito
    int i = 0; // Tras
    int j = 0;  // Esquerdo
    
    /*** Rampa ***/
    int k = 0; // Rampa
    
    if (lerSharp(1) <= distancia_parede) {
      a = 1;
    }
    if (lerSharp(2) <= distancia_parede) {
      b = 1;
    }
    if (lerSharp(3) <= distancia_parede) {
      c = 1;
    }
    if (lerSharp(4) <= distancia_parede) {
       d = 1;
    }
    if (checkpoint_value != 0) { // se ja tiver calibrado
      if(lerQTR(1) >= checkpoint_value) {
        e = 1;
      }
    } else {
      if(lerQTR(1) >= checkpoint_default) {
        e = 1;
      }
    }
    if (blackspace_value != 0) { // se ja tiver calibrado
      if(lerQTR(1) <= blackspace_value) {
        f = 1;
      }
    } else {
      if(lerQTR(1) <= blackspace_default) {
        f = 1;
      }
    }
    if(lerTemp(1, OBJ) > 28 && lerTemp(1, OBJ) < 40) {
      g = 1;
    }
    if(lerTemp(2, OBJ) > 28 && lerTemp(2, OBJ) < 40) {
      h = 1;
    }
    if(lerTemp(3, OBJ) > 28 && lerTemp(3, OBJ) < 40) {
      i = 1;
    }
    if(lerTemp(4, OBJ) > 28 && lerTemp(4, OBJ) < 40) {
      j = 1;
    }
    if(lendoMpuAccel() < -30 || lendoMpuAccel() > 22) {
      k = 1;
    }
      String result;
      result += a;
      result += b;
      result += c;
      result += d;
      result += e;
      result += f;
      result += g;
      result += h;
      result += i;
      result += j;
      result += k;
      
      return result;
      
}


