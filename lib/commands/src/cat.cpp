#include <Arduino.h>
#include "SPIFFS.h"

#include "cat.h"

void CatCommand::cmd(String argv[10]) {
  if (argv[1] == "") {
    Serial.println("error: File not specified!");
    return;
  } 

  File file = SPIFFS.open(argv[1]);
  Serial.print(file.readString());
}