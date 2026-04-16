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

// int intervalsLydianScale[8] = {0, 2, 4, 6, 7, 9, 11, 12};
// int intervalsMajorScale[8] = {0, 2, 4, 5, 7, 9, 11, 12};
// int intervalsMixoScale[8] = {0, 2, 4, 5, 7, 9, 10, 12};
// int intervalsDorianScale[8] = {0, 2, 3, 5, 7, 9, 10, 12};
// int intervalsMinorScale[8] = {0, 2, 3, 5, 7, 8, 10, 12};
// int intervalsPhrygianScale[8] = {0, 1, 3, 5, 7, 8, 10, 12};
int scale = 0;
int allScales[6][8] = { { 0, 2, 4, 6, 7, 9, 11, 12 },
                        { 0, 2, 4, 5, 7, 9, 11, 12 },
                        { 0, 2, 4, 5, 7, 9, 10, 12 },
                        { 0, 2, 3, 5, 7, 9, 10, 12 },
                        { 0, 2, 3, 5, 7, 8, 10, 12 },
                        { 0, 1, 3, 5, 7, 8, 10, 12 } };


float gains[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

int gainControlMaster = A14;
float gain = 0.0;

int freqShiftAll = A15;

float freq1 = 262;
float freq2 = 349.23;
float freq3 = 392;

int newRoot = 0;
int newSecond = 0;
int newThird = 0;
int newFourth = 0;
int newFifth = 0;
int newSixth = 0;
int newSeventh = 0;
int newOctave = 0;

// float semitonesUpOrDown = 0.0;

int chooseScale = A16;

int shift = 0;

int numNotesToPlay = 0;
int temp = A17;


void setup() {
  // need these
  Serial.begin(9600);

  AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  // waveform1.begin(WAVEFORM_SINE);
  // waveform1.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  // waveform1.frequency(freq1);

  // waveform2.begin(WAVEFORM_SINE);
  // waveform2.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  // waveform2.frequency(freq2);

  // waveform3.begin(WAVEFORM_SINE);
  // waveform3.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  // waveform3.frequency(freq3);

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

  shift = map(analogRead(freqShiftAll), 0, 1023, 0, 500);
  // Serial.println(freq1, freq2, freq3);

  scale = map(analogRead(chooseScale), 0, 1023, 0, 5);


  newRoot = freq1 * pow(2, (allScales[scale][0]) / 12.0);
  newSecond = freq1 * pow(2, (allScales[scale][1]) / 12.0);
  newThird = freq1 * pow(2, (allScales[scale][2]) / 12.0);
  newFourth = freq1 * pow(2, (allScales[scale][3]) / 12.0);
  newFifth = freq1 * pow(2, (allScales[scale][4]) / 12.0);
  newSixth = freq1 * pow(2, (allScales[scale][5]) / 12.0);
  newSeventh = freq1 * pow(2, (allScales[scale][6]) / 12.0);
  newOctave = freq1 * pow(2, (allScales[scale][7]) / 12.0);

  // waveform1.frequency(newRootNote);
  // waveform2.frequency(newThird);
  // waveform3.frequency(newFifth);
  // waveform4.frequency(newSeventh);


  // waveform1.begin(.3, allScales[scale][0] , WAVEFORM_SINE);
  // waveform2.begin(.3, allScales[scale][1] , WAVEFORM_SINE);
  // waveform3.begin(.3, allScales[scale][2] , WAVEFORM_SINE);
  // waveform4.begin(.3, allScales[scale][3] , WAVEFORM_SINE);
  // waveform5.begin(.3, allScales[scale][4] , WAVEFORM_SINE);
  // waveform6.begin(.3, allScales[scale][5] , WAVEFORM_SINE);
  // waveform7.begin(.3, allScales[scale][6] , WAVEFORM_SINE);
  // waveform8.begin(.3, allScales[scale][7] , WAVEFORM_SINE);
  
 


  numNotesToPlay = map(analogRead(temp), 0, 1023, 0, 8);
  for (int i = 0; i < 8; i++) {
    if (i <= numNotesToPlay) {
      gains[i] = 0.1;
    } else {
      gains[i] = 0.0;
    }
  }
  waveform1.begin(.3, newRoot , WAVEFORM_SINE);
  waveform2.begin(.3, newSecond , WAVEFORM_SINE);
  waveform3.begin(.3, newThird , WAVEFORM_SINE);
  waveform4.begin(.3, newFourth , WAVEFORM_SINE);
  waveform5.begin(.3, newFifth , WAVEFORM_SINE);
  waveform6.begin(.3, newSixth , WAVEFORM_SINE);
  waveform7.begin(.3, newSeventh , WAVEFORM_SINE);
  waveform8.begin(.3, newOctave , WAVEFORM_SINE);

  mixer1.gain(0, gains[0]);
  mixer1.gain(1, gains[1]);
  mixer1.gain(2, gains[2]);
  mixer1.gain(3, gains[3]);
  mixer2.gain(0, gains[4]);
  mixer2.gain(1, gains[5]);
  mixer2.gain(2, gains[6]);
  mixer2.gain(3, gains[7]);



  // semitonesUpOrDown++;
  // if (semitonesUpOrDown >= 8) {
  //   semitonesUpOrDown = 0;
  delay(500);
}
