
const int trigPin = 12;
const int echoPin = 11;

const int redLED = 7;
const int yellowLED = 6;
const int greenLED = 5;
const int buzzer = 8;

// true = passive buzzer
// false = active buzzer
const bool passiveBuzzer = true;

int zone = -1;
bool buzzerOn = false;

unsigned long lastMeasurement = 0;
unsigned long nextBeep = 0;
unsigned long pauseTime = 800;

void setBuzzer(bool on) {
  buzzerOn = on;

  if (passiveBuzzer) {
    if (on) {
      tone(buzzer, 3000);
    } else {
      noTone(buzzer);
    }
  } else {
    digitalWrite(buzzer, on ? HIGH : LOW);
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  setBuzzer(false);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // Measure every 100 milliseconds
  if (now - lastMeasurement >= 100) {
    lastMeasurement = now;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    int newZone = -1;

    if (duration > 0) {
      float distance = duration * 0.0343 / 2.0;

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      if (distance > 50) {
        newZone = 0;  // SAFE
      }
      else if (distance >= 20) {
        newZone = 1;  // WARNING

        // Beep faster as distance decreases
        pauseTime = map(
          constrain((int)distance, 20, 50),
          20, 50, 450, 1000
        );
      }
      else {
        newZone = 2;  // STOP

        // Very fast beeping near obstacles
        pauseTime = map(
          constrain((int)distance, 2, 19),
          2, 19, 70, 220
        );
      }
    } else {
      Serial.println("No echo");
    }

    // Control LEDs
    digitalWrite(greenLED, newZone == 0);
    digitalWrite(yellowLED, newZone == 1);
    digitalWrite(redLED, newZone == 2);

    // Reset buzzer when zone changes
    if (newZone != zone) {
      zone = newZone;
      setBuzzer(false);
      nextBeep = millis();
    }
  }

  // Control buzzer without delay()
  if (zone == 1 || zone == 2) {
    now = millis();

    if ((long)(now - nextBeep) >= 0) {
      if (buzzerOn) {
        setBuzzer(false);
        nextBeep = now + pauseTime;
      } else {
        setBuzzer(true);
        nextBeep = now + 100;
      }
    }
  }
}

