#include <TimerOne.h>

int pin_Color_Out = 3;
int pin_Color_S0 = 35;
int pin_Color_S1 = 36;
int pin_Color_S2 = 37;
int pin_Color_S3 = 38;
int pin_Color_LED = 39;

char color = 0;
unsigned int counterR = 0, counterG = 0, counterB = 0;
unsigned int counter = 0;

void Detect_Color(char c) {
  if(c == 0) {
    digitalWrite(pin_Color_S2, 0);
    digitalWrite(pin_Color_S3, 0);
  }
  else if(c == 1) {
    digitalWrite(pin_Color_S2, 1);
    digitalWrite(pin_Color_S3, 1);
  }
  else if(c == 2) {
    digitalWrite(pin_Color_S2, 0);
    digitalWrite(pin_Color_S3, 1);
  }
}

void ISR_INT()
{
  counter++;
}

void ISR_Timer() {
  if(color == 0) {
    counterR = counter;
    color = 1;
    Detect_Color(color);
  }
  else if(color == 1) {
    counterG = counter;
    color = 2;
    Detect_Color(color);
  }
  else if(color = 2) {
    counterB = counter;
    color = 0;
    Detect_Color(color);
  }
  counter = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Color_S0, OUTPUT);
  pinMode(pin_Color_S1, OUTPUT);
  pinMode(pin_Color_S2, OUTPUT);
  pinMode(pin_Color_S3, OUTPUT);
  pinMode(pin_Color_Out, INPUT);
  pinMode(pin_Color_LED, OUTPUT);

  //Enble LED
  digitalWrite(pin_Color_LED, 1);

  //Scale
  digitalWrite(pin_Color_S0, 0);
  digitalWrite(pin_Color_S1, 1);

  color = 0;
  Detect_Color(color);

  attachInterrupt(digitalPinToInterrupt(pin_Color_Out), ISR_INT, RISING);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(ISR_Timer);
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Red = ");
  Serial.print(counterR);
  Serial.print("Green = ");
  Serial.print(counterG);
  Serial.print("Blue = ");
  Serial.print(counterB);
  delay(1000);
}
