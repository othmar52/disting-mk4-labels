


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

  Serial.println(getTotalEntries());
}



// upper half of screen with algorithm letter
void drawJackLabelUpper(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, char* patch, char* line1, char* line2, char* line3) {
  int offset = lineHeigth+2;
  scr.drawStr(0,offset,patch);
  scr.drawStr(0,offset+lineHeigth,line1);
  scr.drawStr(0,offset+lineHeigth*2,line2);
  scr.drawStr(0,offset+lineHeigth*3,line3);
}

// upper half of screen without algorithm letter
void drawJackLabelUpper(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, char* line1, char* line2, char* line3) {
  int offset = lineHeigth+2;
  scr.drawStr(0,offset,line1);
  scr.drawStr(0,offset+lineHeigth,line2);
  scr.drawStr(0,offset+lineHeigth*2,line3);
}
// lower half of screen
void drawJackLabelLower(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr, char* line1, char* line2, char* line3) {
  int offset = 90;
  scr.drawStr(0,offset,line1);
  scr.drawStr(0,offset+lineHeigth,line2);
  scr.drawStr(0,offset+lineHeigth*2,line3);
}

void drawPatchName(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr,
                     char* patch, char* line1, char* line2, char* line3) {

  scr.firstPage();
  do {
    drawJackLabelUpper(scr, patch, line1, line2, line3);
  } while ( scr.nextPage() );
}

void drawScreen(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr,
                     char* line1, char* line2, char* line3,
                     char* line4, char* line5, char* line6) {
  do {
     drawJackLabelUpper(scr, line1, line2, line3);
     drawJackLabelLower(scr, line4, line5, line6);
  } while ( scr.nextPage() );
}

void drawScreen(U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr,
                     char* patch,
                     char* line1, char* line2, char* line3,
                     char* line4, char* line5, char* line6) {
  scr.firstPage();
  do {
     drawJackLabelUpper(scr, patch, line1, line2, line3);
     drawJackLabelLower(scr, line4, line5, line6);
  } while ( scr.nextPage() );
}
