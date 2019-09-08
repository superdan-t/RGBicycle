#include <Wire.h>

const byte remoteAddress = 10;

const byte tickDuration = 20;

const byte dimmerCount = 12;

struct Dimmer {
  byte pin;
  byte method;
  byte value;
  byte function;
  byte data[5];
};
long nextDimmerTick;
Dimmer dimmers[dimmerCount];

struct Preset {
  byte values[12];
  boolean enabled = false;
};

Preset presets[20];
boolean presetsEnabled;
int presetIndex = -1;

byte specialFunction = 0;
byte specialFunctionParam = 0;
byte speed = 50;
byte brightness = 70;
boolean terminateCondition = false;
boolean unhalt = false;

byte serialBuffer[64];
byte serialIndex = 0;
byte serialLength = 0;

byte replyBuffer[50];
byte replySize = 0;

void setup() {

  //Bluetooth
  Serial.begin(9600);

  Wire.begin();

  dimmers[0].pin = 5;
  dimmers[1].pin = 3;
  dimmers[2].pin = 6;
  dimmers[3].pin = 10;
  dimmers[4].pin = 9;
  dimmers[5].pin = 11;

  dimmers[6].pin = 0;
  dimmers[7].pin = 1;
  dimmers[8].pin = 2;
  dimmers[9].pin = 3;
  dimmers[10].pin = 4;
  dimmers[11].pin = 5;

  dimmers[6].method = 1;
  dimmers[7].method = 1;
  dimmers[8].method = 1;
  dimmers[9].method = 1;
  dimmers[10].method = 1;
  dimmers[11].method = 1;

  initDimmers();

}

void loop() {

  if (millis() >= nextDimmerTick) {
    nextDimmerTick = millis() + tickDuration;
    runDimmers(false);
  }

  if (terminateCondition) {
    terminateCondition = false;
    switch (specialFunction) {
      case 1:
        policeLights();
        break;
      case 2:
        strobe(-1);
        break;
      case 3:
        flash(-1);
        break;
      case 4:
        build((boolean) specialFunctionParam);
        break;
      case 5:
        construct((boolean) specialFunctionParam);
        break;
      case 6:
        breathe(-1);
        break;
      case 7:
        rotate((boolean) specialFunctionParam, -1);
        break;
      case 8:
        shift((boolean) specialFunctionParam, -1);
        break;
      case 9:
        shiftSmooth((boolean) specialFunctionParam, -1);
        break;
      case 10:
        colorFade(-1);
        break;
      case 11:
        colorJump(-1);
        break;
      case 12:
        mixtureA();
        break;
      case 13:
        mixtureB();
        break;
    }
  }

}

boolean wait(byte cycles) {
  byte cyclesPassed = 0;
  while (cyclesPassed != cycles && !terminateCondition) {
    if (millis() >= nextDimmerTick) {
      nextDimmerTick = millis() + tickDuration;
      runDimmers(false);
      cyclesPassed++;
    }
    serialEvent();
  }

  if (terminateCondition) {
    return false;
  } else {
    return true;
  }

}

boolean halt() {
  while (!terminateCondition && !unhalt) {
    if (millis() >= nextDimmerTick) {
      nextDimmerTick = millis() + tickDuration;
      runDimmers(false);
    }
    serialEvent();
  }

  if (unhalt) {
    unhalt = false;
    return true;
  } else {
    return false;
  }
}
