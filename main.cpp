
#include <Arduino.h>
#include <ESP32Servo.h>
#include <functions.h>

#define CONTROL_YAW   3     // Pin to contrl the yaw angle
#define CONTROL_PITCH 4     // Pin to control the pitch angle
#define CONTROL_RESET 7     // Pin to set position back to center


Servo servoYAW;
Servo servoPITCH;



void setup() {
    Serial.begin(9600);
    servoYAW.setPeriodHertz(50);      // MG90S needs 50Hz
    servoYAW.attach(CONTROL_YAW, 500, 2200);   // Pulse range for MG90S
    servoYAW.write(90);               // Middle position
    servoPITCH.setPeriodHertz(50);      // MG90S needs 50Hz
    servoPITCH.attach(CONTROL_PITCH, 500, 2200);   // Pulse range for MG90S
    servoPITCH.write(90);               // Middle position  
}



int error = 1;
int controlDIR;
int reset;
int direction;
ControlSignal ctr;

void loop() {

    reset = digitalRead(CONTROL_RESET);

    if (reset) {
        ctr.controlValue = 1000;
        ctr.direction = "MIDDLE";
    }
    else {
        ctr = moveCONTROL(error, CONTROL_YAW);
    }

    error *= -1;
    Serial.printf("Position: %s | Control Signal: %d | Reset: %d |\n", 
    ctr.direction, ctr.controlValue, reset);
    servoYAW.write(ctr.controlValue);                   
    delay(1000); 

}