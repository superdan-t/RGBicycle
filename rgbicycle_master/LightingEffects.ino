void colorJump(int limit) {
  byte r = 0;
  while (!terminateCondition && r != limit && presetsEnabled) {
    applyNextEnabledPreset();
    if (!wait(51 - speed / 2)) return;
    r++;
  }
}

void colorFade(int limit) {
  byte r = 0;
  while (!terminateCondition && r != limit && presetsEnabled) {
    presetIndex = getNextEnabledPreset();
    for (byte i = 0; i < 12; i++) {
      makeFade(&dimmers[i], presets[presetIndex].values[i], 51 - speed / 2);
    }
    if (!wait(51 - speed / 2)) return;
  }
  r++;
}


void shift(boolean reverse, int limit) {

  byte shiftCount = 0;
  byte r = 0;

  if (presetsEnabled) {
    if (presetIndex == -1) {
      applyNextEnabledPreset();
    }
  }

  while (!terminateCondition && shiftCount != limit) {

    byte shiftBuffer[3];

    if (reverse) {

      shiftBuffer[0] = dimmers[9].value;
      shiftBuffer[1] = dimmers[10].value;
      shiftBuffer[2] = dimmers[11].value;

      setLevel(&dimmers[9], dimmers[6].value);
      setLevel(&dimmers[10], dimmers[7].value);
      setLevel(&dimmers[11], dimmers[8].value);

      setLevel(&dimmers[6], dimmers[0].value);
      setLevel(&dimmers[7], dimmers[1].value);
      setLevel(&dimmers[8], dimmers[2].value);

      setLevel(&dimmers[0], dimmers[3].value);
      setLevel(&dimmers[1], dimmers[4].value);
      setLevel(&dimmers[2], dimmers[5].value);

      setLevel(&dimmers[3], shiftBuffer[0]);
      setLevel(&dimmers[4], shiftBuffer[1]);
      setLevel(&dimmers[5], shiftBuffer[2]);


    } else {

      shiftBuffer[0] = dimmers[0].value;
      shiftBuffer[1] = dimmers[1].value;
      shiftBuffer[2] = dimmers[2].value;

      setLevel(&dimmers[0], dimmers[6].value);
      setLevel(&dimmers[1], dimmers[7].value);
      setLevel(&dimmers[2], dimmers[8].value);

      setLevel(&dimmers[6], dimmers[9].value);
      setLevel(&dimmers[7], dimmers[10].value);
      setLevel(&dimmers[8], dimmers[11].value);

      setLevel(&dimmers[9], dimmers[3].value);
      setLevel(&dimmers[10], dimmers[4].value);
      setLevel(&dimmers[11], dimmers[5].value);

      setLevel(&dimmers[3], shiftBuffer[0]);
      setLevel(&dimmers[4], shiftBuffer[1]);
      setLevel(&dimmers[5], shiftBuffer[2]);

    }

    if (!wait(51 - speed / 2)) return;

    shiftCount++;

    if (presetsEnabled && shiftCount % 8 == 0) {
      applyNextEnabledPreset();
    }

  }

}

