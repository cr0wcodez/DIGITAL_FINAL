#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform3;  //xy=301,342
AudioSynthWaveform waveform5;  //xy=301,446
AudioSynthWaveform waveform4;  //xy=302,394
AudioSynthWaveform waveform6;  //xy=302,497
AudioSynthWaveform waveform8;  //xy=302,605
AudioSynthWaveform waveform2;  //xy=305,284
AudioSynthWaveform waveform1;  //xy=306,226
AudioSynthWaveform waveform7;  //xy=307,548
AudioMixer4 mixer1;            //xy=584,307
AudioMixer4 mixer2;            //xy=613,485
AudioMixer4 mixer3;            //xy=771,362
AudioOutputI2S i2s1;           //xy=978,335
AudioConnection patchCord1(waveform3, 0, mixer1, 2);
AudioConnection patchCord2(waveform5, 0, mixer2, 0);
AudioConnection patchCord3(waveform4, 0, mixer1, 3);
AudioConnection patchCord4(waveform6, 0, mixer2, 1);
AudioConnection patchCord5(waveform8, 0, mixer2, 3);
AudioConnection patchCord6(waveform2, 0, mixer1, 1);
AudioConnection patchCord7(waveform1, 0, mixer1, 0);
AudioConnection patchCord8(waveform7, 0, mixer2, 2);
AudioConnection patchCord9(mixer1, 0, mixer3, 0);
AudioConnection patchCord10(mixer2, 0, mixer3, 1);
AudioConnection patchCord11(mixer3, 0, i2s1, 0);
AudioConnection patchCord12(mixer3, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=893,572
// GUItool: end automatically generated code

AudioSynthWaveform* oscillators[4] = { &waveform1, &waveform2, &waveform3, &waveform4 };

// int intervalsLydianScale[8] = {0, 2, 4, 6, 7, 9, 11, 12};
// int intervalsMajorScale[8] = {0, 2, 4, 5, 7, 9, 11, 12};
// int intervalsMixoScale[8] = {0, 2, 4, 5, 7, 9, 10, 12};
// int intervalsDorianScale[8] = {0, 2, 3, 5, 7, 9, 10, 12};
// int intervalsMinorScale[8] = {0, 2, 3, 5, 7, 8, 10, 12};
// int intervalsPhrygianScale[8] = {0, 1, 3, 5, 7, 8, 10, 12};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int scale = 0;
int allScales[6][8] = { { 0, 2, 4, 6, 7, 9, 11, 12 },
                        { 0, 2, 4, 5, 7, 9, 11, 12 },
                        { 0, 2, 4, 5, 7, 9, 10, 12 },
                        { 0, 2, 3, 5, 7, 9, 10, 12 },
                        { 0, 2, 3, 5, 7, 8, 10, 12 },
                        { 0, 1, 3, 5, 7, 8, 10, 12 } };


int allScalesFreqs[6][8] = { {}          }




float gains[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

int chords[4][5] = { { 0, 2, 4, 6, 7},
                     { 1, 3, 5, 6, 7},
                     { 2, 4, 5, 6, 7 },
                     { 3, 5, 6, 7, 6 } };

int notesInChord = 3;
int maxNotesInChord = 4;
float startingNoteFreq = 261.0;

int gainControlMaster = A14;
float gain = 0.0;


float semitonesUpOrDown = 0.0;

int chooseScale = A15;


int chordLength = A16;
int chordArp = 0;


int numNotesToPlay = 0;
int temp = A0;

int delayPot = A17;
int delayTime = 0;


float rootFreqs = { 261.63 , 277.18, 293.67 , 311.13, 329.63, 349.23, 369.99, 392.0, 415.30, 440.0, 466.16, 493.88};

void setup() {
  // need these
  Serial.begin(9600);

  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);


  mixer1.gain(0, .1);
  mixer1.gain(1, .1);
  mixer1.gain(2, .1);
  mixer1.gain(3, .1);
  mixer2.gain(0, .1);
  mixer2.gain(1, .1);
  mixer2.gain(2, .1);
  mixer2.gain(3, .1);
}


void loop() {

  gain = analogRead(gainControlMaster) / 1023.0 * 0.7;
  Serial.println(gain);
  sgtl5000_1.volume(gain);

  scale = map(analogRead(chooseScale), 0, 1023, 0, 5);

  chordArp = map(analogRead(chordLength), 0, 1023, 0, 4);


  delayTime = map(analogRead(delayPot), 0, 1028, 0, 2510);


  numNotesToPlay = map(analogRead(temp), 0, 1023, 0, 8);
  for (int i = 0; i < 8; i++) {
    if (i <= numNotesToPlay) {
      gains[i] = 0.1;
      delay(50);
    } else {
      gains[i] = 0.0;
    }
  }

  // int allScales[6][8] = { { 0, 2, 4, 6, 7, 9, 11, 12 },
  //                       { 0, 2, 4, 5, 7, 9, 11, 12 },
  //                       { 0, 2, 4, 5, 7, 9, 10, 12 },
  //                       { 0, 2, 3, 5, 7, 9, 10, 12 },
  //                       { 0, 2, 3, 5, 7, 8, 10, 12 },
  //                       { 0, 1, 3, 5, 7, 8, 10, 12 } };


  playChord(chords[0][0], 0, 0);
  delay(delayTime);
  playChord(chords[0][1], 0, 1);
  delay(delayTime);
  playChord(chords[0][2], 0, 2);
  delay(delayTime);
  playChord(chords[0][3], 0, 3);
  delay(delayTime);


  // turn on all the oscillators so we can hear them all
  for (int i = 0; i < 4; i++) {
    if (i < 4) {
      gains[i] = 0.1;
    } else {
      gains[i] = 0.0;
    }
  }

  oscillators[0]->amplitude(gains[0]);
  oscillators[1]->amplitude(gains[1]);
  oscillators[2]->amplitude(gains[2]);
  oscillators[3]->amplitude(gains[3]);
}

void playChord(float _rootNoteFreq, int _scale, int _chord) {
  // Serial.printf("rootNoteFreq: %d, scale: %d, chord: %d\n", _rootNoteFreq, _scale, _chord);




void happySong() {

  
}








//   for (int i = 0; i < maxNotesInChord; i++) {

//     oscillators[i]->frequency(getFreqFromRoot(_rootNoteFreq, allScales[_scale][chords[_chord][i]]));
//   }
// }

// float getFreqFromRoot(float root, float semitonesUpOrDown) {
//   return root * pow(2, (semitonesUpOrDown / 12.0));
// }


// waveform1.begin(.3, newRoot + shift, WAVEFORM_SINE);
// // waveform2.begin(.3, newSecond + shift, WAVEFORM_SINE);
// waveform3.begin(.3, newThird + shift, WAVEFORM_SINE);
// // waveform4.begin(.3, newFourth + shift, WAVEFORM_SINE);
// waveform5.begin(.3, newFifth + shift, WAVEFORM_SINE);
// // waveform6.begin(.3, newSixth + shift, WAVEFORM_SINE);
// waveform7.begin(.3, newSeventh + shift, WAVEFORM_SINE);
// waveform8.begin(.3, newOctave + shift, WAVEFORM_SINE);

// delay(delayTime);

// waveform1.begin(0, newRoot + shift, WAVEFORM_SINE);
// // waveform2.begin(.3, newSecond + shift, WAVEFORM_SINE);
// waveform3.begin(0, newThird + shift, WAVEFORM_SINE);
// // waveform4.begin(.3, newFourth + shift, WAVEFORM_SINE);
// waveform5.begin(0, newFifth + shift, WAVEFORM_SINE);
// // waveform6.begin(.3, newSixth + shift, WAVEFORM_SINE);
// waveform7.begin(0, newSeventh + shift, WAVEFORM_SINE);
// waveform8.begin(0, newOctave + shift, WAVEFORM_SINE);


// delay(delayTime);

// waveform1.begin(.3, newRoot + shift, WAVEFORM_SINE);
// waveform2.begin(.3, newSecond + shift, WAVEFORM_SINE);
// // waveform3.begin(.3, newThird + shift, WAVEFORM_SINE);
// waveform4.begin(.3, newFourth + shift, WAVEFORM_SINE);
// // waveform5.begin(.3, newFifth + shift , WAVEFORM_SINE);
// waveform6.begin(.3, newSixth + shift, WAVEFORM_SINE);
// // waveform7.begin(.3, newSeventh + shift, WAVEFORM_SINE);
// waveform8.begin(.3, newOctave + shift, WAVEFORM_SINE);

// delay(delayTime);

// waveform1.begin(0, newRoot + shift, WAVEFORM_SINE);
// waveform2.begin(0, newSecond + shift, WAVEFORM_SINE);
// // waveform3.begin(.3, newThird + shift, WAVEFORM_SINE);
// waveform4.begin(0, newFourth + shift, WAVEFORM_SINE);
// // waveform5.begin(.3, newFifth + shift , WAVEFORM_SINE);
// waveform6.begin(0, newSixth + shift, WAVEFORM_SINE);
// // waveform7.begin(.3, newSeventh + shift, WAVEFORM_SINE);
// waveform8.begin(0, newOctave + shift, WAVEFORM_SINE);

// delay(delayTime);


// idk what this is down here im not using it tho

// waveform1.begin(.3, allScales[scale][0] , WAVEFORM_SINE);
// waveform2.begin(.3, allScales[scale][1] , WAVEFORM_SINE);
// waveform3.begin(.3, allScales[scale][2] , WAVEFORM_SINE);
// waveform4.begin(.3, allScales[scale][3] , WAVEFORM_SINE);
// waveform5.begin(.3, allScales[scale][4] , WAVEFORM_SINE);
// waveform6.begin(.3, allScales[scale][5] , WAVEFORM_SINE);
// waveform7.begin(.3, allScales[scale][6] , WAVEFORM_SINE);
// waveform8.begin(.3, allScales[scale][7] , WAVEFORM_SINE);

// what is this

// waveform1.begin(WAVEFORM_SINE);
// waveform1.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
// waveform1.frequency(freq1);

// waveform2.begin(WAVEFORM_SINE);
// waveform2.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
// waveform2.frequency(freq2);

// waveform3.begin(WAVEFORM_SINE);
// waveform3.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
// waveform3.frequency(freq3);