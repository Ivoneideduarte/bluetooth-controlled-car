#define pinENA 5
#define pinN1 4
#define pinN2 6
#define pinN3 7
#define pinN4 8
#define pinENB 9

void setup() {
  Serial.begin(9600);
  for (byte pin = 2; pin < 13; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.println(command);
    if (command == 'f') {
      // Forward
      directionCar(0, 1, 0, 1); // N1 = 0, N2 = 1, N3 = 0, N4 = 1
    }
    if (command == 'b') {
      // Back
      directionCar(1, 0, 1, 0); // N1 = 0, N2 = 1, N3 = 0, N4 = 1
    }
    else if (command == 'r') { 
      // Right
      directionCar(0, 1, 1, 0);
    }
    else if (command == 'l') { 
      // Left
      directionCar(1, 0, 0, 1);
    }
    else if (command == 's') {
      directionCar(0, 0, 0, 0);
    }
  }
}

void directionCar(bool N1, bool N2, bool N3, bool N4) {
  analogWrite(pinENA, 255);
  digitalWrite(pinN1, N1);
  digitalWrite(pinN2, N2);
  digitalWrite(pinN3, N3);
  digitalWrite(pinN4, N4);
  analogWrite(pinENB, 255);
}