void shiftSmooth(boolean reverse, int limit) {

  byte shiftCount = 0;
  byte shiftBuffer[3];

  if (presetsEnabled) {
    if (presetIndex == -1) {
      applyNextEnabledPreset();
    }
  }

  while (!terminateCondition && shiftCount != limit) {

    if (reverse) {

      shiftBuffer[0] = dimmers[9].value;
      shiftBuffer[1] = dimmers[10].value;
      shiftBuffer[2] = dimmers[11].value;

      makeFade(&dimmers[9], dimmers[6].value, 51 - speed / 2);
      makeFade(&dimmers[10], dimmers[7].value, 51 - speed / 2);
      makeFade(&dimmers[11], dimmers[8].value, 51 - speed / 2);

      makeFade(&dimmers[6], dimmers[0].value, 51 - speed / 2);
      makeFade(&dimmers[7], dimmers[1].value, 51 - speed / 2);
      makeFade(&dimmers[8], dimmers[2].value, 51 - speed / 2);

      makeFade(&dimmers[0], dimmers[3].value, 51 - speed / 2);
      makeFade(&dimmers[1], dimmers[4].value, 51 - speed / 2);
      makeFade(&dimmers[2], dimmers[5].value, 51 - speed / 2);

      makeFade(&dimmers[3], shiftBuffer[0], 51 - speed / 2);
      makeFade(&dimmers[4], shiftBuffer[1], 51 - speed / 2);
      makeFade(&dimmers[5], shiftBuffer[2], 51 - speed / 2);


    } else {

      shiftBuffer[0] = dimmers[0].value;
      shiftBuffer[1] = dimmers[1].value;
      shiftBuffer[2] = dimmers[2].value;

      makeFade(&dimmers[0], dimmers[6].value, 51 - speed / 2);
      makeFade(&dimmers[1], dimmers[7].value, 51 - speed / 2);
      makeFade(&dimmers[2], dimmers[8].value, 51 - speed / 2);

      makeFade(&dimmers[6], dimmers[9].value, 51 - speed / 2);
      makeFade(&dimmers[7], dimmers[10].value, 51 - speed / 2);
      makeFade(&dimmers[8], dimmers[11].value, 51 - speed / 2);

      makeFade(&dimmers[9], dimmers[3].value, 51 - speed / 2);
      makeFade(&dimmers[10], dimmers[4].value, 51 - speed / 2);
      makeFade(&dimmers[11], dimmers[5].value, 51 - speed / 2);

      makeFade(&dimmers[3], shiftBuffer[0], 51 - speed / 2);
      makeFade(&dimmers[4], shiftBuffer[1], 51 - speed / 2);
      makeFade(&dimmers[5], shiftBuffer[2], 51 - speed / 2);

    }

    if (!wait(51 - speed / 2)) break;

    shiftCount++;

    if (presetsEnabled && shiftCount % 16 == 0) {

      presetIndex = getNextEnabledPreset();

      for (byte i = 0; i < 12; i++) {
        makeFade(&dimmers[i], presets[presetIndex].values[i], 51 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

    }

  }

  if (terminateCondition) {
    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], dimmers[i].data[0]);
      dimmers[i].function = 0;
    }
  }

}

void breathe(int limit) {
  byte r = 0;
  if (presetsEnabled && presetIndex == -1) {
    applyNextEnabledPreset();
  }

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }

  while (!terminateCondition && r != limit) {

    for (byte i = 0; i < 12; i++) {
      makeFade(&dimmers[i], 0, 51 - speed / 2);
    }
    if (!wait(77 - 3 * speed / 4)) break;

    for (byte i = 0; i < 12; i++) {
      makeFade(&dimmers[i], restoreToLevels[i], 51 - speed / 2);
    }
    if (!wait(77 - 3 * speed / 4)) break;

    if (presetsEnabled) {
      presetIndex = getNextEnabledPreset();
      for (byte i = 0; i < 12; i++) {
        restoreToLevels[i] = presets[presetIndex].values[i];
      }
    }

    r++;

  }

  if (terminateCondition) {
    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], restoreToLevels[i]);
    }
  }

}

void rotate(boolean reverse, int limit) {

  byte r = 0;

  if (presetsEnabled && presetIndex == -1) {
    applyNextEnabledPreset();
  }

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }
  resetAll();

  while (!terminateCondition && r != limit) {

    if (reverse) {

      setLevel(&dimmers[6], restoreToLevels[6]);
      setLevel(&dimmers[7], restoreToLevels[7]);
      setLevel(&dimmers[8], restoreToLevels[8]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[6], 0);
      setLevel(&dimmers[7], 0);
      setLevel(&dimmers[8], 0);

      setLevel(&dimmers[9], restoreToLevels[9]);
      setLevel(&dimmers[10], restoreToLevels[10]);
      setLevel(&dimmers[11], restoreToLevels[11]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[9], 0);
      setLevel(&dimmers[10], 0);
      setLevel(&dimmers[11], 0);

      setLevel(&dimmers[3], restoreToLevels[3]);
      setLevel(&dimmers[4], restoreToLevels[4]);
      setLevel(&dimmers[5], restoreToLevels[5]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[3], 0);
      setLevel(&dimmers[4], 0);
      setLevel(&dimmers[5], 0);

      setLevel(&dimmers[0], restoreToLevels[0]);
      setLevel(&dimmers[1], restoreToLevels[1]);
      setLevel(&dimmers[2], restoreToLevels[2]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[0], 0);
      setLevel(&dimmers[1], 0);
      setLevel(&dimmers[2], 0);

    } else {

      setLevel(&dimmers[6], restoreToLevels[6]);
      setLevel(&dimmers[7], restoreToLevels[7]);
      setLevel(&dimmers[8], restoreToLevels[8]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[6], 0);
      setLevel(&dimmers[7], 0);
      setLevel(&dimmers[8], 0);

      setLevel(&dimmers[0], restoreToLevels[0]);
      setLevel(&dimmers[1], restoreToLevels[1]);
      setLevel(&dimmers[2], restoreToLevels[2]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[0], 0);
      setLevel(&dimmers[1], 0);
      setLevel(&dimmers[2], 0);

      setLevel(&dimmers[3], restoreToLevels[3]);
      setLevel(&dimmers[4], restoreToLevels[4]);
      setLevel(&dimmers[5], restoreToLevels[5]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[3], 0);
      setLevel(&dimmers[4], 0);
      setLevel(&dimmers[5], 0);

      setLevel(&dimmers[9], restoreToLevels[9]);
      setLevel(&dimmers[10], restoreToLevels[10]);
      setLevel(&dimmers[11], restoreToLevels[11]);

      if (!wait(51 - speed / 2)) break;

      setLevel(&dimmers[9], 0);
      setLevel(&dimmers[10], 0);
      setLevel(&dimmers[11], 0);

    }

    if (presetsEnabled) {
      presetIndex = getNextEnabledPreset();
      for (byte i = 0; i < 12; i++) {
        restoreToLevels[i] = presets[presetIndex].values[i];
      }
    }

    r++;

  }

  //Values are totally restored if a termination was called. If the limit has been reached, however, the full values are loaded to the dimmer value, but are not told to output.
  for (byte i = 0; i < 12; i++) {
    if (terminateCondition) {
      setLevel(&dimmers[i], restoreToLevels[i]);
    } else {
      dimmers[i].value = restoreToLevels[i];
    }
  }

}

