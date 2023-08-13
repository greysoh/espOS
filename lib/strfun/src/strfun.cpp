#include <Arduino.h>
#include "strfun.h"

String Strfun::read_loopy(bool should_echo, String delimiter /*= "\n" */) {
  String output;
  
  while (true) {
    String current_key = Serial.readString();

    // For validation purposes only.
    // The buffer can effectively be any size because maths.
    byte buffer[current_key.length() + 1];
    current_key.getBytes(buffer, current_key.length() + 1);

    // FIXME: FIX THIS SHIT
    // We should check *all occurences* in the buffer incase the user types fast. But I'm lazy. Sooooooo yup

    if (buffer[0] == 0) continue;
    if (buffer[0] == 8) {
      if (buffer[0] == 8 && output.length() != 0 && should_echo) {
        Serial.write(8);
        Serial.write(32);
        Serial.write(8);
      }
      output.remove(output.length()-1, 1);

      continue;
    }

    if (should_echo) Serial.print(current_key);
    if (current_key.endsWith(delimiter)) break;

    output = output + current_key;
  }

  return output;
}

String Strfun::read_loopy_suboptimal(bool should_echo, String delimiter /*= "\n" */) {
  String output;
  
  while (true) {
    String current_key = Serial.readString();

    // For validation purposes only.
    // The buffer can effectively be any size because maths.
    byte buffer[current_key.length() + 1];
    current_key.getBytes(buffer, current_key.length() + 1);

    // FIXME: FIX THIS SHIT
    // We should check *all occurences* in the buffer incase the user types fast. But I'm lazy. Sooooooo yup

    if (buffer[0] == 0) continue;
    if (buffer[0] == 8) {
      if (buffer[0] == 8 && output.length() != 0 && should_echo) {
        Serial.write(8);
        Serial.write(32);
        Serial.write(8);
      }
      output.remove(output.length()-1, 1);

      continue;
    }

    output = output + current_key;

    if (should_echo) Serial.print(current_key);
    if (current_key.endsWith(delimiter)) break;

    // FIXME: This is a hack.
    if (current_key.endsWith("\n")) break;
  }

  return output;
}