/* Example usage for PCA9534 library by Abdulrahman Saleh Khamis.
 * Demonstrates the use of simple input/output functionality of the PCA9534.
 *
 * You need to connect:
 * LED to PCA9534 IO pin 0
 * Button to PCA9534 IO pin 1
 */

#include "PCA9534.h"

#define GPIO_PIN_LED           0  // LED connected to GPIO-0 as output
#define GPIO_PIN_BUTTON        1  // Button connected to GPIO-1 as input

PCA9534 gpio;

// Helps ensure the application loop is not interrupted by the system
// background processing and network management.
SYSTEM_THREAD(ENABLED);

void setup() {
  gpio.begin();

  gpio.pinMode(GPIO_PIN_LED, OUTPUT);
  gpio.pinMode(GPIO_PIN_BUTTON, INPUT);

  gpio.digitalWrite(GPIO_PIN_LED, HIGH); // LED off
}

void loop() {
  uint8_t buttonStatus = gpio.digitalRead(GPIO_PIN_BUTTON);
  if (buttonStatus == LOW) {
    gpio.digitalWrite(GPIO_PIN_LED, LOW); // LED On
  } else {
    gpio.digitalWrite(GPIO_PIN_LED, HIGH); // LED Off
  }
}
