/**
 * A generic and fun mixture of all of the effects. It does not utilize presets and will disable them.
 */
void mixtureA() {

  presetsEnabled = false;

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }

  while (!terminateCondition) {

    speed = 42;

    construct(false, 1);
    if (terminateCondition) return;

    speed = 20;

    shiftSmooth(false, 24);
    if (terminateCondition) return;

    shiftSmooth(true, 24);
    if (terminateCondition) return;

    wait(150);
    if (terminateCondition) return;

    speed = 42;

    construct(true, 2);
    if (terminateCondition) return;

    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], restoreToLevels[i]);
    }
    speed = 20;

    strobe(2);
    if (terminateCondition) return;

    speed = 40;

    strobe(2);
    if (terminateCondition) return;

    speed = 60;

    strobe(3);
    if (terminateCondition) return;

    speed = 80;

    strobe(5);
    if (terminateCondition) return;

    speed = 95;

    strobe(10);
    if (terminateCondition) return;

    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], restoreToLevels[i]);
    }
    speed = 20;
    breathe(2);
    if (terminateCondition) return;

    build(false, 2);
    if (terminateCondition) return;

    speed = 20;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 40;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 60;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 80;
    rotate(false, 1);
    if (terminateCondition) return;

  }
}

/**
 * Almost the same as mixture A, but it switches the preset every now and then. If presets aren't enabled, it will just run A.
 */
void mixtureB() {

  if (!presetsEnabled) {
    mixtureA();
    return;
  }

  presetsEnabled = false;

  applyNextEnabledPreset();

  byte restoreToLevels[12];
  for (byte i = 0; i < 12; i++) {
    restoreToLevels[i] = dimmers[i].value;
  }

  while (!terminateCondition) {

    speed = 42;

    construct(false, 1);
    if (terminateCondition) return;

    speed = 20;

    presetsEnabled = true;

    shiftSmooth(false, 32);
    if (terminateCondition) return;

    presetsEnabled = false;

    shiftSmooth(true, 32);
    if (terminateCondition) return;

    presetsEnabled = false;

    wait(150);
    if (terminateCondition) return;

    speed = 42;

    construct(true, 2);
    if (terminateCondition) return;

    presetsEnabled = true;

    for (byte i = 0; i < 12; i++) {
      setLevel(&dimmers[i], restoreToLevels[i]);
    }
    speed = 20;

    strobe(2);
    if (terminateCondition) return;

    speed = 40;

    strobe(2);
    if (terminateCondition) return;

    speed = 60;

    strobe(3);
    if (terminateCondition) return;

    speed = 80;

    strobe(5);
    if (terminateCondition) return;

    speed = 95;

    strobe(10);
    if (terminateCondition) return;

    speed = 50;
    breathe(2);
    if (terminateCondition) return;

    presetsEnabled = false;

    build(false, 3);
    if (terminateCondition) return;

    speed = 20;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 40;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 60;
    rotate(false, 1);
    if (terminateCondition) return;

    speed = 80;
    rotate(false, 1);
    if (terminateCondition) return;

  }
}
