//Ultrasonic definition
#define trigPin 10
#define echoPin 11
long duration;
int distance;

//Line follower sensor definition
#define rightIR 2
#define leftIR 3
bool rightIRSensor, leftIRSensor;

bool warm = false;

//H Brigth definition
//Left Engine
#define ENA 5
#define N1 4
#define N2 6
//Right Engine
#define ENB 9
#define N3 7
#define N4 8

void setup()
{
  Serial.begin(9600); //Initialization of serial communication
  for (byte pin = 4; pin < 10; pin++)
  {
    pinMode(pin, OUTPUT);
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Turns on the Trigger pin at high logic level for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the Echo pin. PulseIn() function returns pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculates the distance
  distance = duration * 0.0171;
  Serial.println(distance);

  if (distance > 30) { // Reading up to 50cm - But, the sensor reading up to 400cm
    rightIRSensor = digitalRead(rightIR); //If you are in: black = 1 / white = 0
    leftIRSensor = digitalRead(leftIR);

    //if ((right sensor is Black) and (left sensor is White))
    if ((rightIRSensor) and (!leftIRSensor)) { //Right turn
      //wheel left: forward
      //wheel right: back
      //direcao(ENA, N1, N2, ENB, N3, N4);
      directionCar(150,  1,  0, 150,  0,  1);
    }
    else if (leftIRSensor) { //Left turn
      //wheel left: back
      //wheel right: forward
      //direcao(ENA, N1, N2, ENB, N3, N4);
      directionCar(150,  0,  1, 150,  1,  0);
    }
    else if ((rightIRSensor) and (leftIRSensor)) { //Stop Car
      //stop engine left
      //stop engine right
      //direcao(ENA, N1, N2, ENB, N3, N4);
      directionCar(  0,  1,  0,   0,  1,  0);
    }
    else { //Forward car
      //wheel left: forward
      //wheel right: forward
      //direcao(ENA, N1, N2, ENB, N3, N4);
      directionCar(200,  1,  0, 200,  1,  0);
    }
  }
  else callBluetooth();
}

void callBluetooth() {
  directionCar(  0,  1,  0,   0,  1,  0);
  warm = true;
  Serial.println("Warm! Obstacle in front");
  while (warm) {

    if (Serial.available() > 0) {
      Serial.println("bluetooth");
      char command = Serial.read();
      Serial.println(command);
      if (command == 'f') {
        //forward car
        directionCar(255,  1,  0, 255,  1,  0);
      }
      else if (command == 'b') {
        //back car
        //direcao(ENA, N1, N2, ENB, N3, N4);
        directionCar(255,  0,  1, 255,  0,  1);
      }
      else if (command == 'l') {
        //left turn car
        directionCar(255,  0,  1, 255,  1,  0);
      }
      else if (command == 'r') {
        //right turn car
        directionCar(255,  1,  0, 255,  0,  1);
      }
      else if (command == 's') {
        //Stop Car
        directionCar(  0,  1,  0,   0,  1,  0);
      }
      else if (command == 'e') {
        //exit of the bluetooth
        directionCar(  0,  1,  0,   0,  1,  0);
        warm = false;
      }
    }
  }
}

void directionCar(byte SpeedL, bool connectorRedL, bool connectorBlackL,
             byte SpeedR, bool connectorRedR, bool connectorBlackR) {
  analogWrite(ENA, SpeedL);
  digitalWrite(N1, connectorRedL);
  digitalWrite(N2, connectorBlackL);
  analogWrite(ENB, SpeedR);
  digitalWrite(N3, connectorRedR);
  digitalWrite(N4, connectorBlackR);
}
