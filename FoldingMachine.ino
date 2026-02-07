#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

/* =======================
   CONSTANTS
   ======================= */
#define SERVOMIN 120
#define SERVOMAX 750
#define SERVO_FREQ 50

// ===== SPEED CONTROL =====
#define STEP_SIZE 4    // bigger = faster
#define STEP_DELAY 5  // ms, smaller = faster

/* =======================
   BUTTON PINS (NC buttons)
   ======================= */
#define BUTTON1_PIN 2  // Fold Servo 1–4
#define BUTTON2_PIN 3  // Fold Servo 1–3

/* =======================
   SERVO CHANNELS
   ======================= */
#define SERVO1 0
#define SERVO2 1
#define SERVO3 2
#define SERVO4 3

/* =======================
   SETUP
   ======================= */
void setup() {
  Serial.begin(9600);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(100);

  Serial.println("Shirt Folding Machine Ready");

  // Initialize servos smoothly
  resetServos();

  delay(1000);
  foldServo1();
  foldServo2();
  foldServo3();
  foldServo4();
}

/* =======================
   LOOP
   ======================= */
void loop() {
  // ===== BUTTON 1: Fold Servo 1–4 =====
  if (digitalRead(BUTTON1_PIN) == HIGH) {
    Serial.println("Button 1 Pressed: Fold Servo 1–4");

    foldServo1();
    foldServo2();
    foldServo3();
    foldServo4();

    delay(1000);  // debounce
  }

  // ===== BUTTON 2: Fold Servo 1–3 =====
  if (digitalRead(BUTTON2_PIN) == HIGH) {
    Serial.println("Button 2 Pressed: Fold Servo 1–3");

    foldServo1();
    foldServo2();
    foldServo3();

    delay(1000);  // debounce
  }
}

/* =======================
   SERVO MOVE FUNCTION
   ======================= */
void moveServoSmooth(uint8_t channel, int fromPulse, int toPulse) {
  if (fromPulse < toPulse) {
    for (int p = fromPulse; p <= toPulse; p += STEP_SIZE) {
      pwm.setPWM(channel, 0, p);
      delay(STEP_DELAY);
    }
  } else {
    for (int p = fromPulse; p >= toPulse; p -= STEP_SIZE) {
      pwm.setPWM(channel, 0, p);
      delay(STEP_DELAY);
    }
  }
}

/* =======================
   SERVO ACTIONS
   ======================= */

// Servo 1: 15° ↔ 90°
void foldServo1() {
  moveServoSmooth(SERVO1, 172, 435);
  delay(300);
  moveServoSmooth(SERVO1, 435, 172);
  delay(300);
}

// Servo 2: 10° ↔ 90°
void foldServo2() {
  moveServoSmooth(SERVO2, 155, 435);
  delay(300);
  moveServoSmooth(SERVO2, 435, 155);
  delay(300);
}

// Servo 3: 80° ↔ 10°
void foldServo3() {
  moveServoSmooth(SERVO3, 400, 155);
  delay(300);
  moveServoSmooth(SERVO3, 155, 400);
  delay(300);
}

// Servo 4: 5° ↔ 90°
void foldServo4() {
  moveServoSmooth(SERVO4, 172, 435);
  delay(300);
  moveServoSmooth(SERVO4, 435, 172);
  delay(300);
}

/* =======================
   RESET POSITION
   ======================= */
void resetServos() {
  moveServoSmooth(SERVO1, 435, 172);
  moveServoSmooth(SERVO2, 435, 155);
  moveServoSmooth(SERVO3, 155, 400);
  moveServoSmooth(SERVO4, 435, 172);
}
