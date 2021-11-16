
void decrementEncoder(int encoderIndex) {
  encPos[encoderIndex]--;
  if (encPos[encoderIndex] < 0) {
    encPos[encoderIndex] = numPatches * tolerance - 1;
  }
}

void incrementEncoder(int encoderIndex) {
  encPos[encoderIndex]++;
  if (encPos[encoderIndex] >= numPatches * tolerance) {
    encPos[encoderIndex] = 0;
  }
}



void setupEncoder() {
  // set up each encoder's values
  for (c = 0; c < numEnc; c++) {

    // set the pins form INPUT
    pinMode(encPinA[c], INPUT);
    pinMode(encPinB[c], INPUT);
    // set the modes and positions - on first read, it may change position once
    //   depending on how the encoders are sitting (having a HIGH position that
    //   gets compared to the initial LOW setting here in the first iteration of
    //   the loop).
    lastModeA[c] = LOW;
    lastModeB[c] = LOW;
    curModeA[c] = LOW;
    curModeB[c] = LOW;
    encPos[c] = 0;
    encPosLast[c] = 0;
  }
}

void loopEncoder () {
  // read in current values
  // set the change variable to 0.  If there is an encoder position change,
  //   this gets changed to 1.  This lets a later portion of the loop that
  //   a change has been made and it doesn't have to compare all the modes
  //   again.
  change = 0;
  // loop through each of the encoders
  for (c = 0; c < numEnc; c++) {
    // read the current state of the current encoder's pins
    curModeA[c] = digitalRead(encPinA[c]);
    curModeB[c] = digitalRead(encPinB[c]);
    // compare the four possible states to figure out what has happened
    //   then encrement/decrement the current encoder's position
    if (curModeA[c] != lastModeA[c]) {
      if (curModeA[c] == LOW) {
        if (curModeB[c] == LOW) {
          //encPos[c]--;
          decrementEncoder(c);
        } else {
          //encPos[c]++;
          incrementEncoder(c);
        }
      } else {
        if (curModeB[c] == LOW) {
          //encPos[c]++;
          incrementEncoder(c);
        } else {
          //encPos[c]--;
          decrementEncoder(c);
        }
      }
    }
    if (curModeB[c] != lastModeB[c]) {
      if (curModeB[c] == LOW) {
        if (curModeA[c] == LOW) {
          //encPos[c]++;
          incrementEncoder(c);
        } else {
          //encPos[c]--;
          decrementEncoder(c);
        }
      } else {
        if (curModeA[c] == LOW) {
          //encPos[c]--;
          decrementEncoder(c);
        } else {
          //encPos[c]++;
          incrementEncoder(c);
        }
      }
    }
    // set the current pin modes (HIGH/LOW) to be the last know pin modes
    //   for the next loop to compare to
    lastModeA[c] = curModeA[c];
    lastModeB[c] = curModeB[c];
    // if this encoder's position changed, flag the change variable so we
    //   know about it later
    if (encPos[c] != encPosLast[c]) {
      change = 1;
    }
  }

  if (change == 1 && millis() - lastEncoderChange > debounceMilliseconds) {
    lastEncoderChange = millis();
    // if an encoder has changed, do something with that information
    // here, I am just going to print all the encoder's positions
    //   if any of them change
    for (c = 0; c < numEnc; c++) {
      getCurrentPatchIndex();
      encPosLast[c] = encPos[c];
    }
    //Serial.println();
    // debounce - if there has been a change, wait for a bit (so to speak) to let the
    //   bounces settle - change to your liking
    //delay(200);
  }
}
