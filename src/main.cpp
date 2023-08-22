#include <Arduino.h>
#include "SPIFFS.h"

#include "strfun.h"

// Commands
#include "echo.h"
#include "kilo.h"
#include "cat.h"
#include "js.h"
#include "ls.h"

#define SERIAL_TIMEOUT 10
bool has_core_init = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("device_tree: CPU");
  Serial.println("espOS-v0.0.1 is starting...");
  Serial.setTimeout(SERIAL_TIMEOUT);
  
  bool fs_starter = SPIFFS.begin();
  if (!fs_starter) {
    Serial.println("ERROR: Filesystem failed to mount. Power cycling board...");
    delay(1000);
    esp_restart();
  }

  has_core_init = true;
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Yes, this probably eats ram for breakfast, lunch, and dinner. I currently do not care.
  Serial.print("$ ");

  String argv[10];
  
  for (int i = 0; i < 10; i++) {
    argv[i] = Strfun::read_loopy_suboptimal(true, " ");

    if (argv[i].endsWith("\n")) {
      argv[i].replace("\r\n", "");
      argv[i].replace(" ", "");
      break;
    } else if (argv[i].endsWith(" ") && i == 9) {
      Serial.println("\nWARNING: You have reached the argument limit. Go back to Twitter.");
    }

    argv[i].replace(" ", "");
  }

  if (argv[0] == "echo") {
    EchoCommand::cmd(argv);
  } else if (argv[0] == "quickjs" || argv[0] == "qjs" || argv[0] == "js") {
    JSCommand::cmd(argv);
  } else if (argv[0] == "ls") {
    LSCommand::cmd(argv);
  } else if (argv[0] == "reset" || argv[0] == "reboot") {
    Serial.println("Rebooting...");
    esp_restart();
  } else if (argv[0] == "kilo") {
    KiloCommand::cmd(argv);
  } else if (argv[0] == "cat") {
    CatCommand::cmd(argv);
  } else {
    Serial.println("Command not found");
  }
}