#include <Arduino.h>
#include "functions.h"



ControlSignal moveCONTROL(int error, int control_pin) {
    // Turns based on input error signal
    // 2000us pulse (servo.write([pulse_length])) goes to furthest right postion
    // 1000us pulse is far left position
    // 1500us pulse is middle position
     ControlSignal c;
        if (error > 0){
        c.controlValue = 2000;   
        c.direction = "RIGHT";
    }
        else {
        c.controlValue = 500;
        c.direction = "LEFT";
    }

    return(c);   
}
