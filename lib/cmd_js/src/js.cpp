#include <Arduino.h>
#include "SPIFFS.h"
#include "ESP-QuickJS.h"

#include "js.h"

void JSCommand::cmd(String argv[10]) {
  String path = argv[1];
  if (path == "") {
    path = "/repl.js";
  }

  File file = SPIFFS.open(path, FILE_READ);

  String file_read = file.readString();
  const char* file_read_char = file_read.c_str();

  ESP32QuickJS qjs;
  qjs.begin();
  qjs.exec(file_read_char);
}