
#include <Arduino.h>

#include <Wire.h>


#include <U8g2lib.h>

#define MAX_CHARS_PER_LINE 12

//U8G2_R0  No rotation, landscape
//U8G2_R1 90 degree clockwise rotation
//U8G2_R2 180 degree clockwise rotation
//U8G2_R3 270 degree clockwise rotation
U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr1(U8G2_R1, /* clock=*/ D1, /* data=*/ D2, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr2(U8G2_R1, /* clock=*/ D1, /* data=*/ D3, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
U8G2_SSD1306_128X64_NONAME_1_SW_I2C scr3(U8G2_R1, /* clock=*/ D1, /* data=*/ D4, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

int lineHeigth = 14;

int currentPatchRequest = 0;
int currentRenderedPatchTitle = 1;
int currentRenderedPatch = 1;

unsigned long lastRenderedPatchTitle = 0;
unsigned long lastRenderedPatch = 0;

int renderPatchDelay = 1500;

int tolerance = 3;
String patchLetter = "";


bool welcome = true;

////////////////////////////////////////////////
// rotary encoder
// without interrupts because it seems to be not compatible with multiple oled stuff
//
// number of encoders
int numEnc = 1;
int encPinA[2] = {D5};
int encPinB[2] = {D6};
int lastModeA[2];
int lastModeB[2];
int curModeA[2];
int curModeB[2];
int encPos[2];
int encPosLast[2];
int change = 0;
int c = 0;
int debounceMilliseconds = 300;
unsigned long lastEncoderChange = 0;
////////////////////////////////////////////////



void setup(void) {
  setupEncoder();
  setupOledDisplays();
  
  setupMidiStuff();
  pinMode(D7, INPUT_PULLUP);
  
  drawScreen(scr1, 1, "4.22", "Disting", "MK4", "", "Arduino", "Labels", "Extension");
  //drawScreen(scr2, 2, "Expert", "Sleepers", "", "disting", "mk4", "");
  //drawScreen(scr3, 3, "firmware", "4.20", "", "", "", "");
}

byte stateButtuon = LOW;
void loop(void) {
  loopEncoder();
  loopPatchSelection();
  midiStuffLoop();

  // TODO: use push function of the encoder for really switching algorithm
  //if (digitalRead(D7) == HIGH) {
  //  Serial.println("button pressed");
  //}

  
}
