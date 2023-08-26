#include <Arduino.h>
#include "loopystresser.h"

void LoopyStressCommand::cmd(String argv[10]) {
  Serial.println("Hello, world!\nThis is a benchmark for the esp32Display code to check how many corruptions occur a second at high speeds.");
  Serial.println("You will have 10 seconds to go into a different mode using espGPUDisplay (the RST prompt).");
  Serial.println("Do NOT reset the board. This code will \"FAKE\" (not really a fake, but meh) a reset. You will wait until it starts.");
  Serial.println("Have fun! Initiating now...");

  for (int i = 0; i < 10; i++) {
    Serial.println("device_tree: LOOPYSTRESSER_CPU");
    delay(1000);
  }

  Serial.println("BEGIN");
  Serial.flush();
  Serial.end(); 
  Serial.begin(921600);

  delay(2000);

  for (int i = 0; i < 60000; i++) {
    Serial.print(i);
    Serial.println(" ABCDEFG012345");
  }

  Serial.println("END");
  delay(15000);
  esp_restart();
}