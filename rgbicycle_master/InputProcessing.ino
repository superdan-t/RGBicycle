void serialEvent() {
  while (Serial.available()) {
    byte newData = Serial.read();
    if (0 == serialLength) {
      serialLength = newData;
    } else {
      serialBuffer[serialIndex++] = newData;
      if (serialIndex >= serialLength) {
        processData(serialBuffer);
        serialIndex = 0;
        serialLength = 0;
        if (replySize > 0) {
          Serial.write(replySize);
          for (byte i = 0; i < replySize; i++) {
            Serial.write(replyBuffer[i]);
          }
          replySize = 0; //Signals that replyBuffer isn't being used and can be overwritten. No need to clear the whole thing.
        }
      }
    }
  }
}

void processData(byte *buf) {
  switch (buf[0]) {
    case 0:
      //Ping
      replyBuffer[0] = 6;
      replySize = 1;
      break;
    case 1:
      //Set all levels
      for (byte i = 0; i < 12; i++) {
        setLevel(&dimmers[i], buf[i + 1]);
      }
      break;
    case 2:
      //Get all levels
      for (byte i = 0; i < 12; i++) {
        replyBuffer[i] = dimmers[i].value;
      }
      replySize = 12;
      break;
    case 3:
      //Set individual level
      setLevel(&dimmers[buf[1]], buf[2]);
      break;
    case 4:
      //Set triplet levels (colors)
      for (byte i = 0; i < buf[1]; i++) {
        setLevel(&dimmers[buf[2 + i * 4] * 3], buf[3 + i * 4]);
        setLevel(&dimmers[buf[2 + i * 4] * 3 + 1], buf[4 + i * 4]);
        setLevel(&dimmers[buf[2 + i * 4] * 3 + 2], buf[5 + i * 4]);
      }
      break;
    case 5:
      //Apply special function
      specialFunction = buf[1];
      specialFunctionParam = buf[2];
      terminateCondition = true;
      break;
    case 6:
      //Break special functions
      specialFunction = 0;
      specialFunctionParam = 0;
      for (byte i = 0; i < 12; i++) {
        dimmers[i].function = 0;
      }
      terminateCondition = true;
      break;
    case 7:
      //Set the speed
      speed = buf[1];
      if (speed > 100) speed = 100;
      unhalt = true;
      break;
    case 8:
      //Set the brightness
      brightness = buf[1];
      if (brightness > 100) brightness = 100;
      forceDimmers();
      break;
    case 9:
      //Get special/param/speed/brightness
      replyBuffer[0] = specialFunction;
      replyBuffer[1] = specialFunctionParam;
      replyBuffer[2] = speed;
      replyBuffer[3] = brightness;
      replySize = 4;
      break;
    case 10:
      //Save a preset
      for (byte i = 0; i < 12; i++) {
        presets[buf[1]].values[i] = buf[2 + i];
      }
      break;
    case 11:
      //Enable/disable presets
      presetsEnabled = false;
      for (byte i = 0; i < 20; i++) {
        presets[i].enabled = buf[1 + i];
        if (buf[1 + i] && !presetsEnabled) {
          presetsEnabled = true;
        }
      }
      presetIndex = -1;
      break;
  }
}
