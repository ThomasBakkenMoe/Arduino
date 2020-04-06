#include <LiquidCrystal.h>
#include <pt.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

static struct pt pt1;

int pointCap = 250; // How many points it takes to win

int team1Points = 0;
int team2Points = 0;

int tickRate = 100; // How quickly the selected team aquires points

short selectedTeam = 0; // 1 = team 1, 2 = team 2

static int protothreadPointCounter

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //size of the lcd (x, y)

  lcd.print("Team 1");
  lcd.setCursor(0, 1);
  lcd.print("Team 2");
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
