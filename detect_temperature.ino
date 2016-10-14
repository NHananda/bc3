#include <WiFiUdp.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiServer.h>
#include <ESP8266WiFi.h>

#include <DHT11.h>
//#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>
//#include <WiFiClientSecure.h>
//
//#include <WiFiClient.h>
//
//
//#include <ESP8266WiFiMulti.h>
//
//#include <WiFiServer.h>


const char* ssid = "nhananda";
const char* password = "12121994";

 int pin = 2;

 WiFiServer server(80);
 DHT11 dht11(pin);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println();
  Serial.println("Connection to " );
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  server.begin();
  Serial.println("Server started");

   Serial.println(WiFi.localIP());
  }



void loop() {
  int err;
float temp, humi;
if ((err = dht11.read(humi, temp)) == 0 )
{
Serial.print("temperature:");
Serial.print(temp);
Serial.print(" humidity:");
Serial.print(humi);
Serial.println();
}
else
{
Serial.println();
Serial.print("Error No :");
Serial.print(err);
Serial.println();
}
WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 5");  // refresh the page automatically every 5 sec
client.println();
client.println("<!DOCTYPE html>");
client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
client.println("<head>\n<meta charset='UTF-8'>");
client.println("<title>Internet Of Thing</title>");
client.println("</head>\n<body>");
client.println("<H2>ESP8266 & DHT11 Sensor</H2>");
client.println("<H3>Humidity / Temperature</H3>");
client.println("<pre>");
client.print("Humidity (%)         : ");
client.println((float)humi, 2);
client.print("Temperature (°C)  : ");
client.println((float)temp, 2);

client.println("</pre>");

client.print("</body>\n</html>");
delay(DHT11_RETRY_DELAY); //delay for reread
}
