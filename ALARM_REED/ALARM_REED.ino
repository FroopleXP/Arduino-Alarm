//////////////////////////////////////
//                                  //
//    ALARM FIRMWARE                //
//    WRITTEN BY: CONNOR EDWARDS    //
//    DATE: 3/9/15                  //
//                                  //
//////////////////////////////////////

// Including the libraies for LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialising the I2C for LCD
LiquidCrystal_I2C lcd_dis(0x27, 16, 2);

// Setting pins for reed switches and LED's
int led = 13;
int reed_1= 8;
int reed_2 = 9;
int key = 10;

// Status indicators for reed switches and LED's
int reed_1_stat;
int reed_2_stat;
int key_stat;

// Booleans for the alarm status and door open status
boolean alarm_stat;
boolean door_open;

void setup() {
  
  lcd_dis.init();
  
  pinMode(led, OUTPUT);
  pinMode(key, INPUT);
  pinMode(reed_1, INPUT);
  pinMode(reed_2, INPUT);
  
  alarm_stat = false;
  door_open = false;
  
  lcd_dis.backlight();
  
  welcome_message();
  init_check();
  
}

void loop() {
  
  // Listening for key turn
  if (digitalRead(key) == HIGH) {
    
    if (alarm_stat != true) {
      alarm_stat = true;
      activate();
    }
    
  } else if (digitalRead(key) == LOW) {
    
    if (alarm_stat != false) {
      alarm_stat = false;
      deactivate();
    }
    
  }
  
}

// Activates the alarm
void activate() {
  
  update_disp(1); 
  
  while (alarm_stat) {
      
    if ((digitalRead(reed_1) && digitalRead(reed_2)) == LOW) {
      
      digitalWrite(led, HIGH);
      
      lcd_dis.println("                ");
      lcd_dis.setCursor(0, 1);
      lcd_dis.print("ALARM TRIGGERED");
      
      if (digitalRead(key) == LOW) {
        alarm_stat = false;
        deactivate();
        break;
      }
      
    } else if (digitalRead(key) == LOW) {
      alarm_stat = false;
      deactivate();
      break;
    }
    
  }
  
  return;
  
}

void deactivate() {
  
  digitalWrite(led, LOW);
  update_disp(0); 
  
  return;
  
}

// Function for welcoming the User
void welcome_message() {
  
  lcd_dis.setCursor(2, 0);
  lcd_dis.print("ALARM SYSTEM");
  lcd_dis.setCursor(0, 1);
  lcd_dis.print("Booting...");
  lcd_dis.setCursor(0, 0);
  delay(2000);
  lcd_dis.clear();
  lcd_dis.print("Firmware V.1.0");
  lcd_dis.setCursor(0, 0);
  delay(2000);
  lcd_dis.clear();
  lcd_dis.print("Written By:");
  lcd_dis.setCursor(0, 1);
  lcd_dis.print("Connor Edwards");
  lcd_dis.setCursor(0, 0);
  delay(3000);
  lcd_dis.clear();
  lcd_dis.print("Ready!");
  lcd_dis.setCursor(0, 0);
  delay(1000);
  lcd_dis.clear();
 
  lcd_dis.print("ALARM STATUS: ");
  lcd_dis.setCursor(0, 1);
  
  return;
  
}

void update_disp(int sel) {
  
  if (sel == 1) {
    
    lcd_dis.setCursor(0, 1);
    lcd_dis.println("                ");
    lcd_dis.setCursor(0, 1);
    lcd_dis.print("ACTIVE");
    
  } else {
    
    lcd_dis.setCursor(0, 1);
    lcd_dis.println("                ");
    lcd_dis.setCursor(0, 1);
    lcd_dis.print("DEACTIVATED");
    
  }
  
  return;
  
}

void init_check() {
 if (digitalRead(key) == HIGH) {
   activate();
 } else {
   deactivate(); 
 }
}
