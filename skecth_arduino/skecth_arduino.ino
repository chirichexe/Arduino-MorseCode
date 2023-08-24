#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinBottone = 8;
int pinBottoneInvia = 4;
const int pinLed = 7;
const int pinSuono = 6;
int intensitaSuono = 300;
int velocita = 50;
char c = "";
String parola = "";

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBottone, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

}

void loop() {
  
  char res[] = "";
  int t = contaTempo();
  if (t <= 250 ){
    strcat(res, "0");
  }
  else if(t > 250){
    strcat(res, "1");
  }
  else strcat(res, " ");
  
  Serial.println(res);
  
  
  /*
  if (Serial.available()){
    c = Serial.read();
    decodifica(c);
    if(c!='0' && c!='1' && c!=' '){
      parola+= c;
    }
    if(c =='\n'){
      lcd.clear();
      lcd.print("La parola era:");
      lcd.setCursor(0, 1);
      for(int i = 0; i<parola.length()-1;i++){
       lcd.print(parola.charAt(i));
      } 
     
    }
  }
  */
}

//SEZIONE CODIFICA


String codifica(){
  char res[] = "";
  int t = contaTempo();
  if (t <= 250 ){
    strcat(res, "0");
  }
  else if(t > 250){
    strcat(res, "1");
  }
  else strcat(res, " ");
  return res;
}

  int press = 0;
  int timePress = 0;
  int time = 0;
  int conteggio = 0;
int contaTempo(){
  press = digitalRead(pinBottone);
    if ((press==1) && (conteggio == 0)){
      conteggio = 1;
      timePress = millis();
    }

    if ((conteggio == 1) && (press==0)){
      conteggio = 0;
      time = millis()- timePress;
      return time;
    }
  }

//SEZIONE DECODIFICA

void decodifica(char c){
  if (c == '0') {
    corto();
  } else if (c == '1') {
    lungo();
  } else if (c == '/') {
    pausaParole();
  } else if (c == ' ') {
    pausaCaratteri();
  } else {
    fineParola();
  }
}

void lungo(){
  tone(pinSuono, intensitaSuono);
  digitalWrite(pinLed, HIGH);
  delay(velocita*3);
  digitalWrite(pinLed, LOW);
  noTone(pinSuono);
  delay(velocita/2);
}

void corto(){
  digitalWrite(pinLed, HIGH);
  tone(pinSuono, intensitaSuono);
  delay(velocita);
  digitalWrite(pinLed, LOW);
  noTone(pinSuono);
  delay(velocita/2);
}

void pausaCaratteri(){
  delay(velocita);
}

void pausaParole(){
  delay(velocita*2);
}

void fineParola(){
  noTone(pinSuono);
  pinMode(pinLed, LOW);
}