void strobe(int limit) {

  if (presetsEnabled) {

    byte r = 0;
    if (presetIndex == -1) {
      applyNextEnabledPreset();
    }
    while (!terminateCondition) {
      if (limit == -1) {
        for (byte i = 0; i < 12; i++) {
          makeStrobe(&dimmers[i], 1, 51 - speed / 2, presets[presetIndex].values[i], 0);
        }
        if (!wait(52 - speed / 2)) break;
        presetIndex = getNextEnabledPreset();
      } else {
        for (byte i = 0; i < 12; i++) {
          makeStrobe(&dimmers[i], 1, 51 - speed / 2, presets[presetIndex].values[i], 0);
        }
        if (!wait(52 - speed / 2)) break;
        r++;
        if (r == limit) return;
        presetIndex = getNextEnabledPreset();

      }
    }

  } else {

    for (byte i = 0; i < 12; i++) {
      makeStrobe(&dimmers[i], 1, 51 - speed / 2, dimmers[i].value, 0);
    }
    while (!terminateCondition) {
      if (limit == -1) {
        halt();
      } else {
        wait(limit * (52 - speed / 2));
        break;
      }
      if (!terminateCondition) {
        for (byte i = 0; i < 12; i++) {
          dimmers[i].data[1] = 51 - speed / 2;
        }
      }
    }

  }

  if (terminateCondition) {
    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], dimmers[i].data[2]);
    }
  }

}

void flash(int limit) {

  if (presetsEnabled) {

    byte r = 0;
    if (presetIndex == -1) {
      applyNextEnabledPreset();
    }
    while (!terminateCondition) {
      if (limit == -1) {
        for (byte i = 0; i < 12; i++) {
          makeStrobe(&dimmers[i], 51 - speed / 2, 51 - speed / 2, presets[presetIndex].values[i], 0);
        }
        if (!wait(102 - speed)) break;
        presetIndex = getNextEnabledPreset();
      } else {
        for (byte i = 0; i < 12; i++) {
          makeStrobe(&dimmers[i], 51 - speed / 2, 51 - speed / 2, presets[presetIndex].values[i], 0);
        }
        if (!wait(102 - speed)) break;
        r++;
        if (r == limit) return;
        presetIndex = getNextEnabledPreset();

      }
    }

  } else {

    for (byte i = 0; i < 12; i++) {
      makeStrobe(&dimmers[i], 51 - speed / 2, 51 - speed / 2, dimmers[i].value, 0);
    }
    while (!terminateCondition) {
      if (limit == -1) {
        halt();
      } else {
        wait(limit * (102 - speed));
        break;
      }
      if (!terminateCondition) {
        for (byte i = 0; i < 12; i++) {
          dimmers[i].data[1] = 51 - speed / 2;
          dimmers[i].data[2] = 51 - speed / 2;
        }
      }
    }

  }

  if (terminateCondition) {
    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], dimmers[i].data[2]);
    }
  }

}

