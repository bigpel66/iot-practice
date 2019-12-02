int pin_PIR = 18;
char flag_PIR = 0;

void ISR_PIR(void) {
  flag_PIR = 1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_PIR, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pin_PIR), ISR_PIR, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag_PIR == 1) {
    Serial.println("Detected");
  }
  else if(flag_PIR == 0) {
    Serial.println("Not Detected");
  }
  delay(500);
}
