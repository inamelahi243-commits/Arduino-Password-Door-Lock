#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo setup
Servo doorServo;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Components pins
int greenLED = 10;
int redLED = 11;
int buzzer = 12;
int servoPin = 13;

// Passwords
char openPIN[] = "1234";
char closePIN[] = "4321";

char enteredPIN[5];

int index = 0;
bool doorOpened = false;

void setup() {

  // LEDs and buzzer setup
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Servo setup
  doorServo.attach(servoPin);
  doorServo.write(0);

  // LCD setup
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Enter Open PIN");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    // Show * on LCD
    if (index < 4) {

      enteredPIN[index] = key;
      index++;

      lcd.setCursor(index - 1, 1);
      lcd.print("*");
    }

    // When 4 digits entered
    if (index == 4) {

      enteredPIN[4] = '\0';

      // -------- OPEN DOOR --------
      if (!doorOpened && strcmp(enteredPIN, openPIN) == 0) {

        digitalWrite(greenLED, HIGH);

        tone(buzzer, 1000, 300);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("DOOR OPENED");

        // Servo opens
        doorServo.write(90);

        doorOpened = true;

        delay(2000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter ClosePIN");

        digitalWrite(greenLED, LOW);
      }

      // ------- CLOSE DOOR --------
      else if (doorOpened && strcmp(enteredPIN, closePIN) == 0) {

        digitalWrite(greenLED, HIGH);

        tone(buzzer, 1000, 300);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("DOOR CLOSED");

        // Servo closes
        doorServo.write(0);

        doorOpened = false;

        delay(2000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Open PIN");

        digitalWrite(greenLED, LOW);
      }

      // -------- WRONG PASSWORD --------
      else {

        digitalWrite(redLED, HIGH);

        tone(buzzer, 500, 1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WRONG PASSWORD");

        delay(2000);

        digitalWrite(redLED, LOW);

        lcd.clear();

        if (doorOpened) {

          lcd.setCursor(0,0);
          lcd.print("Enter ClosePIN");
        }

        else {

          lcd.setCursor(0,0);
          lcd.print("Enter Open PIN");
        }
      }

      resetInput();
    }
  }
}

// Reset keypad input
void resetInput() {

  index = 0;

  for (int i = 0; i < 5; i++) {

    enteredPIN[i] = '\0';
  }

  lcd.setCursor(0,1);
  lcd.print("                ");
}
