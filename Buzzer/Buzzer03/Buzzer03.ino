int pin_Buzzer = 35;
int pin_Joy_V = A1;
int note_Duration = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Buzzer, OUTPUT);
  pinMode(pin_Joy_V, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Joy_V = analogRead(pin_Joy_V);

  Serial.print("Joy_V: ");
  Serial.print(Joy_V);

  tone(pin_Buzzer, (Joy_V + 1023), note_Duration);
}
