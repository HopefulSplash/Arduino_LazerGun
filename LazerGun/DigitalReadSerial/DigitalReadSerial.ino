
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SPI.h>
#include <SD.h>



//SD card pin
#define SD_ChipSelectPin 10
//soundplayer object
TMRpcm tmrpcm;


int led = 13;
//pin numbers
int buttonpin = 3;
int lazerpin = 4;
int buttonpin2 = 5;
int motorPin = 6;
int motorPin2 = 7;

//other values
int t = 0;
int val;
int val2;
int ammoUsed = 0;
int prestate = 0;
int prestate2 = 1;
int canReload = 0;

void setup()
{
  //pin modes
  pinMode(led, OUTPUT);
  pinMode(lazerpin, OUTPUT);
  pinMode(buttonpin, INPUT);
  pinMode(buttonpin2, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin))
  {
    return;
  }
  else {
    //setup sound
    tmrpcm.speakerPin = 9;
    tmrpcm.quality(1);
    tmrpcm.setVolume(5);
    //play setup sound (user knows the gun is ready)
    playSound(0);
    tmrpcm.disable();
    tmrpcm.stopPlayback();
  }
}

//method to call sounds depending on the input
void playSound(int t) {
  tmrpcm.disable();
  tmrpcm.stopPlayback();

  if (t == 0) {
    tmrpcm.setVolume(5);
    tmrpcm.play("0.wav");
    delay(2980); //time of clip
  }
  else if (t == 1) {
    tmrpcm.setVolume(6);
    tmrpcm.play("1.wav");
    delay(660); //time of clip
  }
  else if (t == 2) {
    tmrpcm.setVolume(5);
    tmrpcm.play("2.wav");
    delay(950); //time of clip
  }
  else if (t == 3) {
    tmrpcm.setVolume(6);
    tmrpcm.play("3.wav");
    delay(620); //time of clip
  }
  else if (t == 4) {
    tmrpcm.setVolume(5);
    tmrpcm.play("4.wav");
    delay(660); //time of clip
  }

  tmrpcm.disable();
  tmrpcm.stopPlayback();

  return;
}
void loop()
{
  val = digitalRead(buttonpin); // check the state of the button
  val2 = digitalRead(buttonpin2); // check the state of the button

  //reload gun
  if (val2 == HIGH && prestate2 == 0 && canReload == 1)
  {
    //reset ammo and play sound with vibrate
    ammoUsed = 0;
    canReload = 0;
    digitalWrite(motorPin, HIGH); //vibrate
    digitalWrite(motorPin2, HIGH); //vibrate
    playSound(3);
    digitalWrite(motorPin, LOW);  //stop vibrating
    digitalWrite(motorPin2, LOW);  //stop vibrating
    prestate2 = 1;

  }
  else if (val2 == LOW)
  {
    //reload let go
    prestate2 = 0;
  }


  //Shooting the gun 1-4 normal. 5 is louder and longer.
  if (val == LOW) // if button is pressed, turn LED on
  {
    digitalWrite(lazerpin, LOW);
    digitalWrite(led, LOW);
    prestate = 0;
  }
  else if (val == HIGH && prestate == 0)
  {
    if (ammoUsed != 5)
    {
      ammoUsed ++;

      if (ammoUsed > 0) {
        canReload = 1;
      }
      else {
        canReload = 0;
      }


      //turn on lazer and virbate
      digitalWrite(lazerpin, HIGH);
      digitalWrite(led, HIGH);
      digitalWrite(motorPin, HIGH); //vibrate
      digitalWrite(motorPin2, HIGH); //vibrate

      //play sound
      if (ammoUsed == 5) {
        playSound(2);
      }
      else {
        playSound(1);
      }
      //after sound lazer and vibrate turn off
      digitalWrite(motorPin, LOW);  //stop vibrating
      digitalWrite(motorPin2, LOW);  //stop vibrating
      digitalWrite(lazerpin, LOW);
      digitalWrite(led, LOW);

      prestate = 1;
    }
    else {
      //no ammo just vibrate and play sound with no lazer
      digitalWrite(motorPin, HIGH); //vibrate
      digitalWrite(motorPin2, HIGH); //vibrate
      playSound(4);
      canReload = 1;
      digitalWrite(motorPin, LOW);  //stop vibrating
      digitalWrite(motorPin2, LOW);  //stop vibrating
      prestate = 1;

    }
  }

}
