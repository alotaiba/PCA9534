/* Example usage for PCA9534 library by Abdulrahman Saleh Khamis.
 * Demonstrates the use of interrupt functionality of the PCA9534.
 *
 * You need to connect:
 * LED to PCA9534 IO pin 0
 * Button to PCA9534 IO pin 1
 * PCA9534 INT pin to Particle D4 pin
 */

#include "PCA9534.h"

#define GPIO_PIN_LED           0  // LED connected to GPIO-0 as output
#define GPIO_PIN_BUTTON        1  // Button connected to GPIO-1 as input
#define PARTICLE_PIN_INTERRUPT D4 // Interrupt pin on Particle

PCA9534 gpio;
volatile uint8_t ioState = LOW;
// Last time the output pin was toggled
unsigned long lastDebounceTime = 0;
// Debounce time; increase if the output flickers
unsigned long debounceDelay = 25;

void io() {
  ioState = HIGH;
  // Capture all the flickering
  lastDebounceTime = millis();
}

// Helps ensure the application loop is not interrupted by the system
// background processing and network management.
SYSTEM_THREAD(ENABLED);

void setup() {
  Serial.begin(115200);
  gpio.begin();

  gpio.pinMode(GPIO_PIN_LED, OUTPUT);
  gpio.pinMode(GPIO_PIN_BUTTON, INPUT);

  gpio.digitalWrite(GPIO_PIN_LED, HIGH); // LED off

  attachInterrupt(PARTICLE_PIN_INTERRUPT, io, FALLING);
}

void loop() {
  if (ioState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      uint8_t buttonStatus = gpio.digitalRead(GPIO_PIN_BUTTON);
      if (buttonStatus == LOW) {
        gpio.digitalWrite(GPIO_PIN_LED, LOW); // LED On
      } else {
        gpio.digitalWrite(GPIO_PIN_LED, HIGH); // LED Off
      }
      ioState = LOW; // Reset the state for another interrupt
    }
  }
}
