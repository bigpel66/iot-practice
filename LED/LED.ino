int pin_LED[3] = {11, 12, 13};

void setup() {
  // put your setup code here, to run once:
  char i;
  for(i = 0; i < 3; i++){
    pinMode(pin_LED[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char i;
  for(i = 0; i < 3; i++) {
    digitalWrite(pin_LED[i], 1);
  }
  delay(500);
  
  for(i = 0; i < 3; i++) {
    digitalWrite(pin_LED[i], 0);
  } 
  delay(500);
}
