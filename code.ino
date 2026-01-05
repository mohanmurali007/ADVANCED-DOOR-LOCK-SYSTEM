#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x3F,16,2);

const byte ROWS = 4;
const byte COLS = 4;

String pass = "1234";
String entered = "";
String changedpass="";

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int RED = 11;
int GREEN = 12;

bool closeDoor = true;
bool openDoor  = false;

int a=9;

bool wrong=0;
int wrongcount=0;
int chancesleft =3-wrongcount;
int buzz=10;
bool togg;

void setup() {
  lcd.init();
  lcd.backlight();
  myservo.attach(13);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(buzz,OUTPUT);
}

void loop() {

  digitalWrite(RED, closeDoor);
  digitalWrite(GREEN, openDoor);
  String msg = " Enter # or * or A    ";
  lcd.noBlink();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg);
  for(int i=0; i < msg.length(); i++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("key");
  lcd.setCursor(0, 1);
  lcd.print("Pressed: ");
  char key = keypad.getKey();
  while(!key)
  {
    key = keypad.getKey();
    lcd.setCursor(a,1);
    if(entered.length() < pass.length()-1)
    {
      lcd.blink();
    }
  }

  if(key=='#')
  {
    while(key!='D')
    {
      lcd.setCursor(0, 0);
      lcd.print("Enter password ");
      lcd.setCursor(0, 1);
      lcd.print("Pressed: ");

      key = keypad.getKey();

      if (key != 'A')
      {
        while(!key)
        {
          key = keypad.getKey();
          lcd.setCursor(a,1);
          if(entered.length() < pass.length()-1)
          {
            lcd.blink();
          }
        }
        if (key) 
        {
          if((key=='C'||key=='B') && a>=9)
          {
            if(key=='C')
            {
              entered="";
              a=9;
              lcd.clear();
            }
            if(key=='B'&& a>9)
            {
              entered.remove(entered.length()-1,1);
              a--;
              lcd.setCursor(a,1);
              lcd.print(" ");
              lcd.setCursor(a,1); 
            }
          }
          lcd.setCursor(0, 1);
          lcd.print("Pressed: ");
          if(key!='C' && key!='B' && key!='D' && key!='A')
          {
            lcd.setCursor(a,1);
            lcd.print(key);
            delay(300);
            lcd.setCursor(a,1);
            lcd.print("*");

            entered += key;
            delay(500);
            a++;
            lcd.noBlink();
          }
          if (entered.length() == pass.length()) 
          {

            a=9;
            if (entered == pass) {
              wrongcount=0;

              openDoor  = !openDoor;
              closeDoor = !closeDoor;

              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Correct Password!");
              delay(2000);

              if (closeDoor) {
                for(int i=180; i>=0; i--) {
                  myservo.write(i);
                  delay(20);
                }
                digitalWrite(RED, closeDoor);
                digitalWrite(GREEN, openDoor);
                for(int i=0; i<4; i++)
                {
                  lcd.clear();
                  delay(1000);
                  lcd.print("DOOR CLOSED");
                  delay(1000);
                }
              }
              if (openDoor) {
                for(int i=0; i<=180; i++) {
                  myservo.write(i);
                  delay(20);
                }
                digitalWrite(RED, closeDoor);
                digitalWrite(GREEN, openDoor);
                for(int i=0; i<4; i++)
                {
                  lcd.clear();
                  delay(1000);
                  lcd.print("DOOR OPENED");
                  delay(1000);
                }
              }

              lcd.clear();
            }
            else 
            {
              wrongcount++;
              chancesleft =3-wrongcount;
              lcd.clear();
              if(wrongcount!=3)
              {
                lcd.setCursor(0,0);
                lcd.print("Wrong Password");
                lcd.setCursor(0,0);
                lcd.print("Chances left: ");
                lcd.setCursor(15,0);
                lcd.print(chancesleft);
                lcd.setCursor(0,1);
                lcd.print("Try again");
                delay(3000);
              }
              if(wrongcount==3)
              {
                lcd.setCursor(0,0);
                lcd.print("Security Alert");
                lcd.setCursor(0,1);
                lcd.print("Try after:");
                lcd.setCursor(13,1);
                lcd.print("Sec");
                togg=1;
                for(int i=9;i>=0;i--)
                {
                  lcd.setCursor(11,1);
                  lcd.print(i);
                  delay(1000);
                  digitalWrite(buzz,togg);
                  togg=!togg;
                }

                wrongcount=0;
              }
              lcd.clear();
            }
            entered = "";
          }
        }
      }
    }
  }

  if(key=='*')
  {
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PROJECT OVERVIEW");
    delay(3000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("ADVANCED DOOR");
    lcd.setCursor(2,1);
    lcd.print("LOCK SYSTEM");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BY   SREENADH");
    lcd.setCursor(0,1);
    lcd.print("AND  MOHAN");
    delay(3000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("UNDER THE");
    lcd.setCursor(2,1);
    lcd.print("GUIDANCE OF");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dr. SRINIVAS");
    lcd.setCursor(4,1);
    lcd.print("BOPPU SIR");
    delay(3000);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("KEY PAD");
    lcd.setCursor(2,1);
    lcd.print("DESCRIPTION");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD");
    lcd.setCursor(0,1);
    lcd.print("ENTRIES   : 0-9");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A-MANUAL");
    lcd.setCursor(2,1);
    lcd.print("PASSWORD RESET");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("B-BACKSPACE");
    lcd.setCursor(0,1);
    lcd.print("C-CLEAR");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("D-BACK TO");
    lcd.setCursor(2,1);
    lcd.print("HOME SCREEN");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("#-ENTERING");
    lcd.setCursor(2,1);
    lcd.print("LOCK PASSWORD");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("*-KEY PAD");
    lcd.setCursor(2,1);
    lcd.print("DESCRIPTION");
    delay(3000);
    lcd.clear();
  }

  if((key!='*')&&(key!='#')&&(key!='D')&&(key!='A'))
  {
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("!!INCORRECT");
    lcd.setCursor(3,1);
    lcd.print("KEY WORD!!");
    delay(3000);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("PLEASE ENTER");
    lcd.setCursor(0,1);
    lcd.print("CORRECT KEY WORD");
    delay(3000);
    lcd.clear();
  }

  if(key=='D')
  {
    lcd.clear();
    a=9;
    entered="";
  }

  if(key=='A')
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Resetting your");
    lcd.setCursor(0,1);
    lcd.print("password...");
    delay(2000);
    entered="";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter old pass");
    lcd.setCursor(0, 1);
    lcd.print("Pressed: ");
    a=9;
    key = keypad.getKey();
    while(entered.length() != 4)
    {
      key = keypad.getKey();
      while(!key)
      {
        key = keypad.getKey();
        lcd.setCursor(a,1);
        if(entered.length() < pass.length()-1)
        {
          lcd.blink();
        }   
      }
      if (key) 
      {
        if((key=='C'||key=='B'|| key=='D') && a>=9)
        {
          if(key=='C')
          {
            entered="";
            a=9;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter old pass");
            lcd.setCursor(0, 1);
            lcd.print("Pressed: ");
          }
          if(key=='B'&& a>9)
          {
            entered.remove(entered.length()-1,1);
            a--;
            lcd.setCursor(a,1);
            lcd.print(" ");
            lcd.setCursor(a,1); 
          }
          if(key=='D')
          {
            entered="";
            lcd.clear();
            a=9;
            break;
          }
        }
        lcd.setCursor(0, 1);
        lcd.print("Pressed: ");
        if(key!='C' && key!='B' && key!='A' && key!='D')
        {
          lcd.setCursor(a,1);
          lcd.print(key);
          delay(300);
          lcd.setCursor(a,1);
          lcd.print("*");
          entered += key;
          delay(500);
          a++;
          lcd.noBlink();
        }
      }
    }
    if(entered==pass)
    {
      entered="";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter new pass");
      lcd.setCursor(0, 1);
      lcd.print("Pressed: ");
      a=9;
      key = keypad.getKey();
      while(entered.length() != 4)
      {
        key = keypad.getKey();
        while(!key)
        {
          key = keypad.getKey();
          lcd.setCursor(a,1);
          if(entered.length() < pass.length()-1)
          {
            lcd.blink();
          }   
        }
        if (key) 
        {
          if((key=='C'||key=='B'|| key=='D') && a>=9)
          {
            if(key=='C')
            {
              entered="";
              a=9;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Enter new pass");
              lcd.setCursor(0, 1);
              lcd.print("Pressed: ");
            }
            if(key=='B'&& a>9)
            {
              entered.remove(entered.length()-1,1);
              a--;
              lcd.setCursor(a,1);
              lcd.print(" ");
              lcd.setCursor(a,1); 
            }
            if(key=='D')
            {
              entered="";
              break;
            }
          }
          lcd.setCursor(0, 1);
          lcd.print("Pressed: ");
          if(key!='C' && key!='B' && key!='A')
          {
            lcd.setCursor(a,1);
            lcd.print(key);
            delay(300);
            lcd.setCursor(a,1);
            lcd.print("*");
            entered += key;
            delay(500);
            a++;
            lcd.noBlink();
          }
        }
      }
      if(key!='D')
      {
        pass=entered;
        entered="";
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("New pass is set");
        lcd.setCursor(0,1);
        lcd.print("Successfully....");
        delay(2000);
      }
      lcd.clear();
      a=9;
    }
    else if(key!='D')
    {
      entered="";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Security Alert");
      lcd.setCursor(0,1);
      lcd.print("Try after:");
      lcd.setCursor(13,1);
      lcd.print("Sec");
      togg=1;
      for(int i=4;i>=0;i--)
      {
        lcd.setCursor(11,1);
        lcd.print(i);
        delay(1000);
        digitalWrite(buzz,togg);
        togg=!togg;
      }
      digitalWrite(buzz,0);
      lcd.clear();
      a=9;
    }
  }
}
