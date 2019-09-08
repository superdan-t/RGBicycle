void resetAll() {
  for (byte i = 0; i < 12; i++) {
    dimmers[i].function = 0;
    dimmers[i].data[0] = 0;
    dimmers[i].data[1] = 0;
    dimmers[i].data[2] = 0;
    dimmers[i].data[3] = 0;
    dimmers[i].data[4] = 0;
    setLevel(&dimmers[i], 0);
  }
}

void makeStrobe(Dimmer *dim, byte upTicks, byte downTicks, byte upLevel, byte downLevel) {
  dim->data[0] = upTicks;
  dim->data[1] = downTicks;
  dim->data[2] = upLevel;
  dim->data[3] = downLevel;
  dim->data[4] = 0;
  dim->function = 2;
}

void makeFade(Dimmer *dim, byte finalValue, byte step, byte skip) {
  dim->data[0] = finalValue;
  dim->data[1] = step;
  dim->data[2] = skip;
  dim->data[3] = 0;
  dim->data[4] = 0;
  dim->function = 1;
}

void makeFade(Dimmer *dim, byte finalValue, byte ticks) {
  byte dif = dim->value < finalValue ? (finalValue - dim->value): (dim->value - finalValue);
  makeFade(dim, finalValue, (byte) ceil((float) dif / (float) ticks), 0);
}

void applyPreset(byte presetID, boolean enforce) {
  for (byte i = 0; i < 12; i++) {
    if (enforce) {
      setLevel(&dimmers[i], presets[presetID].values[i]);
    } else {
      dimmers[i].value = presets[presetID].values[i];
    }
  }
}

int getNextEnabledPreset() {

  if (!presetsEnabled) return -1;

  byte i = presetIndex != -1 ? presetIndex : 0;

  for (byte totalChecked = 0; totalChecked < 20; totalChecked++) {

    if (i == 19) {
      i = 0;
    } else {
      i++;
    }

    if (presets[i].enabled) {
      return i;
    }
    
  }

  return -1;
  
}

boolean applyNextEnabledPreset() {
  if (!presetsEnabled) return false;
  presetIndex = getNextEnabledPreset();
  applyPreset(presetIndex, true);
  return true;
}
