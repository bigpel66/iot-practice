#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A5 440
#define NOTE_B5 494
#define NOTE_C5 523

int pin_Buzzer = 35;
int note_Duration = 250;

int notes[8] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A5, NOTE_B5, NOTE_C5
};

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    byte data = Serial.read();
    if(data >= '1' && data <= '8') {
      tone(pin_Buzzer, notes[data - '1'], note_Duration);
      Serial.println(data);
    }
  }
}
