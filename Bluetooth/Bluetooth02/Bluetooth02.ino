void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  
  Serial3.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char color;

  if(Serial.available()) {
    Serial3.write(Serial.read());
  }
  if(Serial3.available()) {
      color = Serial3.read();
      switch(color) {
      case 'r':
        digitalWrite(11, HIGH);
        delay(1000);
        break;
      case 'g':
        digitalWrite(12, HIGH);
        delay(1000);
        break;
      case 'b':
        digitalWrite(13, HIGH);
        delay(1000);
        break;
      default:
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
        break;
    }

    Serial.write(color);
  }
}
