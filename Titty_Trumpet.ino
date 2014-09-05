#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <CapacitiveSensor.h>

SdFat sd;
SFEMP3Shield MP3player;

CapacitiveSensor   c1  = CapacitiveSensor(A0,A3); // 2
CapacitiveSensor   c2  = CapacitiveSensor(A1,A4); // 1
CapacitiveSensor   c3  = CapacitiveSensor(A2,A5); // 3

void setup() { 
  Serial.begin(9600);
  

  //Read the SD Card
  sd.begin(SD_SEL, SPI_HALF_SPEED);

  //Start MP3 Play
  MP3player.begin();
  
  // Set playback volume
  MP3player.setVolume(0, 0);
}

void loop() {
  
  // Read signal
  long start = millis();
  long total1 =  c1.capacitiveSensor(20); // GREEN
  long total2 =  c2.capacitiveSensor(20); // BLUE
  long total3 =  c3.capacitiveSensor(20); // BROWN
  
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing 
    
  Serial.print(total1);
  Serial.print("\t");
  Serial.print(total2);
  Serial.print("\t");
  Serial.println(total3);

  // If signal is higher than set range then play track
  if(total1 > 600) {
    //If a track is playing stop it
    if (MP3player.isPlaying()) MP3player.stopTrack();
    //Play track001.mp3 from SD card
    MP3player.playTrack(1);
    reset();
  } else 
  
  if (total2 > 600) {
    if (MP3player.isPlaying()) MP3player.stopTrack();
    MP3player.playTrack(2);
    reset();
  } else
 
  if (total3 > 600) {
    if (MP3player.isPlaying()) MP3player.stopTrack();
    MP3player.playTrack(3);
    reset();
  }

  delay(150);  
}


void reset() {
  c1.reset_CS_AutoCal();
  c2.reset_CS_AutoCal();
  c3.reset_CS_AutoCal();
}
