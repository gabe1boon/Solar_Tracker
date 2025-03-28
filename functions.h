#ifndef FUNCTION_H
#define FUNCTION_H

struct ControlSignal {
    String direction;
    int controlValue;
  };

void runTest(); // Function you want to call from main.cpp
ControlSignal moveCONTROL(int error, int control_pin);


#endif
