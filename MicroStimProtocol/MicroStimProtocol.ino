/*
  author: Sebastian Barrientos
  Protocol to send pulses to the stimulator MultiChannel.
  HFS and LFS protocol are taken from Picconi et al, 2003.

  Arduino can receive serial messages from C# to trigger the routines.

*/

#include <Arduino.h>
int pins[6] = {7, 8, 9, 10, 11, 13};
int nPins = sizeof(pins);

char procedure;// Procedure code
int Freq; // Frequency of the stimulation train
int Duration; // For how long we stimulate
char Hemi; // Hemisphere
int Structure;

int stimElectrode;
int nPulses;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  for (int ix = 0; ix < nPins ; ix++) {
    pinMode(pins[ix], OUTPUT);
  }
}

void loop() {
  //Arduino will receive a message in the format: $+(Procedure Code [int])+$+(Freq [int])+$(Duration [int])+(l or r)+(structure ID)
  while (Serial.read() != '$') ;  // Wait for $
  procedure = Serial.parseInt();// Procedure code
  Freq = Serial.parseInt(); // Frequency of the stimulation train
  Duration = Serial.parseInt(); // For how long we stimulate
  Hemi = Serial.parseInt(); // Hemisphere IDX
  Structure = Serial.parseInt();

  //check stim pins:
  if (Hemi == 1) {
    if (Structure == 1) {
      stimElectrode = pins[0];
    }
    else if (Structure == 2) {
      stimElectrode = pins[1];
    }
    else if (Structure == 3) {
      stimElectrode = pins[2];
    }else{
      break; //no output
    }
  } else if (Hemi == 2){
    if (Structure == 1) {
      stimElectrode = pins[3];
    }
    else if (Structure == 2) {
      stimElectrode = pins[4];
    }
    else if (Structure == 3) {
      stimElectrode = pins[5];
    }else{
      break;//no output
    }
  }else{
    break; //no output
  }

  //Select stim procedure
  if (procedure == 0) {
    Probing(Freq, Duration);
  }
  else if (procedure == 1) {
    HFS(Freq, Duration, stimElectrode);
  }
  else if (procedure == 2) {
    LFS(Freq, Duration, stimElectrode);
  }else{
    break;
  }
}

void Probing(int xFreq, int xDuration)
{
  nPulses = xDuration/xFreq;
  float ISI = (1/xFreq)/nPins;

  //Loop for each pin
  int pinArray[6] = {pins[0],pins[1],pins[2],pins[3],pins[4],pins[5]}; //fix the order depending on the desired series
  for (int ix = 0; ix <= nPulses; ix++) {
    digitalWrite(pinArray[ix], 'HIGH');
    delay(ISI-5);
    digitalWrite(pinArray[ix], 'LOW');
    delay(5);
  }
}

//3 trains, 3sec duration, 100Hz, 20sec interval
void HFS(int xFreq, int xDuration, int xstimElectrode)
{
  int trainDuration = 3; //sec
  int trainInterval = 20;//sec
  int rounds = xDuration/trainInterval;
  nPulses = trainDuration/xFreq;
  float ISI = (1/xFreq);

  for (int k = 0; k <= rounds; k++){
    for (int ix = 0; ix <= nPulses; ix++) {
      digitalWrite(xstimElectrode, 'HIGH');
      delay(ISI-5);
      digitalWrite(xstimElectrode, 'LOW');
      delay(5);
    }
    delay(trainInterval);
  }
}

//10 min, 2Hz
void LFS(int xFreq, int xDuration, int xstimElectrode)
{
  nPulses = xDuration/xFreq;
  float ISI = (1/xFreq);

  for (int ix = 0; ix <= nPulses; ix++) {
    digitalWrite(xstimElectrode, 'HIGH');
    delay(ISI-5);
    digitalWrite(xstimElectrode, 'LOW');
    delay(5);
  }

}
