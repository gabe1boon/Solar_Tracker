#include <Wire.h>
#include <INA226_WE.h>
#include <functions.h>
#define I2C_ADDRESS 0x40

INA226_WE ina226(I2C_ADDRESS);
// INA226_WE ina226 = INA226_WE(); // Alternative: sets default address 0x40

void startup() {
  Wire.begin(A5, A4);
  ina226.init();

  /* Set Number of measurements for shunt and bus voltage which shall be averaged
  * Mode *     * Number of samples *
  AVERAGE_1            1 (default)
  AVERAGE_4            4
  AVERAGE_16           8
  AVERAGE_64          64
  AVERAGE_128        128
  AVERAGE_256        256
  AVERAGE_512        512
  AVERAGE_1024      1024
  */
  //ina226.setAverage(AVERAGE_1); // choose mode and uncomment for change of default

  /* Set conversion time in microseconds
     One set of shunt and bus voltage conversion will take: 
     number of samples to be averaged x conversion time x 2
     
     * Mode *         * conversion time *
     CONV_TIME_140          140 µs
     CONV_TIME_204          204 µs
     CONV_TIME_332          332 µs
     CONV_TIME_588          588 µs
     CONV_TIME_1100         1.1 ms (default)
     CONV_TIME_2116       2.116 ms
     CONV_TIME_4156       4.156 ms
     CONV_TIME_8244       8.244 ms  
  */
  //ina226.setConversionTime(CONV_TIME_1100); //choose conversion time and uncomment for change of default
  
  /* Set measure mode
  POWER_DOWN - INA219 switched off
  TRIGGERED  - measurement on demand
  CONTINUOUS  - Continuous measurements (default)
  */
  ina226.setMeasureMode(CONTINUOUS); // choose mode and uncomment for change of default
  
  /* If the current values delivered by the INA226 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA226
  */
  // ina226.setCorrectionFactor(0.95);
  
   
  // ina226.waitUntilConversionCompleted(); //makes no sense - in triggered mode we wait anyway for completed conversion
}



SolarOutput getMeas() {
  SolarOutput s1;
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  
  ina226.startSingleMeasurement();
  ina226.readAndClearFlags();
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  s1.busVoltage_V = ina226.getBusVoltage_V();
  s1.current_mA = ina226.getCurrent_mA();
  s1.power_mW = ina226.getBusPower();
  s1.loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
    
  return(s1);
}