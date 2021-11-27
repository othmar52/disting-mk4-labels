

#include <MIDI.h>


// for debugging purposes use D8 instead of TX pin
//#include <SoftwareSerial.h>
//SoftwareSerial softSerial(D7, D8); // RX, TX
//MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, MIDI);

MIDI_CREATE_DEFAULT_INSTANCE();

void setupMidiStuff()
{
  MIDI.begin(MIDI_CHANNEL_OMNI); // Launch MIDI, by default listening to channel 1.
  MIDI.turnThruOff();
  // unfortunately disting mk4 does not send anything when changing algo
  // @see https://modwiggler.com/forum/viewtopic.php?f=35&t=224887&sid=0d4f1d17d1fd31339dd2832f5ed35092#p3641737
  // so we do not have bidirectional midi communication :/
}

void midiStuffLoop() {
  MIDI.read();
}

// changing algorithm on disting mk4 via CC18
void sendMidiAlgorithmChange(int inProgramNumber) {
  MIDI.sendControlChange(18, inProgramNumber, 1);
}
