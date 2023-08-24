#include <Arduino.h>
#include "SPIFFS.h"

#include "tusbdrive.h"
#include "strfun.h"

void downgrade_conn() {
  Serial.flush();
  Serial.end();
  Serial.begin(115200);
}

bool exists(String path) {
  File f = SPIFFS.open(path);
  return (f == true);// && f.isDirectory();
}

void TinyUSBCommand::cmd(String argv[10]) {
  bool hasBitten = false;
  
  while (true) {
    if (Serial.available()) {
      String readData = Strfun::read_loopy(false, "\n");
      
      if (readData == "BITE") {
        hasBitten = true;
          
        // Upgrade connection to 921600 baud
        //Serial.flush();
        //Serial.end(); 
        //Serial.begin(921600);
          
        continue;
      } else if (readData.startsWith("list")) {
        String directoryItem = readData.substring(readData.indexOf(" ") + 1);
        if (!exists(directoryItem)) {
          Serial.println("ERROR ENOTFOUND");
          
          continue;
        }

        File root = SPIFFS.open(directoryItem);
        File file = root.openNextFile();

        while (file) {
          Serial.print("LIST ");
          Serial.println(file.name());
          file = root.openNextFile();
        }
      } else if (readData.startsWith("read")) {
        String directoryItem = readData.substring(readData.indexOf(" ") + 1);
        if (!exists(directoryItem)) {
          Serial.println("ERROR ENOTFOUND");     
          continue;
        }

        File file = SPIFFS.open(directoryItem);
        
        // We do a little reading
        uint8_t buffer[1];
        Serial.print("SIZE ");
        Serial.println(file.size());
        delay(1000); // Allow for processing delays

        while (file.available()) {
          file.read(buffer, 1);

          Serial.print(buffer[0]);
          Serial.print(" ");
        }

        // FIXME: Apparently freeing the buffer crashes my code. :/
        //free(buffer);
        Serial.println("DONE");
      }
    }

    if (!hasBitten) {
      Serial.println("device_tree: STORAGE_CPU");
      delay(900);
    }

    delay(100);
  }
}