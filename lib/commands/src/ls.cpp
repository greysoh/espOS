#include <Arduino.h>
#include "SPIFFS.h"

#include "ls.h"

bool in_house_exists(String path) {
  File f = SPIFFS.open(path);
  return (f == true) && f.isDirectory();
}

void LSCommand::cmd(String argv[10]) {
  if (argv[1] == "") {
    Serial.println("error: Folder not specified!");
    return;
  } else if (!in_house_exists(argv[1])) {
    Serial.println("error: Folder not found!");
    return;
  }

  File root = SPIFFS.open(argv[1]);
  File file = root.openNextFile();

  while (file) {
    Serial.println(file.name());
    file = root.openNextFile();
  }
}