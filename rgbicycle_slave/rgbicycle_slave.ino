#include <Wire.h>

const byte remoteAddress = 10;

const byte dimmerCount = 6;

byte targetDimmer;
byte newValue;
boolean dimmerSupplied = false;
boolean pairComplete = false;

struct Dimmer {
  byte pin;
  byte value;
};

Dimmer dimmers[6];

void setup() {

  Wire.begin(remoteAddress);
  Wire.onReceive(receiveEvent);

  dimmers[0].pin = 5;
  dimmers[1].pin = 3;
  dimmers[2].pin = 6;
  dimmers[3].pin = 10;
  dimmers[4].pin = 11;
  dimmers[5].pin = 9;

  initDimmers();

}

void loop() {
  //Nothing to loop. Just waiting for incoming data
}

void receiveEvent(int amount) {
  while (Wire.available()) {
    if (!dimmerSupplied) {
      targetDimmer = Wire.read();
      dimmerSupplied = true;
    } else {
      newValue = Wire.read();
      pairComplete = true;
    }

    if (pairComplete) {
      pairComplete = false;
      dimmerSupplied = false;
      setLevel(&dimmers[targetDimmer], newValue);
    }

  }

}

/**
   Sets the output level of the specified dimmer. Accepts dimmer struct, not an index.
*/
void setLevel(Dimmer *dim, byte value) {
  dim->value = value;
  analogWrite(dim->pin, value);
}

/**
   Loads properties from memory and sets necessary pins to outputs
*/
void initDimmers() {

  for (byte i = 0; i < dimmerCount; i++) {
    pinMode(dimmers[i].pin, OUTPUT);
  }

}
