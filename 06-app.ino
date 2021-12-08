

void getCurrentPatchIndex() {
  currentPatchRequest = encPos[0]/tolerance;
}

char *getCharsForPatch(int patchNum, int subject, int lineNum) {
  char cur[MAX_CHARS_PER_LINE] = "";
  int useIndex = patchNum*wordsPerPatch + subject*3 + lineNum;
  strcpy(cur, allWords[useIndex]); return cur;
}

void loopPatchSelection() {
  char patch[MAX_CHARS_PER_LINE],
    titleL1[MAX_CHARS_PER_LINE],
    titleL2[MAX_CHARS_PER_LINE],
    titleL3[MAX_CHARS_PER_LINE];

  if (welcome == true) {
    if (millis() > 6000) {
      welcome = false;
      currentPatchRequest = 0;
      lastRenderedPatchTitle = 0;
      lastRenderedPatch = 0;
    }
    return;
  }
  
  if (currentPatchRequest != currentRenderedPatchTitle) {
    strcpy(patch, getCharsForPatch(currentPatchRequest, 0, 0));
    strcpy(titleL1, getCharsForPatch(currentPatchRequest, 1, 0));
    strcpy(titleL2, getCharsForPatch(currentPatchRequest, 1, 1));
    strcpy(titleL3, getCharsForPatch(currentPatchRequest, 1, 2));
    drawPatchName(scr1, 1, patch, titleL1, titleL2, titleL3);
    currentRenderedPatchTitle = currentPatchRequest;
    lastRenderedPatchTitle = millis();
    currentRenderedPatch = -1;
    return;
  }

  // already rendered
  if (currentRenderedPatch == currentPatchRequest) {
    return;
  }

  // wait until delay milliseconds is finished
  if (millis() - lastRenderedPatchTitle < renderPatchDelay ) {
    return;  
  }

  char titleL4[MAX_CHARS_PER_LINE],
    titleL5[MAX_CHARS_PER_LINE],
    titleL6[MAX_CHARS_PER_LINE];
  
  strcpy(patch, getCharsForPatch(currentPatchRequest, 0, 0));
  strcpy(titleL1, getCharsForPatch(currentPatchRequest, 1, 0));
  strcpy(titleL2, getCharsForPatch(currentPatchRequest, 1, 1));
  strcpy(titleL3, getCharsForPatch(currentPatchRequest, 1, 2));
  strcpy(titleL4, getCharsForPatch(currentPatchRequest, 2, 0));
  strcpy(titleL5, getCharsForPatch(currentPatchRequest, 2, 1));
  strcpy(titleL6, getCharsForPatch(currentPatchRequest, 2, 2));
  drawScreen(scr1, 1, patch, titleL1, titleL2, titleL3, titleL4, titleL5, titleL6);
  
  strcpy(titleL1, getCharsForPatch(currentPatchRequest, 3, 0));
  strcpy(titleL2, getCharsForPatch(currentPatchRequest, 3, 1));
  strcpy(titleL3, getCharsForPatch(currentPatchRequest, 3, 2));
  strcpy(titleL4, getCharsForPatch(currentPatchRequest, 4, 0));
  strcpy(titleL5, getCharsForPatch(currentPatchRequest, 4, 1));
  strcpy(titleL6, getCharsForPatch(currentPatchRequest, 4, 2));
  drawScreen(scr2, 2, titleL1, titleL2, titleL3, titleL4, titleL5, titleL6);
  
  strcpy(titleL1, getCharsForPatch(currentPatchRequest, 5, 0));
  strcpy(titleL2, getCharsForPatch(currentPatchRequest, 5, 1));
  strcpy(titleL3, getCharsForPatch(currentPatchRequest, 5, 2));
  strcpy(titleL4, getCharsForPatch(currentPatchRequest, 6, 0));
  strcpy(titleL5, getCharsForPatch(currentPatchRequest, 6, 1));
  strcpy(titleL6, getCharsForPatch(currentPatchRequest, 6, 2));
  drawScreen(scr3, 3, titleL1, titleL2, titleL3, titleL4, titleL5, titleL6);

  currentRenderedPatch = currentPatchRequest;
  lastRenderedPatch = millis();
  sendMidiAlgorithmChange(currentPatchRequest);
  
}
