#include <ESP32Servo.h>

// Servo myServo;
// int servoPin = 18;

// void setup() {
//   Serial.begin(9600);
//   delay(1000);  // Give time for Serial Monitor to connect

//   Serial.println("Attaching servo...");
//   myServo.attach(servoPin);
  
//   Serial.println("Moving to center (90°)");
//   myServo.write(90); // Start at center
//   delay(1000);
// }

// void loop() {
//   // Turn left slowly (from 90° to 0°)
//   Serial.println("Turning left slowly (90° → 0°)");
//   for (int pos = 90; pos >= 0; pos-= 10) {
//     myServo.write(pos);
//     Serial.print("Angle: ");
//     Serial.println(pos);
//     delay(100);  // Slow speed
//   }
//   delay(1000);

//   // Turn left fast (from 0° to 90°)
//   Serial.println("Turning left fast (0° → 90°)");
//   for (int pos = 0; pos <= 90; pos += 10) {
//     myServo.write(pos);
//     Serial.print("Angle: ");
//     Serial.println(pos);
//     delay(100);  // Fast speed
//   }
//   delay(1000);

//   // Turn right slowly (from 90° to 180°)
//   Serial.println("Turning right slowly (90° → 180°)");
//   for (int pos = 90; pos <= 180; pos+= 10) {
//     myServo.write(pos);
//     Serial.print("Angle: ");
//     Serial.println(pos);
//     delay(100);  // Slow speed
//   }
//   delay(1000);

//   // Turn right fast (from 180° to 90°)
//   Serial.println("Turning right fast (180° → 90°)");
//   for (int pos = 180; pos >= 90; pos -= 10) {
//     myServo.write(pos);
//     Serial.print("Angle: ");
//     Serial.println(pos);
//     delay(100);  // Fast speed
//   }

//   Serial.println("Cycle complete. Restarting in 1 seconds...\n");
//   delay(1000); // Wait before repeating
// }




// 


// // Pin assignments
// const int powerPin = 13;      // Power toggle for LDRs
// const int ldr1Pin = 12;       // LDR 1 analog pin top left
// const int ldr2Pin = 11;       // LDR 2 analog pin top right
// const int ldr3Pin = 10;        // LDR 3 analog pin bottom left
// const int ldr4Pin = 9;        // LDR 4 analog pin bottom right
// const int servoYawPin = 18;   // Servo for yaw adjustment
// const int servoPitchPin = 17; // Servo for pitch adjustment

// Servo servoYaw;
// Servo servoPitch;

// int yawPosition = 1500;   // Initial yaw servo position
// int pitchPosition = 1500; // Initial pitch servo position

// const int stepSize = 10; // Step size for servo adjustments
// const int tolerance = 100; // Acceptable LDR difference tolerance

// void setup() {
//   Serial.begin(9600); // For debugging

//   pinMode(powerPin, OUTPUT);
//   digitalWrite(powerPin, HIGH); // Enable power to LDR circuit
//   delay(10); // Stabilization time for LDR circuit
//   pinMode(ldr1Pin, INPUT);
//   pinMode(ldr2Pin, INPUT);
//   pinMode(ldr3Pin, INPUT);
//   pinMode(ldr4Pin, INPUT);

//   // Attach servos to their respective pins
//   if (servoYaw.attach(servoYawPin) == 0) {
//     Serial.println("Failed to attach Yaw servo");
//   } else {
//     Serial.println("Yaw servo attached.");
//   }
//   servoYaw.setPeriodHertz(50);
//     // Attach servo
//   if (servoPitch.attach(servoPitchPin) == 0) {
//     Serial.println("Failed to attach Pitch servo");
//   } else {
//     Serial.println("Pitch servo attached.");
//   }
//   servoPitch.setPeriodHertz(50);

//   servoYaw.writeMicroseconds(1500);  // Move to 0°
//   delay(1000);
//   servoYaw.writeMicroseconds(1000); // Move to 180°
//   delay(1000);
//   servoYaw.writeMicroseconds(1500);  // Reset to 90°
//   delay(1000);
//   servoYaw.writeMicroseconds(2000); // Move to 180°

//   // servoPitch.writeMicroseconds(1500);  // Move to 0°
//   // delay(1000);
//   // servoPitch.writeMicroseconds(1000); // Move to 180°
//   // delay(1000);
//   // servoPitch.writeMicroseconds(1500);  // Reset to 90°
//   // delay(1000);
//   // servoPitch.writeMicroseconds(2000); // Move to 180°
// }

// void loop() {
//   // Read LDR values
//   int ldr1 = analogRead(ldr1Pin);
//   int ldr2 = analogRead(ldr2Pin);
//   int ldr3 = analogRead(ldr3Pin);
//   int ldr4 = analogRead(ldr4Pin);

//   // Calculate light differences
//   int verticalDifference = (ldr1 + ldr2) - (ldr3 + ldr4);
//   int horizontalDifference = (ldr1 + ldr3) - (ldr2 + ldr4);

//   // Adjust pitch (vertical) if necessary
//   if (abs(verticalDifference) > tolerance) {
//     if (verticalDifference > 0 && pitchPosition > 1000) {
//       pitchPosition -= stepSize; // Move down
//     } else if (verticalDifference < 0 && pitchPosition < 2000) {
//       pitchPosition += stepSize; // Move up
//     }
//     // servoPitch.writeMicroseconds(pitchPosition);
//   }

