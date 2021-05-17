// Pin definition
char command = ' ';
#define pinENA 5
#define pinN1  4
#define pinN2  6
#define pinENB 9
#define pinN3  7
#define pinN4  8

void setup() 
{ 
  Serial.begin(9600); // Initializes serial communication
  for (byte pin = 3; pin <= 7; pin++) pinMode(pin, OUTPUT); // Definition of the motor pins
}

void loop() 
{  
  carDirection(command); 
}

void carDirection(char command) 
{
  if (Serial.available() > 0) 
  {
    command = Serial.read();
    Serial.println("Comando: " + String(command)); // Shows commands via serial
    // carEngine(byte leftSpeed, bool connectorRedL, bool connectorBlackL, byte rightSpeed, bool connectorRedR, bool connectorBlackR)
         if (command == 'f') carEngine(150, 1, 0, 150, 1, 0); // command for the car to go forward
    else if (command == 'b') carEngine(150, 0, 1, 150, 0, 1); // command for the car to go back
    else if (command == 'l') carEngine(150, 0, 1, 150, 1, 0); // command for the car to go left
    else if (command == 'r') carEngine(150, 1, 0, 150, 0, 1); // command for the car to go right
    else if (command == 's') carEngine(0, 1, 0, 0, 1, 0);     // command for the car to go stop
  }
}

void carEngine(byte leftSpeed, bool connectorRedL, bool connectorBlackL,
               byte rightSpeed, bool connectorRedR, bool connectorBlackR) {
  analogWrite(pinENA, leftSpeed);
  digitalWrite(pinN1, connectorRedL);
  digitalWrite(pinN2, connectorBlackL);
  analogWrite(pinENB, rightSpeed);
  digitalWrite(pinN3, connectorRedR);
  digitalWrite(pinN4, connectorBlackR);
}
