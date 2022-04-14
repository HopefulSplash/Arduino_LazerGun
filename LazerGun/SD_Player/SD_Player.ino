#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SPI.h>
#include <SD.h>


#define SD_ChipSelectPin 10
TMRpcm tmrpcm;
int t = 0;

void setup()
{
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin))
  {
    return;
  }
  else {
    tmrpcm.speakerPin = 9;
    tmrpcm.setVolume(5);
  }

}



void playSound() {
  tmrpcm.stopPlayback();

    if (t == 0) {
      tmrpcm.play("0.wav");
      delay(2980); //time of clip
    }
    else if (t == 1) {
      tmrpcm.play("shot.wav");
      delay(660); //time of clip
    }
    else if (t == 2) {
      tmrpcm.play("2.wav");
      delay(900); //time of clip
    }
    else if (t == 3) {
      tmrpcm.play("reload.wav");
      delay(620); //time of clip
    }
    else if (t == 4) {
      tmrpcm.play("noammo.wav");
      delay(350); //time of clip
    }

  return;
}


void loop() {
  // put your main code here, to run repeatedly:
  playSound(0);

}
