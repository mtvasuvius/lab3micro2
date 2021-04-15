#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 clock;
RTCDateTime dt;
String motor_speed = "3/4";
int speed_of_motor = 192;
String motor_dir = "CC";
bool clockwise = true;

#define INTPIN 2
#define ENABLE 5
#define DIRA 3
#define DIRB 4

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {

  pinMode(INTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTPIN), changeMotorDirection, FALLING);
  
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("DIR: "); lcd.print(motor_dir); lcd.print(" S: "); lcd.print(motor_speed);

  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);

  analogWrite(ENABLE,speed_of_motor);
  digitalWrite(DIRA,LOW); 
  digitalWrite(DIRB,HIGH);
  
}

void loop() {
  
  dt = clock.getDateTime();
  
  lcd.setCursor(0, 0);
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second); 

  delay(995);
  
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("DIR: "); lcd.print(motor_dir); lcd.print(" S: "); lcd.print(motor_speed);
  
}

void changeMotorDirection() {

  if(clockwise){
    clockwise = false;
    motor_dir = "CCW";
    digitalWrite(DIRA,HIGH); 
    digitalWrite(DIRB,LOW);
  }
  else{
    clockwise = true;
    motor_dir = "CC";
    digitalWrite(DIRA,LOW); 
    digitalWrite(DIRB,HIGH);   
  }
  
}
