#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);  
int ThermistorPin = A0;
int Vo;
float R1 = 10000;             
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
display.clearDisplay();
display.display();
Serial.begin(9600);
}

void loop() {

  Vo = analogRead(ThermistorPin);                     
  R2 = R1 * (1023.0 / (float)Vo - 1.0);               
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); 
  Tc = (273.15 - T)*(-1) ;

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print(Tc,2);                                
  display.print(" 'C");
  display.display();
  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C"); 
  display.clearDisplay();  

  delay(1000);
}
