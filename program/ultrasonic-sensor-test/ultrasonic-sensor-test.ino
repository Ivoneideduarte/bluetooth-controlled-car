#define trigPin 10
#define echoPin 11
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Connect the Trigger pin at high logic level for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the Echo pin. The pulseIn () function returns the pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculates distance
  distance = duration * 0.0171;
  Serial.println(distance);
}
