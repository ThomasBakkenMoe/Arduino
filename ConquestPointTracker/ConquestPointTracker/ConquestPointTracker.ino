#include <LiquidCrystal.h>
#include <pt.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

static struct pt pt1, pt2, pt3; // Three treads to be distributed by the main loop

int pointCap = 250; // How many points it takes to win

int team1Points = 0;
int team2Points = 0;

int tickRate = 1000; // How quickly (ms) the selected team aquires points

int blinkArrowRate = 250; // How quickly (ms) the selected team's arrow blinks

short selectedTeam = 0; // The team that is currently reciving points. 1 = team 1, 2 = team 2 

int switch1Pin = 10;
int switch2Pin = 9;
int switchState = 0;

static int protothreadButtonHandler(struct pt *pt){
  static unsigned long lastTimeCheck = 0;

  PT_BEGIN(pt);
  while(true){
    lastTimeCheck = millis();
    PT_WAIT_UNTIL(pt, digitalRead(switch1Pin) == HIGH);
    selectedTeam = 1;
    PT_WAIT_UNTIL(pt, digitalRead(switch2Pin) == HIGH);
    selectedTeam = 2;
  }
  PT_END(pt);
}


static int protothreadArrowHandler(struct pt *pt){
  
  static unsigned long lastTimeBlink = 0;
  static short blinkPosition = 0;
  
  PT_BEGIN(pt);
  while(true){
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > blinkArrowRate);
    switch(blinkPosition){
      
      case 0:
      lcd.setCursor(9, 0);
      lcd.print(" ->");
      blinkPosition++;
      break;
      
      case 1:
      lcd.setCursor(9, 0);
      lcd.print("- >");
      blinkPosition++;
      break;
      
      case 2:
      lcd.setCursor(9, 0);
      lcd.print("-- ");
      blinkPosition = 0;
      break;
    }
  }
  PT_END(pt);
}

static int protothreadPointCounter(struct pt *pt){
  
  static unsigned long lastTimeTick = 0;
  
  PT_BEGIN(pt);
  while(true){
    lastTimeTick = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeTick > tickRate);
    
    if(selectedTeam == 1){
      team1Points++;
      lcd.setCursor(13, 0);
      lcd.print(team1Points);
    }else if(selectedTeam == 2){
      team2Points++;
      lcd.setCursor(13, 1);
      lcd.print(team2Points);
    }
  }
  PT_END(pt);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  
  lcd.begin(16, 2); //size of the lcd (x, y)

  lcd.print("Team 1");
  lcd.setCursor(0, 1);
  lcd.print("Team 2");
    
}

void loop() {
  // put your main code here, to run repeatedly:
  protothreadPointCounter(&pt1);
  protothreadArrowHandler(&pt2);
  protothreadButtonHandler(&pt3);
}
