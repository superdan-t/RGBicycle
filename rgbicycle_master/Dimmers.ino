/**
   sets necessary pins to outputs
*/
void initDimmers() {

  for (byte i = 0; i < dimmerCount; i++) {
    if (dimmers[i].method == 0) {
      pinMode(dimmers[i].pin, OUTPUT);
    }
  }

}

/**
   Sets the output level of the specified dimmer. Accepts dimmer struct, not an index.
*/
void setLevel(Dimmer *dim, byte value) {
  dim->value = value;
  switch (dim->method) {
    case 0:
      analogWrite(dim->pin, value * brightness / 100);
      break;
    case 1:
      Wire.beginTransmission(remoteAddress);
      Wire.write(dim->pin);
      Wire.write(value * brightness / 100);
      Wire.endTransmission();
      break;
  }
}

void forceDimmers() {
  for (byte i = 0; i < dimmerCount; i++) {
    setLevel(&dimmers[i], dimmers[i].value);
  }
}

/**
   Controls the special functions for dimmers. If forceAll is true, it will update the output of all of the enabled dimmers, even if they have no functions applied.
*/
void runDimmers(boolean forceAll) {
  for (byte i = 0; i < dimmerCount; i++) {
      switch (dimmers[i].function) {
        case 0:
          if (forceAll) {
            setLevel(&dimmers[i], dimmers[i].value);
          }
          break;
        case 1:
          //A fading function. data[0] is the final value, data[1] is the step size, and data[2] is the tick skip (runs every data[2] + 1 ticks, so 0 runs on every tick, 1 every other tick, and so on...)
          if (dimmers[i].data[2] == dimmers[i].data[3]) {
            dimmers[i].data[3] = 0;

            if (abs(dimmers[i].data[0] - dimmers[i].value) < dimmers[i].data[1]) {
              setLevel(&dimmers[i], dimmers[i].data[0]);
              dimmers[i].function = 0;
              dimmers[i].data[0] = 0;
              dimmers[i].data[1] = 0;
              dimmers[i].data[2] = 0;
            } else {
              if (dimmers[i].data[0] > dimmers[i].value) {
                setLevel(&dimmers[i], dimmers[i].value + dimmers[i].data[1]);
              } else {
                setLevel(&dimmers[i], dimmers[i].value - dimmers[i].data[1]);
              }
            }

          } else {
            dimmers[i].data[3]++;
          }
          break;
        case 2:
          //Alternate between two states (strobe). data[0] is up ticks, data[1] is down ticks, data[2] is up value, data[3] is down value

          if (dimmers[i].data[4] == 0) {
            //Meaning that the function was just applied
            setLevel(&dimmers[i], dimmers[i].data[2]);
            dimmers[i].data[4] = dimmers[i].data[0];
          } else if (dimmers[i].value == dimmers[i].data[2]) {
            //The dimmer is currently up
            dimmers[i].data[4]--;
            if (dimmers[i].data[4] == 0) {
              //Time to switch
              setLevel(&dimmers[i], dimmers[i].data[3]);
              dimmers[i].data[4] = dimmers[i].data[1];
            }
          } else if (dimmers[i].value == dimmers[i].data[3]) {
            //The dimmer is currently down
            dimmers[i].data[4]--;
            if (dimmers[i].data[4] == 0) {
              setLevel(&dimmers[i], dimmers[i]. data[2]);
              dimmers[i].data[4] = dimmers[i].data[0];
            }
          } else {
            //Something else changed the value. Instead of breaking, just restart the process
            dimmers[i].data[4] = 0;
          }


          break;
        case 3:
          //Sequence. data[0] on value, data[1] exit value, data[2] on time, data[3] is next in sequence + 1, since data[3] = 0 means stop
          if (dimmers[i].data[4] == 0) {
            dimmers[i].data[4] = dimmers[i].data[2];
          }
          if (dimmers[i].value != dimmers[i].data[0]) {
            setLevel(&dimmers[i], dimmers[i].data[0]);
          }
          if (dimmers[i].data[2] == 0) {
            dimmers[i].data[2] = dimmers[i].data[4];
            setLevel(&dimmers[i], dimmers[i].data[1]);
            dimmers[i].function = 0;
            if (dimmers[i].data[3] != 0) {
              dimmers[dimmers[i].data[3] - 1].function = 3;
            }
          } else {
            dimmers[i].data[2]--;
          }

          break;
        case 4:
          //Flicker and return. data[0] is value, data[1] is time
          if (dimmers[i].data[3] == 0) {
            //Was just set
            dimmers[i].data[2] = dimmers[i].value;
            dimmers[i].data[3] = 1;
          }
          if (dimmers[i].value != dimmers[i].data[0]);
          setLevel(&dimmers[i], dimmers[i].data[0]);
          if (dimmers[i].data[1] == 0) {
            setLevel(&dimmers[i], dimmers[i].data[2]);
            dimmers[i].function = 0;
          } else {
            dimmers[i].data[1]--;
          }
          break;
      }
    
  }
}
