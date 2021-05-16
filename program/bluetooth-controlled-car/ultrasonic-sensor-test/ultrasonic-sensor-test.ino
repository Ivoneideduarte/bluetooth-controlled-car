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
  // Liga o pino Trigger em nivel logico alto por 10 microsegundoa
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Ler o pino Echo. A função pulseIn() retorna a duracão do pulso em microsegundos
  duration = pulseIn(echoPin, HIGH);
  // Calcula a distancia
  distance = duration * 0.0171;
  Serial.println(distance);
}
