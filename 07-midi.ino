

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
//#include <SoftwareSerial.h>
//SoftwareSerial softSerial(D7, D8); // RX, TX
//MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

void setupMidiStuff()
{

  //Serial.begin(31250); // MIDI baudrate
  
  //Serial.println("starting serial with debug monitor");
  //Serial.println("MIDI RX/TX pins are 7/8");

  MIDI.begin(MIDI_CHANNEL_OMNI); // Launch MIDI, by default listening to channel 1.
  MIDI.turnThruOff();
  // unfortunately disting mk4 dous not send anything when changing algo
  // @see https://modwiggler.com/forum/viewtopic.php?f=35&t=224887&sid=0d4f1d17d1fd31339dd2832f5ed35092#p3641737
  //MIDI.setHandleProgramChange(handleMidiEventProgramChange);
  //MIDI.setHandleControlChange(handleMidiEventControlChange);
}

void midiStuffLoop() {

  //Serial.begin(31250); // MIDI baudrate
  MIDI.read();
}

/*
void handleMidiEventControlChange(byte inChannel, byte inControlNumber, byte inControlValue) {
  //MIDI.sendControlChange(inControlNumber, inControlValue, inChannel);
  //Serial.print("Received CC #"); Serial.println(inControlNumber);
  //Serial.print("on channel "); Serial.println(inChannel);
  //erial.print("with value "); Serial.println(inControlValue);

}

void handleMidiEventProgramChange(byte inChannel, byte inProgramNumber) {
  Serial.print("Received programm change to "); Serial.println(inProgramNumber);
  Serial.print("on channel "); Serial.println(inChannel);
  incrementEncoder(0);
  //MIDI.sendProgramChange(inProgramNumber, inChannel);
}

*/

// changing algorithm on disting mk4 via CC18
void sendMidiAlgorithmChange(int inProgramNumber) {
  //Serial.println("sending program change ");
  //MIDI.sendProgramChange(inProgramNumber, 1);
  MIDI.sendControlChange(18, inProgramNumber, 1);
}
