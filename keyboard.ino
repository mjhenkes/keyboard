#include <Keyboard.h>

const int buttonPins[9] = {1, 2, 4, 6, 8, 10, 14, 18, 20};
const int ledPins[9] = {0, 3, 5, 7, 9, 16, 15, 19, 21};

int buttonState[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int lastButtonState[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
char mappedChars[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

unsigned long lastDebounceTime[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

void setup()
{
  int button = 0;
  while(button < 9){
    pinMode(buttonPins[button], INPUT);  // Set the button as an input
    digitalWrite(buttonPins[button], HIGH);  // Pull the button high
    pinMode(ledPins[button], OUTPUT);
    digitalWrite(ledPins[button], LOW);
    button++;
  }
}

int debounceButton(int button)
{
  int reading = digitalRead(buttonPins[button]);
  bool buttonChange = false;
  
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState[button]) {
    // reset the debouncing timer
    lastDebounceTime[button] = millis();
  }

  if ((millis() - lastDebounceTime[button]) > debounceDelay) {
    if (reading != buttonState[button]) {
      buttonState[button] = reading;
      buttonChange = true;
    }
  }

  lastButtonState[button] = reading;
  
  return buttonChange;
}

void loop()
{
//  Serial.print("hi");
  int button = 0;
  while(button < 9){
    if (debounceButton(button)) {
      int currentState = buttonState[button];
      if(currentState == LOW) {
        Keyboard.write(mappedChars[button]);
      }
  
      digitalWrite(ledPins[button], !currentState); 
    }
    button++;
  }
}
