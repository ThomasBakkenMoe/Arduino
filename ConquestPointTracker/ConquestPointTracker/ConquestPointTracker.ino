#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pointCap = 250;

int team1Points = 0;
int team2Points = 0;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //size of the lcd (x, y)
  
  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball!");

  lcd.setCursor(5,1);
  lcd.print("123");

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
