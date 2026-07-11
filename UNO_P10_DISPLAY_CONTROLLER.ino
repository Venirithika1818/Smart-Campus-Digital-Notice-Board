#include <SPI.h>
#include <DMD.h>
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
String message = "READY";
unsigned long lastStep = 0;

void setup() {
  Serial.begin(9600);
  dmd.selectFont(SystemFont5x7);
  dmd.clearScreen(true);
  
  dmd.drawMarquee(message.c_str(), message.length(), (32 * DISPLAYS_ACROSS), 0);
}

void loop() {
  dmd.scanDisplayBySPI(); 

  if (Serial.available()) {
    delay(50);
    String incoming = Serial.readString();
    incoming.trim();
    
    if(incoming.length() > 0) {
      message = incoming;
      dmd.clearScreen(true);
      dmd.drawMarquee(message.c_str(), message.length(), (32 * DISPLAYS_ACROSS), 0);
    }
  
  if (millis() - lastStep > 30) { 
    bool reachedEnd = dmd.stepMarquee(-1, 0); 
  
    if (reachedEnd) {
      dmd.drawMarquee(message.c_str(), message.length(), (32 * DISPLAYS_ACROSS), 0);
    }
    lastStep = millis();
  }
}
