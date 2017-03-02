#pragma once

/* PCA9534 library by Abdulrahman Saleh Khamis
 *
 * This library allows for easy interfacing with PCA9534 GPIO expander chip
 * using I2C protocol. It has familiar functions when dealing with the pins
 * such as pinMode(), digitalWrite(), and digitalRead().
 *
 * It also allows using inverted input, as well as interrupt when input status
 * changes, to avoid continuous polling.
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

#define PCA9534_I2C_ADDRESS     0x20
#define PCA9534_IP_REGISTER     0x00
#define PCA9534_OP_REGISTER     0x01
#define PCA9534_INV_REGISTER    0x02
#define PCA9534_CONF_REGISTER   0x03
#define INPUT_INVERTED          0x04


class PCA9534 {
public:
  /**
   * Constructor
   * Creates a new PCA9534 class to manage a PCA9534 chip.
   */
  PCA9534();

  /**
   * Initializes the device and performs initial I2C setup.
   * This method should be called before any others are used.
   *
   * @param i2caddr sets the slave address of the PCA9534, defaults to 0x20.
   */
  void begin(uint8_t i2caddr = PCA9534_I2C_ADDRESS);

  /**
   * Configures the specified pin to behave either as an input, inverted input,
   * or output.
   *
   * @param pin is number of the pin whose mode you wish to set.
   * @param mode INPUT, INPUT_INVERTED, or OUTPUT.
   */
  void pinMode(uint8_t pin, uint8_t mode);

  /**
   * Writes a HIGH or a LOW value to a digital pin.
   *
   * @param pin is number of the pin whose value you wish to set.
   * @param value HIGH, or LOW.
   */
  void digitalWrite(uint8_t pin, uint8_t value);

  /**
   * Reads the value from a specified digital pin, either HIGH or LOW.
   *
   * @param pin is number of the pin whose value you wish to get.
   * @return the status of the pin either HIGH or LOW. Note: when using
   * INPUT_INVERTED on pinMode(), you will get the inverted status.
   */
  uint8_t digitalRead(uint8_t pin);

private:
  uint8_t _i2caddr; // I2C address of the device
  uint8_t _port; // Port configuration status on Configuration register
  uint8_t _invport; // Port inverted status on Polarity Inversion register
};
