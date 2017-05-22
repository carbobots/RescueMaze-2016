#include <Arduino.h>

/*
  FUNÇÕES de Controles DO ROBÔ
*/

void rodar(bool condicao) {
  if (condicao == true) {

    checarBateria();  

    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");

    norte = 1;
   
    String coordenadainicial;
    coordenadainicial += xinicial;
    coordenadainicial += yinicial;

    coordenadaatual = coordenadainicial;

    // Executa o algoritmo até todo o labirinto for completo
    int nunca = 0;
   while(nunca < 2) {
      Algoritmo(); 
   }
   /* int nunca = 0;    
    while(nunca < 1) {
    MostrarLCD(CIMA, 0, "F:" + String(lerSharp(1)) + "  T:" + String(lerSharp(3)));
    MostrarLCD(BAIXO, 0, "D:" + String(lerSharp(2)) + "  E:" + String(lerSharp(4)));
    delay(250);
    }*/
    
  }
}




/**** CALIBRAR OS VALORES DOS QTR ***/
void calibrar(bool condicao) {
  if (condicao == true) {
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");
    
    delay(500);
      
      // enquanto nao aberta o botao para sair ou salvar, ele fica exibindo a mensagem
      while(Botao3.readValue() == LOW && Botao4.readValue() == LOW) {
          MostrarLCD(CIMA, 0, "QTR: " + String(lerQTR(1)) +  " Preto");
          MostrarLCD(BAIXO, 0, "Aperte p salvar");
      }
       if (Botao3.readValue() == HIGH) {
        blackspace_value = lerQTR(1) + 50; // se o botao 3 for apertado, salva o valor da variavel
      }

      delay(300);
      
      // enquanto nao aberta o botao para sair ou salvar, ele fica exibindo a mensagem
      while(Botao3.readValue() == LOW && Botao4.readValue() == LOW) {
          MostrarLCD(CIMA, 0, "QTR: " + String(lerQTR(1)) +  " Chckpt");
          MostrarLCD(BAIXO, 0, "Aperte p salvar");
      }
       if (Botao3.readValue() == HIGH) {
        checkpoint_value = lerQTR(1) - 50; // se o botao 3 for apertado, salva o valor da variavel
      }
      
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");

    delay(500);


      
  }
}


/*************** VER VALORES ******************/
void valores(bool condition) {
  if(condition == true) {
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");
    delay(300);
    while(Botao4.readValue() != HIGH){
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
      delay(100);
    }
    delay(300);
    while(Botao4.readValue() != HIGH){
      MostrarLCD(CIMA, 0, "                ");
      MostrarLCD(BAIXO, 0, "                ");
      MostrarLCD(CIMA, 0, checarBytesQuadrado());
      delay(100);
    }
    delay(300);
    
    MostrarLCD(CIMA, 0, "                ");
    MostrarLCD(BAIXO, 0, "                ");

    
  }
}

