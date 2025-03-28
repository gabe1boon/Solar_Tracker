#include "functions.h"



ControlSignal moveCONTROL(int error, int control_pin, int servo_position, int tick_number) {
    // Turns based on input error signal
    // 2000us pulse (servo.write([pulse_length])) goes to furthest right postion
    // 1000us pulse is far left position
    // 1500us pulse is middle position
     ControlSignal c;
        if (error > 0){
        c.controlValue = servo_position - tick_number;   
        c.direction = "RIGHT/DOWN";
    }
        else {
        c.controlValue = servo_position + tick_number;
        c.direction = "LEFT/UP";
    }
    return(c);   
}
