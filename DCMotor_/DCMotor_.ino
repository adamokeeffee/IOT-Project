

                                   //27
                                   //14

                                  //33
                                  //32

// Define ESP32 outputs to the motor driver pins
#define M1  27  // Motor 1 control pin (Direction)                 //5
#define E1  14  // Motor 1 enable pin (PWM for speed)              //18
#define M2  33  // Motor 2 control pin (Direction)                 //19
#define E2  32  // Motor 2 enable pin (PWM for speed)              //21

// PWM parameters
#define PWM_FREQ     5000 // Frequency for PWM
#define PWM_RES      8    // 8-bit resolution (0-255)
#define PWM_CHANNEL_E1 0  // PWM channel for Motor 1 (E1)
#define PWM_CHANNEL_E2 1  // PWM channel for Motor 2 (E2)

// Initialize motor control
void setup() {
  // Set M1 and M2 as output for direction control
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  // Configure PWM for E1 and E2
  ledcSetup(PWM_CHANNEL_E1, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL_E2, PWM_FREQ, PWM_RES);

  // Attach PWM channels to E1 and E2 pins
  ledcAttachPin(E1, PWM_CHANNEL_E1);
  ledcAttachPin(E2, PWM_CHANNEL_E2);

  // Stop both motors initially
  stopMotors();
}

// Function to stop both motors
void stopMotors() {
  digitalWrite(M1, LOW);  // No direction for Motor 1
  digitalWrite(M2, LOW);  // No direction for Motor 2
  ledcWrite(PWM_CHANNEL_E1, 0); // Stop Motor 1
  ledcWrite(PWM_CHANNEL_E2, 0); // Stop Motor 2
}

// Function to control Motor 1
void controlMotor1(int speed, bool forward) {
  digitalWrite(M1, forward ? HIGH : LOW);  // Set direction
  ledcWrite(PWM_CHANNEL_E1, speed);       // Set speed
}

// Function to control Motor 2
void controlMotor2(int speed, bool forward) {
  digitalWrite(M2, forward ? HIGH : LOW);  // Set direction
  ledcWrite(PWM_CHANNEL_E2, speed);       // Set speed
}

void loop() {
  // Example: Run Motor 1 forward at 50% speed
  controlMotor1(255, true);
  //delay(2000);

  // Example: Run Motor 2 backward at full speed
  controlMotor2(255, false);
  delay(2000);

  // Stop both motors
  stopMotors();
  delay(1000);
}