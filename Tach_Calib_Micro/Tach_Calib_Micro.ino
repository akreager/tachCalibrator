/*
  This project is to set an Arduino Micro up to calibrate an automotive air coil
  type tachometer.
  
  Circuit:
  Digital pin 13 PWM Output, connected to N-Channel Mosfet Gate.
  Mosfet Drain connected to load; solenoid coil.
  Mosfet Source connected to ground.
  Analog input A5 connected to potentiometer wiper.
  
*/

//Library for serial LCD
#include <LiquidCrystal.h>

//Initialize the lcd library with the numbers of the interface pins
//LCD pin name	 [RS EN DB4 DB5 DB6 DB7]
//Arduino pin #	 [12  11  10  9  8  7]
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

//define pins used and variables
int backlight = 6;     //PWM Pin connected to LCD backlight
int brightness = 255;  //LCD brightness value 0->255, off->full bright
int cyl=8;             // Number of cylinders in engine.
unsigned int freq=0;   // Variable to hold frequency for tone()
int val=0;             // Variable to hold value of potentiometer.
unsigned int RPM=0;    // Variable to hold value of simulated engine speed.
int signal=13;         // Signal output on Digital pin 13.
int dimmer=A5;         // Potentiometer inpupt on Analog pin 5.

void setup()
{
  //turn the backlight on
  pinMode(backlight, OUTPUT);
  analogWrite(backlight, brightness);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //set pin mode for tachometer output and potentiometer input
  pinMode(signal, OUTPUT);
  pinMode(dimmer, INPUT);
}

void loop()
{
  val=analogRead(dimmer);
  RPM=map(val,1023,0,0,8184);
  freq=(RPM*cyl)/120;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(RPM);
  lcd.print(" RPM");
  lcd.setCursor(0, 1);
  lcd.print(freq);
  lcd.print("Hz");
  tone(signal, freq);
  delay(500);
}

