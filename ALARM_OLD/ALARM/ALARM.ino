#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0X27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define RELAY_PIN 13

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// INITIALISE LIBRARY WITH VARIABLES

int btnOne = 2;
int btnTwo = 3;
int sensePin = 4;
int ledG = 12;
int speaker = A1;
boolean systemAct;
boolean toneOn;

void setup() {
  
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home
  
  lcd.begin (16, 2); //  <<----- My LCD was 16x2
  lcd.setCursor(1, 0); // SETTING CURSOR
  startUp();
  lcd.print("SYSTEM STATUS:"); // PRINTING INITIALISE TEXT
  deactivate(); // CALLING THE DEACTIVATE FUNCTION
  pinMode(btnOne, INPUT); // SETTING PINMODES
  pinMode(btnTwo, INPUT);
  pinMode(sensePin, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(ledG, OUTPUT);
  systemAct = false;  // SETTING DEFAULT SYSTEM STAT
  toneOn = false;
  
}

void loop() {
    
  // LISTENING FOR REMOTE INPUT
  if (digitalRead(btnOne) == HIGH) {
     
    if (systemAct != true) {
      systemAct = true;
      activate(); // CALLING THE ACTIVATE FUNCTION
    }

  } else if (digitalRead(btnTwo) == HIGH) {
    
     if (systemAct != false) {
      systemAct = false;
      deactivate(); // CALLING THE DEACTIVATE FUNCTION
    }
     
  }
}

void startUp () {
 
 lcd.print("INITIALISING");
  
 int i = 0;
 int x1 = 16;
 
 lcd.setCursor(0, 1);
 
 while (i < x1) {
  
  lcd.print("|");
  i++;
  delay(100);
   
 }
 
 delay(1000);
 lcd.clear();
 
 lcd.setCursor(0, 0);
 lcd.print("PROGRAMMED BY:");
 lcd.setCursor(0, 1);
 lcd.print("CONNOR EDWARDS");
 
 tonePlay(1);

 delay(1000);
 lcd.clear();
  
}

void activate() {
  
  statusUpdate(1); // UPDATING THE DISPLAY RESPECTIVELEY
  digitalWrite(ledG, HIGH);
  
  while (systemAct) {
    
     if (digitalRead(sensePin) == HIGH) {
      
      digitalWrite(ledG, LOW);
      digitalWrite(RELAY_PIN, LOW);
      
      lcd.println("                ");
      lcd.setCursor(0, 1);
      lcd.print("ALARM TRIGGERED");
      
      if (digitalRead(btnTwo) == HIGH) {
         systemAct = false;
         deactivate();
         break;
      }
      
     } else if (digitalRead(btnTwo) == HIGH) {
         systemAct = false;
         deactivate();
         break;
     }
  
  }
  
}

void deactivate() {
  
  digitalWrite(ledG, LOW);
  digitalWrite(RELAY_PIN, HIGH);
  statusUpdate(0); // UPDATING THE DISPLAY RESPECTIVELEY
  
}

void statusUpdate(int sel) {
  
  if (sel == 1) {
    
    lcd.setCursor(0, 1);
    lcd.println("                ");
    lcd.setCursor(0, 1);
    lcd.print("ACTIVE");
    tonePlay(1);
    
  } else {
    
    lcd.setCursor(0, 1);
    lcd.println("                ");
    lcd.setCursor(0, 1);
    lcd.print("DEACTIVATED");
    tonePlay(2);
    
  }
  
}

void tonePlay(int toneSel) {
 
  if (toneSel == 1) {
  
   tone(speaker, 440, 100);
   delay(250);
   tone(speaker, 440, 100);
   delay(125);
   tone(speaker, 880, 100);
   
  } else {
    
    tone(speaker, 880, 100);
    delay(250);
    tone(speaker, 880, 100);
    delay(125);
    tone(speaker, 440, 100);
    
  }
  
}


