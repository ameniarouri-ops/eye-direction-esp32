#include <Arduino.h>

const int PIN_LEFT = 34, PIN_RIGHT = 35;
const int LED_LEFT = 25, LED_CENTER = 26, LED_RIGHT = 27;
const int N_SAMPLES = 10;
const char* SOURCE = "simulated";   // "real" later

int tLeft = 400, tRight = -400;     // overwritten by calibration

int readAverage(int pin) {
  long sum = 0;
  for (int i = 0; i < N_SAMPLES; i++) { sum += analogRead(pin); delay(2); }
  return sum / N_SAMPLES;
}

long recordPhase(const char* msg) {  // average diff over 5 s
  Serial.println(msg);
  delay(4000);                       // time to get ready
  long sum = 0; int n = 0;
  unsigned long start = millis();
  while (millis() - start < 5000) {
    sum += readAverage(PIN_LEFT) - readAverage(PIN_RIGHT);
    n++;
    delay(50);
  }
  return sum / n;
}

void showDirection(int dir) {
  digitalWrite(LED_LEFT,   dir == -1);
  digitalWrite(LED_CENTER, dir == 0);
  digitalWrite(LED_RIGHT,  dir == 1);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_CENTER, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  Serial.println("CALIBRATION");
  long mL = recordPhase("Look LEFT now (hold 5 s)");
  long mC = recordPhase("Look CENTER now (hold 5 s)");
  long mR = recordPhase("Look RIGHT now (hold 5 s)");

  tLeft  = (mL + mC) / 2;   // above this = LEFT
  tRight = (mR + mC) / 2;   // below this = RIGHT
  Serial.print("tLeft=");  Serial.print(tLeft);
  Serial.print(" tRight="); Serial.println(tRight);
  Serial.println("time_ms,left,right,diff,label,source");
}

void loop() {
  int left = readAverage(PIN_LEFT);
  int right = readAverage(PIN_RIGHT);
  int diff = left - right;

  int dir = 0; const char* name = "CENTER";
  if (diff > tLeft)       { dir = -1; name = "LEFT"; }
  else if (diff < tRight) { dir = 1;  name = "RIGHT"; }
  showDirection(dir);

  Serial.print(millis()); Serial.print(",");
  Serial.print(left);     Serial.print(",");
  Serial.print(right);    Serial.print(",");
  Serial.print(diff);     Serial.print(",");
  Serial.print(name);     Serial.print(",");
  Serial.println(SOURCE);
  delay(200);
}