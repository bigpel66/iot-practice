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
int response_Type = 1;

WiFiEspServer server(80);

RingBuffer buf(25);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  WiFi.init(&Serial1);

  if(WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");

    while(true);
  }

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID:  ");
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
        char c=  client.read();
        buf.push(c);

        if(buf.endsWith("\r\n\r\n")) {
          break;
        }
        else if(buf.endsWith("GET / "))
          response_Type = 1;
        else if(buf.endsWith("GET /led.cgi?LEDstatus=1"))
          response_Type = 2;
        else if(buf.endsWith("GET /led.cgi?LEDstatus=0"))
          response_Type = 3;
      }
    }

    switch(response_Type) {
      case 1: show_Main_Page(client); break;
      case 2: show_On_Off_Page(client, true); break;
      case 3: show_On_Off_Page(client, false); break;
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

void show_On_Off_Page(WiFiEspClient client, boolean status) {
  led_Status  = status;
  digitalWrite(led1, led_Status);
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  
  client.println("<html>");
  client.println("<body>");
  
  client.print("Now... LED is ");
  client.println(led_Status ? "On.":"Off.");
  
  client.println("<br /><br />");
  client.println("<a href=\"/\">Main Control Page</a>");

  client.println("</body>");
  client.println("</html>");
  
  client.println();
}

void show_Main_Page(WiFiEspClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  
  client.println("<html>");
  client.println("<body>");
  
  client.print("Currently... LED is ");
  client.println(led_Status ? "On.":"Off.");
  
  client.println("<br />");
  client.println("<FORM method=\"get\" action=\"/led.cgi\">");
  client.println("<P><INPUT type=\"radio\" name=\"LEDstatus\" value=\"1\">Turn On");
  client.println("<P><INPUT type=\"radio\" name=\"LEDstatus\" value=\"0\">Turn off");
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
