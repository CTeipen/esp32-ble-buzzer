#include <BleKeyboard.h>

#define BUTTON_PIN          14
#define LED_TRIGGER_PIN     12
#define LED_BLE_PIN         27
#define LED_POWER_PIN       13

BleKeyboard bleKeyboard;

int button_state;
int last_button_state;

boolean connected = false;
boolean connectedLed = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_POWER_PIN, OUTPUT);
  digitalWrite(LED_POWER_PIN, HIGH);

  pinMode(LED_TRIGGER_PIN, OUTPUT);
  digitalWrite(LED_TRIGGER_PIN, LOW);

  pinMode(LED_BLE_PIN, OUTPUT);
  digitalWrite(LED_BLE_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button_state = digitalRead(BUTTON_PIN);
  
  bleKeyboard.setName("Buzzer");
  
  bleKeyboard.begin();
}


void controlConnectionLED() {
  if(!connected && bleKeyboard.isConnected()) {
    digitalWrite(LED_BLE_PIN, HIGH);
    connectedLed = true;
  }
}


void loop() {
  controlConnectionLED();
  connected = bleKeyboard.isConnected();

  if(connected) {
    last_button_state = button_state;
    button_state = digitalRead(BUTTON_PIN);
    delay(10);
  
    if (last_button_state == HIGH && button_state == LOW) {
      Serial.println("The button is pressed");

      bleKeyboard.write(KEY_RETURN);
      digitalWrite(LED_TRIGGER_PIN, HIGH);
      delay(1000);
      digitalWrite(LED_TRIGGER_PIN, LOW);
    }
  } else {
    if(connectedLed) {
      digitalWrite(LED_BLE_PIN, LOW);
    } else {
      digitalWrite(LED_BLE_PIN, HIGH);
    }
    
    connectedLed = !connectedLed;
    delay(500);
  }
}
