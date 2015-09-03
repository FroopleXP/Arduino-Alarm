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
  
}

void loop() {
  
  // Listening for key turn
  if (digitalRead(key) == HIGH) {
    alarm_stat = true;
  } else {
    alarm_stat = false;
  }
  
  // Listening for door open
  if ((digitalRead(reed_1) && digitalRead(reed_2)) == HIGH) {
    door_open = false;
  } else {
    door_open = true; 
  }
  
  // Checking if the door is open and the alarm is active
  if ((alarm_stat && door_open) == true) {
    sound_alarm();
  } 
  
}

// Function used to sound the alarm and listen for key
void sound_alarm() {
  
 while (alarm_stat == true) {
   if (digitalRead(key) == LOW) {
     turn_off_alarm();
     alarm_stat = false;
   } else {
     turn_on_alarm();
     alarm_stat = true; 
   }
 }
 
 return;
  
}

// Actually sounds the alarm
void turn_off_alarm() {
  digitalWrite(led, LOW);
  return;
}

// Turns off the alarm
void turn_on_alarm() {
  digitalWrite(led, HIGH);
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

void update_disp(char msg[15]) {
  lcd_dis.clear();
  lcd_dis.print(msg);
}
