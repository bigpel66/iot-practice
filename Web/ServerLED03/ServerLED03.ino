#include <WiFiEsp.h>

#ifndef HAVE_HWSERIAL1
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7);
#endif

char ssid[] = "";
char pass[] = "";
int status = WL_IDLE_STATUS;

int brightness = 0;
int led1 = 5;
int response_Type = 1;

WiFiEspServer server(80);

RingBuffer buf(30);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  WiFi.init(&Serial1);

  if(WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");

    while(true);
  }

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.print(ssid);

    status = WiFi.begin(ssid, pass);
  }

  Serial.print("You're connected to the network");
  printWifiStatus();

  Serial.begin(115200);
  Serial1.begin(115200);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiEspClient client = server.available();

  if(client) {
    bool led_Flag_Start = false;
    bool led_Flag_End = false;
    int num_led = 0;
    String bvalue = "";

    Serial.println("New client");
    buf.init();

    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        buf.push(c);

        if(buf.endsWith("\r\n\r\n")) {
          break;
        }

        if(led_Flag_Start == true && led_Flag_End == false) {
          if(c != ' ') {
            bvalue += c;
            num_led += 1;
          }
          else {
            led_Flag_End = true;
            int input = bvalue.toInt();
            if(input >= 0 && input <= 255) {
              brightness = input;
              analogWrite(led1, brightness);
              Serial.println(brightness);
            }
          }
        }

        if(buf.endsWith("GET /led.cgi?brightness=")) {
          led_Flag_Start = true;
        }
      }
    }

    show_Main_Page(client);

    client.stop();
    Serial.println("Client disconnected");
  }
}

void show_Main_Page(WiFiEspClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  
  client.println("<html>");
  client.println("<body>");
  
  client.print("LED brightness (0 ~ 255) is ");
  client.println(brightness);
  
  client.println("<br />");
  client.println("<FORM method=\"get\" action=\"/led.cgi\">");
  client.println("<P>Brightness <INPUT type=\"text\" name=\"brightness\">");
  client.println("<P><INPUT type=\"submit\" value=\"Submit\"></FORM>");
  
  client.println("</body>");
  client.println("</html>");

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
