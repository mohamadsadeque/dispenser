int interruptPin = 3;
int sensor = A0;
int estado = 0;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(sensor, INPUT);
 attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
pinMode(7,OUTPUT);
}

void interrupt(){
 Serial.println("Entrei");
 estado = !estado;
 delay(200);
  }

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(7, estado);
Serial.println(digitalRead(3));
}
