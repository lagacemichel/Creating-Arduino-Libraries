/*
  DHT22 Sensor library V1.0.0
  DHT22 Temperature / Humidity Controller Class Body

  DHT22 temperature and relative humidity sensor handling class. This class
  allows the instanciation of objects that communicate with a DHT22 sensor
  connected to a digital input/output port on an Arduino micro-controller.
  This code is associated with the Creating Arduino Libraries blog post on
  https://lagacemichel.com

  MIT License

  Copyright (c) 2025, Michel Lagace

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Arduino.h"
#include "DHT22.h"

const int CYCLES_PER_COUNT = 50;
const int TIMEOUT_MICROSECONDS = 300;
const int TIMEOUT = TIMEOUT_MICROSECONDS / CYCLES_PER_COUNT*F_CPU / 1000000;
const int ONE_SECOND = 1000;
const int TWO_SECONDS = 2000;
const int TWO_MILLISECONDS = 2;

// DH22 constructor, accepts Arduino digital I/O port number
DHT22::DHT22(int pin) {
  _pin = pin;
  _data[0] = 0;
  _data[1] = 0;
  _data[2] = 0;
  _data[3] = 0;
  _data[4] = 0;
  _lastRead = 0;
  _firstTime = true;
  _temperature = 0.0;
  _relativeHumidity = 0.0;
}

// DH22 destructor
DHT22::~DHT22() {
}

// DHT22 sensor initialization
void DHT22::begin() {
  fetchData();
}

// Return temperature
float DHT22::readTemperature() {
  // Get data from sensor and return temperature read
  fetchData();
  return _temperature;
}

// Return relative humidity
float DHT22::readRelativeHumidity() {
  // Get data from sensor and return relative humidity read
  fetchData();
  return _relativeHumidity;
}

// Return the number of milliseconds since last time read
unsigned long DHT22::timeSinceLastRead() const {
  // Get current processor time
  unsigned long currentMilliseconds = millis();
  unsigned long timeSince = 0;

  // Check if time wrapped around, if so use two's complement
  if (currentMilliseconds < _lastRead) {
    timeSince = ~_lastRead + 1 + currentMilliseconds;
  }

  // Otherwise use difference
  else {
    timeSince = currentMilliseconds - _lastRead;
  }

  // Return elapsed time
  return timeSince;
}

// Wait for serial line to reach a state and return relative time
int DHT22::waitForState(bool state) const {
  int count = 0;
  while ((bool)digitalRead(_pin) != state) {
    count++;
    if (count >= TIMEOUT) {
      count = 0;
      break;
    }
  }
  return count;
}

// Fetch data from sensor
void DHT22::fetchData() {
  // We will access sensor on the very first time and if more than two
  // seconds have passed since last access.
  if (_firstTime || (timeSinceLastRead() > TWO_SECONDS)) {

    // First time around, wait at least one second for sensor to settle
    if (_firstTime) {
      _firstTime = false;
      pinMode(_pin, INPUT_PULLUP);
      delay(ONE_SECOND);
    }

    // Send request signal to read temperature and relative humidity from device.
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(TWO_MILLISECONDS);
    pinMode(_pin, INPUT_PULLUP);

    // Since timings are critical, prevent interrupts while DHT22 transmits
    noInterrupts();

    // Get Start of Transmission, falling, rising, then falling edges
    // Interval: 80 micro-seconds, no need to check
    int lowCounter = 0;
    int highCounter = 0;
    highCounter = waitForState(LOW);
    if (highCounter > 0) {
      lowCounter = waitForState(HIGH);
      if (lowCounter > 0) {
        highCounter = waitForState(LOW);
      }
    }

    // Get 40 bits of data and store them in the data array
    if (highCounter > 0) {
      for (int bitN = 0; bitN < 40; bitN++) {  // 40 bits, 5 x 8-bit bytes
        lowCounter = waitForState(HIGH);       // Byte 0: Relative Humidity MSB
        if (lowCounter > 0) {                  // Byte 1: Relative Humidity LSB
          highCounter = waitForState(LOW);     // Byte 2: Temperature MSB
          if (highCounter > 0) {               // Byte 3: Temperature LSB
            int byteN = bitN / 8;              // Byte 4: Checksum
            _data[byteN] <<= 1;
            if (highCounter > lowCounter) {    // Low 50us, High 25us -> 0 (low time > high time)
              _data[byteN] |= 1;               // Low 50us, High 70us -> 1 (low time < high time)
            }
          }
        }
      }
    }
    // Reception complete, interrupts are re-enabled
    interrupts();

    // Save the time of last data transfer
    _lastRead = millis();

    // Compute temperature and relative humidity if data is valid
    byte checksum = _data[0] + _data[1] + _data[2] + _data[3];
    if (_data[4] == checksum) {
      _relativeHumidity = int16_t((_data[0] << 8) + _data[1]) / 10.0;
      _temperature = int16_t((_data[2] << 8) + _data[3]) / 10.0;
    }
    else {
      _relativeHumidity = 0.0;
      _temperature = 0.0;
    }
  }
}
