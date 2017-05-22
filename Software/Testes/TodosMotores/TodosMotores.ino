int direitafrente = 3;
int esquerdafrente = 5;

int trasfrente = 6;
int trasdireitafrente = 9;

int esquerdatras = 2;
int direitatras = 4;

int trastras = 7;
int trasdireitatras = 8;


int forca = 150;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);  
  pinMode(9, OUTPUT);

}

void loop() {
analogWrite(direitafrente, forca);
 analogWrite(esquerdafrente, forca);
  analogWrite(trasfrente, forca);
  analogWrite(trasdireitafrente, forca);
  analogWrite(esquerdatras, 0);
  analogWrite(direitatras, 0);
  analogWrite(trastras, 0);
  analogWrite(trasdireitatras, 0);*/
  delay(4000);

  analogWrite(esquerdatras, forca);
  analogWrite(direitatras, forca);
  analogWrite(trastras, forca);
  analogWrite(trasdireitatras, forca);
   analogWrite(direitafrente, 0);
  analogWrite(esquerdafrente, 0);
  analogWrite(trasfrente, 0);
  analogWrite(trasdireitafrente, 0);
  delay(4000);
  // put your main code here, to run repeatedly:

}
