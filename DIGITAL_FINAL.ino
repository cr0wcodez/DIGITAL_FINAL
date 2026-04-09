#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3; //xy=301,342
AudioSynthWaveform       waveform2; //xy=305,284
AudioSynthWaveform       waveform1;      //xy=306,226
AudioMixer4              mixer1;         //xy=532,249
AudioOutputI2S           i2s1;           //xy=743,206
AudioConnection          patchCord1(waveform3, 0, mixer1, 2);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(waveform1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=609,384
// GUItool: end automatically generated code

int gainControlMaster = A13;
float gain = 0.0;

int freqShiftAll = A10;

float freq1 = 262;
float freq2 = 349.23;
float freq3 = 392;

int shift = 0;


void setup() {
// need these
Serial.begin(9600);

AudioMemory(12);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  waveform1.frequency(freq1);

  waveform2.begin(WAVEFORM_SINE);
  waveform2.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  waveform2.frequency(freq2);

  waveform3.begin(WAVEFORM_SINE);
  waveform3.amplitude(0.2);  //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
  waveform3.frequency(freq3);

  mixer1.gain(0,.2);
  mixer1.gain(1,.2);
  mixer1.gain(2,.2);

}

void loop() {

  gain = analogRead(gainControlMaster) / 1023.0 * 0.7;
  Serial.println(gain);
  sgtl5000_1.volume(gain);

  shift = map(analogRead(freqShiftAll), 0, 1023, 0, 500);
  // Serial.println(freq1, freq2, freq3);

  waveform1.frequency(freq1 + shift);
  waveform2.frequency(freq2 + shift);
  waveform3.frequency(freq3 + shift);
  
  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_SINE);
  waveform3.begin(WAVEFORM_SINE);
}
