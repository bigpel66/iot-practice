#include <WiFiEsp.h>

#ifndef HAVE_HWSERIAL1
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7);
#endif

char ssid[] = "";
char pass[] = "";
int status = WL_IDLE_STATUS;

int led_Status = LOW;
int led1 = 5;

WiFiEspServer server(80);

RingBuffer buf(8);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  WiFi.init(&Serial1);

  if(WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");

    while(true);
  }

  while(status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();

  Serial.begin(115200);
  Serial1.begin(115200);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiEspClient client = server.available();

  if(client) {
    Serial.println("New client");
    buf.init();
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        buf.push(c);

        Serial.write(c);

        if(buf.endsWith("\r\n\r\n")) {
          sendHttpResponse(client);
          break;
        }

        if(buf.endsWith("GET /H")) {
          led_Status = HIGH;
          digitalWrite(led1, HIGH);
        }
        else if(buf.endsWith("GET /L")) {
          led_Status = LOW;
          digitalWrite(led1, LOW);
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

void sendHttpResponse(WiFiEspClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  
  client.print("The LED is ");
  client.print(led_Status);
  client.println("<br>");
  client.println("<br>");
  
  client.println("Click <a href=\"/H\">here</a> turn the LED on<br>");
  client.println("Click <a href=\"/L\">here</a> turn the LED off<br>");
  
  client.println();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
