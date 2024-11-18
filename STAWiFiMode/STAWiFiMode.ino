#include <WiFi.h>

const char *ssid = "Xiaomi 13 Lite";
const char *password = "salom12345";

NetworkServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);  // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  NetworkClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; }");
            client.println(".button { padding: 10px 20px; font-size: 18px; color: #fff; ");
            client.println("border: none; border-radius: 5px; cursor: pointer; }");
            client.println(".on { background-color: #4CAF50; }");  // Green for ON
            client.println(".off { background-color: #f44336; }"); // Red for OFF
            client.println(".button:hover { opacity: 0.8; }");
            client.println("</style></head><body>");

            // the content of the HTTP response follows the header:
            client.println("<h1>ESP32 LED Control</h1>");
            client.print("<p><a href=\"/H\" class=\"button on\">Turn LED On</a></p>");
            client.print("<p><a href=\"/L\" class=\"button off\">Turn LED Off</a></p>");

            // The HTTP response ends with another blank line:
            client.println("</body></html>");
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(23, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(23, LOW);  // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
