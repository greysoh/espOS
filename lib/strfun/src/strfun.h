#include <Arduino.h>

class Strfun {
  public:
    static String read_loopy(bool should_echo, String delimiter = "\n");
    static String read_loopy_suboptimal(bool should_echo, String delimiter = "\n");   
};