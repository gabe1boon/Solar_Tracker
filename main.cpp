
#include <Arduino.h>
#include <ESP32Servo.h>
#include <functions.h>

#define CONTROL_YAW   3     // Pin to contrl the yaw angle
#define CONTROL_PITCH 4     // Pin to control the pitch angle
#define CONTROL_RESET 7     // Pin to set position back to center

#define TOP_LEFT_SENSOR A0
#define TOP_RIGHT_SENSOR A1
#define BOTTOM_LEFT_SENSOR A2
#define BOTTOM_RIGHT_SENSOR A3

#define YAW_MIDDLE 1000
#define YAW_RIGHT 1500
#define YAW_LEFT 500

#define PITCH_MIDDLE 90
#define PITCH_DOWN 30
#define PITCH_UP 150

Servo servoYAW;
Servo servoPITCH;

const int TopLMax = 4095;
const int TopRMax = 4095;
const int BottomLMax = 4095;
const int BottomRMax = 4095;
const int TopLMin = 250;
const int TopRMin = 230;
const int BottomLMin = 100;
const int BottomRMin = 70;



inline int fastMap(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

void setup() {
    Serial.begin(9600);
    servoYAW.setPeriodHertz(50);      // MG90S needs 50Hz
    servoYAW.attach(CONTROL_YAW, 500, 2200);   // Pulse range for MG90S
    servoPITCH.setPeriodHertz(50);      // MG90S needs 50Hz
    servoPITCH.attach(CONTROL_PITCH, 500, 2200);   // Pulse range for MG90S
    servoYAW.write(YAW_MIDDLE);
    servoPITCH.write(PITCH_MIDDLE);
    startup();
}



int error = 1;
int controlDIR;
int reset;
int direction;
ControlSignal ctrYAW;
ControlSignal ctrPITCH;
SolarOutput s1;
int sensorValues[4];

int vertError;
int horiError;
int yawPosition = YAW_MIDDLE;
int pitchPosition = PITCH_MIDDLE;

int upperLeftValue;
int upperRightValue;
int lowerLeftValue;
int lowerRightValue;

void loop() {

    s1 = getMeas();
    Serial.print("Bus Voltage [V]: "); Serial.println(s1.busVoltage_V);
    Serial.print("Load Voltage [V]: "); Serial.println(s1.loadVoltage_V);
    Serial.print("Current[mA]: "); Serial.println(s1.current_mA);
    Serial.print("Bus Power [mW]: "); Serial.println(s1.power_mW);

    upperLeftValue = analogRead(TOP_LEFT_SENSOR);
    upperRightValue = analogRead(TOP_RIGHT_SENSOR);
    lowerLeftValue = constrain(analogRead(BOTTOM_LEFT_SENSOR)*2,0,4095);
    lowerRightValue = constrain(analogRead(BOTTOM_RIGHT_SENSOR)*2,0,4095);
    sensorValues[0] = fastMap(upperLeftValue, TopLMin, TopLMax, 0, 1000);
    sensorValues[1] = fastMap(upperRightValue, TopRMin, TopRMax, 0, 1000);
    sensorValues[2] = fastMap(lowerLeftValue, BottomLMin, BottomLMax, 0, 1000);
    sensorValues[3] = fastMap(lowerRightValue, BottomRMin, BottomRMax, 0, 1000);

    vertError = sensorValues[0,1] - sensorValues[2,3];      // TOP - BOTTOM -- +ve when bottom is closer to light
    horiError = sensorValues[0,2] - sensorValues[1,3];      // LEFT - RIGHT -- +ve when right is closer to light

    
    if (reset) {
        ctrYAW.controlValue = YAW_MIDDLE;
        ctrYAW.direction = "MIDDLE";
        ctrPITCH.controlValue = PITCH_MIDDLE;
        ctrPITCH.direction = "MIDDLE";
    }

    else {
        while (abs(vertError) > 80) {
            
            upperLeftValue = analogRead(TOP_LEFT_SENSOR);
            upperRightValue = analogRead(TOP_RIGHT_SENSOR);
            lowerLeftValue = constrain(analogRead(BOTTOM_LEFT_SENSOR)*2,0,4095);
            lowerRightValue = constrain(analogRead(BOTTOM_RIGHT_SENSOR)*2,0,4095);
            sensorValues[0] = fastMap(upperLeftValue, TopLMin, TopLMax, 0, 1000);
            sensorValues[1] = fastMap(upperRightValue, TopRMin, TopRMax, 0, 1000);
            sensorValues[2] = fastMap(lowerLeftValue, BottomLMin, BottomLMax, 0, 1000);
            sensorValues[3] = fastMap(lowerRightValue, BottomRMin, BottomRMax, 0, 1000);
            vertError = sensorValues[0,1] - sensorValues[2,3];      // TOP - BOTTOM -- +ve when bottom is closer to light
            horiError = sensorValues[0,2] - sensorValues[1,3];      // LEFT - RIGHT -- +ve when right is closer to light

            ctrPITCH = moveCONTROL(vertError, CONTROL_PITCH, pitchPosition, 1);
            ctrPITCH.controlValue = constrain(ctrPITCH.controlValue,PITCH_DOWN,PITCH_UP);
            servoPITCH.write(ctrPITCH.controlValue);
            pitchPosition = ctrPITCH.controlValue;
            delay(1000);
            Serial.printf("VERTICAL ERROR: %d | PITCH POSITION: %d | PITCH CONTROL: %d \n",
                vertError, pitchPosition, ctrPITCH.controlValue);
        }

        while (abs(horiError) > 80) {
            servoYAW.setPeriodHertz(50);      // MG90S needs 50Hz
            servoYAW.attach(CONTROL_YAW, 500, 2200);   // Pulse range for MG90S
            upperLeftValue = analogRead(TOP_LEFT_SENSOR);
            upperRightValue = analogRead(TOP_RIGHT_SENSOR);
            lowerLeftValue = constrain(analogRead(BOTTOM_LEFT_SENSOR)*2,0,4095);
            lowerRightValue = constrain(analogRead(BOTTOM_RIGHT_SENSOR)*2,0,4095);
            sensorValues[0] = fastMap(upperLeftValue, TopLMin, TopLMax, 0, 1000);
            sensorValues[1] = fastMap(upperRightValue, TopRMin, TopRMax, 0, 1000);
            sensorValues[2] = fastMap(lowerLeftValue, BottomLMin, BottomLMax, 0, 1000);
            sensorValues[3] = fastMap(lowerRightValue, BottomRMin, BottomRMax, 0, 1000);
            vertError = sensorValues[0,1] - sensorValues[2,3];      // TOP - BOTTOM -- +ve when bottom is closer to light
            horiError = sensorValues[0,2] - sensorValues[1,3];      // LEFT - RIGHT -- +ve when right is closer to light

            ctrYAW = moveCONTROL(horiError, CONTROL_YAW, yawPosition, 10);
            ctrYAW.controlValue = constrain(ctrYAW.controlValue,YAW_LEFT,YAW_RIGHT);
            servoYAW.write(ctrYAW.controlValue);
            yawPosition = ctrYAW.controlValue;
            delay(1000);
            Serial.printf("HORIZONTAL ERROR: %d | YAW POSITION: %d | YAW CONTROL: %d \n",
                horiError, yawPosition, ctrYAW.controlValue);
        }
        pinMode(CONTROL_YAW, OUTPUT);
        digitalWrite(CONTROL_YAW, 0);
    }
    


    
    Serial.printf("TOP LEFT RAW: %d | TOP RIGHT RAW: %d | BOTTOM LEFT RAW: %d | BOTTOM RIGHT RAW: %d |\n", 
        upperLeftValue , upperRightValue , lowerLeftValue  , lowerRightValue);
    Serial.printf("TOP_LEFT: %d | TOP_RIGHT: %d | BOTTOM_LEFT: %d | BOTTOM_RIGHT: %d |\n Vertical Error: %d | Horizontal Error: %d |\n", 
        sensorValues[0] , sensorValues[1] , sensorValues[2]  , sensorValues[3], vertError, horiError);
    
    
    Serial.printf("VERTICAL ERROR: %d | PITCH POSITION: %d | PITCH CONTROL: %d \n",
        vertError, pitchPosition, ctrPITCH.controlValue);
    Serial.printf("HORIZONTAL ERROR: %d | YAW POSITION: %d | YAW CONTROL: %d \n",
        horiError, yawPosition, ctrYAW.controlValue);
    delay(1000);
    
}



