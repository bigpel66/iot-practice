#include <dht11.h>
dht11 DHT11;
int pin_DHT11 = 6;

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int check = DHT11.read(pin_DHT11);
  switch (check) {
    case DHTLIB_OK:
      Serial3.print("Temperature: ");
      Serial3.print(DHT11.temperature);
      Serial3.print("[C] Humidity: ");
      Serial3.print(DHT11.humidity);
      Serial3.println("[%]");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial3.println("Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial3.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
  delay(1000);
}
