#include <dht11.h>

dht11 DHT11;
int pin_DHT11 = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int check = DHT11.read(pin_DHT11);

  switch(check){
    case DHTLIB_OK:
      Serial.print("Temperature: ");
      Serial.print(DHT11.temperature);
      Serial.print("[C] Humidity: ");
      Serial.print(DHT11.humidity);
      Serial.print("[%]");
      break;

    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error");
      break;

    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error");
      break;

    default:
      Serial.println("Unknown error");
      break;
  }

  delay(1000);
}
