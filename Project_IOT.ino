#include <LiquidCrystal.h>

//Declare LCD, Gas Sensor, Buzzer 
//Declare led pins (RED, ORANGE, YELLOW, GREEN)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int const GasSensor = A1;
int buzzer = 10;
int LED_GREEN = 7;
int LED_YELLOW = 6;
int LED_ORANGE = 8;
int LED_RED = 9;

void setup() {
  //Set the LED and buzzer pins as OUTPUT to control,
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_ORANGE, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(buzzer, OUTPUT);
    //start Serial communication (9600 baud) for debugging,
    Serial.begin(9600);
    //initialize 16x2 LCD display
    lcd.begin(16, 2);
}

void loop() {
    //Read value from gas sensor (GasSensor)
    int value = analogRead(GasSensor);
    //Convert sensor value (300-750) to 0-100 scale (%)
    value = map(value, 300, 750, 0, 100);
  //Control LEDs based on measured gas levels
    digitalWrite(LED_GREEN, value <= 29 ? HIGH : LOW); //Safe
    digitalWrite(LED_YELLOW, value >= 30 ? HIGH : LOW); //Alert
    digitalWrite(LED_ORANGE, value >= 50 ? HIGH : LOW); //Danger
    digitalWrite(LED_RED, value >= 80 ? HIGH : LOW); //Contaminated
  //Clear LCD display before displaying new data 
    lcd.clear();
    lcd.setCursor(0, 0);
  //Display pollution status on LCD screen and sound warning
    if (value >= 80) {
        lcd.print("CONTAMINATED"); //Severe Pollution
        tone(buzzer, 80, 250); //Play Loud Warning Sound
    } else if (value >= 50) {
        lcd.print("DANGER"); //Danger
        tone(buzzer, 60, 250); //Play medium warning sound
    } else if (value >= 30) {
        lcd.print("ALERT"); //Warning
        tone(buzzer, 20, 250); //Play a small warning sound
    } else {
        lcd.print("SAFE"); //Safe environment
    }
    //Display gas value on second line of LCD display
    lcd.setCursor(0,1);
    lcd.print("Gas: ");
    lcd.print(value);
    lcd.print("%");
  // Pause the program for 500ms before repeating
    delay(500);
}
