int pin_UL_Trig = 7;
int pin_UL_Out = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_UL_Trig, OUTPUT);
  pinMode(pin_UL_Out, INPUT);
  Serial.begin(115200);
  digitalWrite(pin_UL_Trig, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long microseconds, distance_cm;

  digitalWrite(pin_UL_Trig, 0);
  delayMicroseconds(2);

  digitalWrite(pin_UL_Trig, 1);
  delayMicroseconds(10);

  digitalWrite(pin_UL_Trig, 0);

  microseconds = pulseIn(pin_UL_Out, 1, 24000);
  distance_cm = microseconds * 17 / 1000;

  Serial.print("Time: ");
  Serial.print(microseconds);
  Serial.println("[us]");

  Serial.print("Dist: ");
  Serial.print(distance_cm);
  Serial.println("[cm]");
  delay(1000);
}
