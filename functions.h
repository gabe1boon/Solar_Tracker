#ifndef FUNCTION_H
#define FUNCTION_H
#include <Arduino.h>

struct ControlSignal {
    String direction;
    int controlValue;
  };

struct SolarOutput {
    float busVoltage_V; 
    float current_mA;
    float power_mW;
    float loadVoltage_V;
  };

void runTest(); // Function you want to call from main.cpp
ControlSignal moveCONTROL(int error, int control_pin, int servo_position, int tick_number);
SolarOutput getMeas();
void startup();

#endif
