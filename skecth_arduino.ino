#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinLed = 8;
const int pinSuono = 7;
int intensitaSuono = 300;
int velocita = 50;
char c = "";
String parola = "";

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
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
}
  

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