//   // Adjust yaw (horizontal) if necessary
//   if (abs(horizontalDifference) > tolerance) {
//     if (horizontalDifference > 0 && yawPosition > 1000) {
//       yawPosition -= stepSize; // Move left
//     } else if (horizontalDifference < 0 && yawPosition < 2000) {
//       yawPosition += stepSize; // Move right
//     }
//      servoYaw.writeMicroseconds(yawPosition);
//   }

//   // Debugging output
//   Serial.printf("TOP_LEFT: %d TOP_RIGHT: %d BOTTOM_LEFT: %d BOTTOM_RIGHT: %d | Vertical Diff: %d Horizontal Diff: %d | Yaw: %d Pitch: %d\n", 
//                ldr1, ldr2, ldr3, ldr4, verticalDifference, horizontalDifference, yawPosition, pitchPosition);

//    servoYaw.writeMicroseconds(yawPosition);   // Initialize yaw position
//   // servoPitch.writeMicroseconds(pitchPosition); // Initialize pitch position
//   delay(100); // Small delay for stability
// }

// 

// Pin assignments
const int powerPin = 13;      // Power toggle for LDRs
const int ldr1Pin = 12;       // LDR 1 analog pin top left
const int ldr2Pin = 11;       // LDR 2 analog pin top right
const int ldr3Pin = 10;       // LDR 3 analog pin bottom left
const int ldr4Pin = 9;        // LDR 4 analog pin bottom right
const int servoYawPin = 18;   // Servo for yaw adjustment
const int servoPitchPin = 17; // Servo for pitch adjustment

Servo servoYaw;
Servo servoPitch;

int yawPosition = 1500;   // Initial yaw servo position
int pitchPosition = 1500; // Initial pitch servo position

const int stepSize = 100;   // Step size for servo adjustments
const int tolerance = 100; // Acceptable LDR difference tolerance

void setup() {
  Serial.begin(9600); // For debugging
  delay(1000);

  // LDR setup
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH); // Enable power to LDR circuit
  delay(10); // Stabilization time

  pinMode(ldr1Pin, INPUT);
  pinMode(ldr2Pin, INPUT);
  pinMode(ldr3Pin, INPUT);
  pinMode(ldr4Pin, INPUT);

  // Attach servos
  if (servoYaw.attach(servoYawPin) == 0) {
    Serial.println("Failed to attach Yaw servo");
  } else {
    Serial.println("Yaw servo attached.");
  }
  servoYaw.setPeriodHertz(50);

  // if (servoPitch.attach(servoPitchPin) == 0) {
  //   Serial.println("Failed to attach Pitch servo");
  // } else {
  //   Serial.println("Pitch servo attached.");
  // }
  // servoPitch.setPeriodHertz(50);

  // Initial yaw test
  Serial.println("Testing yaw servo...");
  servoYaw.writeMicroseconds(1500); delay(1000);
  servoYaw.writeMicroseconds(1000); delay(1000);
  servoYaw.writeMicroseconds(1500); delay(1000);
  servoYaw.writeMicroseconds(2000); delay(1000);

  // Initial pitch test (commented out)
  /*
  Serial.println("Testing pitch servo...");
  servoPitch.writeMicroseconds(1500); delay(1000);
  servoPitch.writeMicroseconds(1000); delay(1000);
  servoPitch.writeMicroseconds(1500); delay(1000);
  servoPitch.writeMicroseconds(2000); delay(1000);
  */
}

void loop() {
  // Read LDR values
  int ldr1 = analogRead(ldr1Pin);
  int ldr2 = analogRead(ldr2Pin);
  int ldr3 = analogRead(ldr3Pin);
  int ldr4 = analogRead(ldr4Pin);

  // Calculate light differences
  int verticalDifference = (ldr1 + ldr2) - (ldr3 + ldr4);
  int horizontalDifference = (ldr2 + ldr4) - (ldr1 + ldr3);

  // Adjust pitch (vertical) — movement is disabled for now
  if (abs(verticalDifference) > tolerance) {
    if (verticalDifference > 0 && pitchPosition > 500) {
      pitchPosition -= stepSize; // Move down
      Serial.println("Pitch adjustment: DOWN");
    } else if (verticalDifference < 0 && pitchPosition < 2500) {
      pitchPosition += stepSize; // Move up
      Serial.println("Pitch adjustment: UP");
    }
    // servoPitch.writeMicroseconds(pitchPosition); // <-- still commented out
  }

  // Adjust yaw (horizontal)
  if (abs(horizontalDifference) > tolerance) {
    if (horizontalDifference > 0 && yawPosition > 500) {
      yawPosition -= stepSize; // Move left
      Serial.println("Yaw adjustment: LEFT");
    } else if (horizontalDifference < 0 && yawPosition < 2500) {
      yawPosition += stepSize; // Move right
      Serial.println("Yaw adjustment: RIGHT");
    }
    servoYaw.writeMicroseconds(yawPosition);
  }

  // Debug output
  // Serial.printf("TOP_LEFT: %d | TOP_RIGHT: %d | BOTTOM_LEFT: %d | BOTTOM_RIGHT: %d\n", ldr1, ldr2, ldr3, ldr4);
  // Serial.printf("Vertical Diff: %d | Horizontal Diff: %d | Yaw: %d | Pitch: %d\n\n",
  //               verticalDifference, horizontalDifference, yawPosition, pitchPosition);

  Serial.printf("TOP_LEFT: %d TOP_RIGHT: %d BOTTOM_LEFT: %d BOTTOM_RIGHT: %d | Vertical Diff: %d Horizontal Diff: %d | Yaw: %d Pitch: %d\n", 
  ldr1, ldr2, ldr3, ldr4, verticalDifference, horizontalDifference, yawPosition, pitchPosition);

  delay(1000);
}