#include <Arduino.h>
#include "echo.h"

void EchoCommand::cmd(String argv[10]) {
  Serial.println(argv[1] + " " + argv[2] + argv[3] + " " + argv[4] + argv[5] + " " + argv[6] + argv[7] + " " + argv[8] + argv[9]); 
}