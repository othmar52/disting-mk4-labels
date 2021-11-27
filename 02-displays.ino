


void setupOledDisplays() {
  scr1.begin();
  scr2.begin();
  scr3.begin();
  
  // @see fonts https://arduino-projekte.info/schriftarten-fuer-oled-display/
  scr1.setFont(u8g2_font_crox2h_tf);
  scr2.setFont(u8g2_font_crox2h_tf);
  scr3.setFont(u8g2_font_crox2h_tf);
  
  scr1.setFontMode(0);    // enable transparent mode, which is faster
  scr2.setFontMode(0);    // enable transparent mode, which is faster
  scr3.setFontMode(0);    // enable transparent mode, which is faster

  getTotalEntries();
  // Serial.println(getTotalEntries());
}



// upper half of screen with algorithm letter
void drawJackLabelUpper(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex, char* patch, char* line1, char* line2, char* line3) {
  int offset = lineHeigth+2;
  scr.drawStr(0,offset,patch);
  scr.drawStr(0,offset+lineHeigth,line1);
  scr.drawStr(0,offset+lineHeigth*2,line2);
  scr.drawStr(0,offset+lineHeigth*3,line3);
  drawDivider(scr);
  
}

// horizontal line on screen 1
void drawDivider(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr) {
  scr.drawBox (0, 70, 64, 1); // x,y,w,h
}

// upper half of screen without algorithm letter
void drawJackLabelUpper(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex, char* line1, char* line2, char* line3) {
  uint8_t lineCount = getLineCount(line1, line2, line3);
  int offset = lineHeigth+2;
  if (lineCount == 0) {
    return;  
  }
  if (screenIndex == 2 && lineCount == 2) { offset += lineHeigth; }
  if (screenIndex == 3 && lineCount == 2) { offset -= 0.1*lineHeigth; }
  
  if (screenIndex == 2 && lineCount == 1) { offset += 1.4*lineHeigth; }
  if (screenIndex == 3 && lineCount == 1) { offset += 0.5*lineHeigth; }
  if (screenIndex == 2 && lineCount == 3) { offset = lineHeigth+10; }
  
  scr.drawStr(0,offset,line1);
  if (lineCount == 1) {
    return;  
  }
  scr.drawStr(0,offset+lineHeigth,line2);
  if (lineCount == 2) {
    return;  
  }
  scr.drawStr(0,offset+lineHeigth*2,line3);
}
// lower half of screen
void drawJackLabelLower(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex, char* line1, char* line2, char* line3) {
  uint8_t lineCount = getLineCount(line1, line2, line3);
  int offset = 97;
  if (lineCount == 0) {
    return;  
  }
  if (screenIndex == 3 && lineCount == 3) { offset = 88; }
  if (screenIndex == 1 && lineCount == 1) { offset += 1.5*lineHeigth; }
  if (screenIndex == 2 && lineCount == 1) { offset += lineHeigth; }

  
  if (screenIndex == 1 && lineCount == 2) { offset += 0.9*lineHeigth; }
  if (screenIndex == 2 && lineCount == 2) { offset += 0.5*lineHeigth; }
  if (screenIndex == 3 && lineCount == 2) { offset -= 0.3*lineHeigth; }
  
  scr.drawStr(0,offset,line1);
  if (lineCount == 1) {
    return;  
  }
  scr.drawStr(0,offset+lineHeigth,line2);
  if (lineCount == 2) {
    return;  
  }
  scr.drawStr(0,offset+lineHeigth*2,line3);
}

uint8_t getLineCount(char* line1, char* line2, char* line3) {
  int lineCount = 0;
  if (line1[0] != '\0') {
    lineCount++;
  }
  if (line2[0] != '\0') {
    lineCount++;
  }
  if (line3[0] != '\0') {
    lineCount++;
  }
  return lineCount;
}

void drawPatchName(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex,
                     char* patch, char* line1, char* line2, char* line3) {

  scr.clearBuffer();
  scr.firstPage();
  do {
    drawJackLabelUpper(scr, screenIndex, patch, line1, line2, line3);
    drawDivider(scr);
  } while ( scr.nextPage() );
}

void drawScreen(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex,
                     char* line1, char* line2, char* line3,
                     char* line4, char* line5, char* line6) {
  scr.clearBuffer();
  do {
     drawJackLabelUpper(scr, screenIndex, line1, line2, line3);
     drawJackLabelLower(scr, screenIndex, line4, line5, line6);
  } while ( scr.nextPage() );
}

void drawScreen(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, uint8_t screenIndex,
                     char* patch,
                     char* line1, char* line2, char* line3,
                     char* line4, char* line5, char* line6) {
  scr.clearBuffer();
  scr.firstPage();
  do {
     drawJackLabelUpper(scr, screenIndex, patch, line1, line2, line3);
     drawJackLabelLower(scr, screenIndex, line4, line5, line6);
  } while ( scr.nextPage() );
}
