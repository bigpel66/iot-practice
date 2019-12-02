int pin_Joy_H = A0;
int pin_Joy_V = A1;
int pin_Up = 45;
int pin_Down = 46;
int pin_Left = 47;
int pin_Right = 48;
int pin_Sel =  49;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Joy_H, INPUT);
  pinMode(pin_Joy_V, INPUT);
  pinMode(pin_Up, INPUT);
  pinMode(pin_Down, INPUT);
  pinMode(pin_Left, INPUT);
  pinMode(pin_Right, INPUT);
  pinMode(pin_Sel, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Joy_H: ");
  Serial.println(analogRead(pin_Joy_H));
  Serial.print("Joy_V: ");
  Serial.println(analogRead(pin_Joy_V));
  Serial.print("Up: ");
  Serial.println(analogRead(pin_Up));
  Serial.print("Down: ");
  Serial.println(analogRead(pin_Down));
  Serial.print("Left: ");
  Serial.println(analogRead(pin_Left));
  Serial.print("Right: ");
  Serial.println(analogRead(pin_Right));
  Serial.print("Sel: ");
  Serial.println(analogRead(pin_Sel));
  delay(500);
}