void policeLights() {

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }
  resetAll();

  while (!terminateCondition) {

    makeStrobe(&dimmers[8], 51 - speed / 2, 51 - speed / 2, 255, 0);
    makeStrobe(&dimmers[5], 51 - speed / 2, 51 - speed / 2, 255, 0);
    if (!wait(204 - speed * 2)) {
      break;
    }

    dimmers[8].function = 0;
    dimmers[5].function = 0;

    makeStrobe(&dimmers[0], 51 - speed / 2, 51 - speed / 2, 255, 0);
    makeStrobe(&dimmers[3], 51 - speed / 2, 51 - speed / 2, 255, 0);
    if (!wait(204 - speed * 2)) {
      break;
    }

    dimmers[0].function = 0;
    dimmers[3].function = 0;

  }

  for (byte i = 0; i < 12; i++) {
    setLevel(&dimmers[i], restoreToLevels[i]);
  }

}

boolean build(boolean reverse) {
  return build(reverse, 0);
}

/**
   Reverse: An alternative build down where the order is reverse of the build up
   Condition: 0 - nothing, 1 - stop after building up, 2 - START by building down
*/
boolean build(boolean reverse, byte condition) {

  if (presetsEnabled && presetIndex == -1) {
    applyNextEnabledPreset();
  }

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }
  resetAll();

  while (!terminateCondition) {

    if (condition != 2) {

      for (byte i = 0; i < 3; i++) {
        makeFade(&dimmers[i], restoreToLevels[i], 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break; //The difference (51 vs 55) is intentional. The next fade will start before the last is finished

      for (byte i = 6; i < 9; i++) {
        makeFade(&dimmers[i], restoreToLevels[i], 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        makeFade(&dimmers[i], restoreToLevels[i], 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 9; i < 12; i++) {
        makeFade(&dimmers[i], restoreToLevels[i], 55 - speed / 2);
      }
      if (!wait(55 - speed / 2)) break;

    }

    if (condition == 1) {
      return true;
    }

    if (reverse) {

      for (byte i = 9; i < 12; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 6; i < 9; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 0; i < 3; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(55 - speed / 2)) break;

    } else {
      for (byte i = 0; i < 3; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 6; i < 9; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 9; i < 12; i++) {
        makeFade(&dimmers[i], 0, 55 - speed / 2);
      }
      if (!wait(55 - speed / 2)) break;

    }

    if (condition == 2) {
      return true;
    }

    if (presetsEnabled) {
      presetIndex = getNextEnabledPreset();
      for (byte i = 0; i < 12; i++) {
        restoreToLevels[i] = presets[presetIndex].values[i];
      }
    }

  }

  for (byte i = 0; i < 12; i++) {
    setLevel(&dimmers[i], restoreToLevels[i]);
  }

  return false;

}

boolean construct(boolean reverse) {
  return construct(reverse, 0);
}

boolean construct(boolean reverse, byte condition) {

  if (presetsEnabled && presetIndex == -1) {
    applyNextEnabledPreset();
  }

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }
  resetAll();

  while (!terminateCondition) {

    if (condition != 2) {
      for (byte i = 0; i < 3; i++) {
        setLevel(&dimmers[i], restoreToLevels[i]);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 6; i < 9; i++) {
        setLevel(&dimmers[i], restoreToLevels[i]);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        setLevel(&dimmers[i], restoreToLevels[i]);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 9; i < 12; i++) {
        setLevel(&dimmers[i], restoreToLevels[i]);
      }
      if (!wait(51 - speed / 2)) break;
    }

    if (condition == 1) return true;

    if (reverse) {

      for (byte i = 9; i < 12; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 6; i < 9; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 0; i < 3; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

    } else {

      for (byte i = 0; i < 3; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 6; i < 9; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 3; i < 6; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

      for (byte i = 9; i < 12; i++) {
        setLevel(&dimmers[i], 0);
      }
      if (!wait(51 - speed / 2)) break;

    }

    if (condition == 2) return true;

    if (presetsEnabled) {
      presetIndex = getNextEnabledPreset();
      for (byte i = 0; i < 12; i++) {
        restoreToLevels[i] = presets[presetIndex].values[i];
      }
    }

  }

  for (byte i = 0; i < 12; i++) {
    setLevel(&dimmers[i], restoreToLevels[i]);
  }

  return false;

}
