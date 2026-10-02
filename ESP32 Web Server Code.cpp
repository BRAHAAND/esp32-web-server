// Include the Wi-Fi library required for ESP32 networking
#include <WiFi.h>

// Replace with your actual network credentials
const char* ssid = "YOUR_WIFI_NETWORK_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Set web server port number to 80 (the standard HTTP port)
WiFiServer server(80);

// Assign the built-in LED pin (GPIO 2 is standard for most ESP32 Dev Boards)
const int ledPin = 2; 

void setup() {
  // Start serial communication at 115200 baud rate for diagnostic output
  Serial.begin(115200);
  
  // Configure the LED pin as an output and ensure it is turned off initially
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to the specified Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wait in a loop until the ESP32 successfully connects to the router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print the assigned local IP address to the Serial Monitor
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start the web server to listen for incoming clients (browsers)
  server.begin();
}

void loop(){
  // Check if a new client has connected to the web server
  WiFiClient client = server.available();   

  if (client) {                             // If a client successfully connects,
    String currentLine = "";                // Create a String to hold incoming HTTP request data
    while (client.connected()) {            // Keep looping while the client remains connected
      if (client.available()) {             // If there are bytes to read from the client,
        char c = client.read();             // Read a single character
        
        // If the character is a newline ('\n')
        if (c == '\n') {                    
          // If the current line is blank (two newlines in a row), 
          // it signifies the end of the client's HTTP request.
          if (currentLine.length() == 0) {
            
            // 1. Send standard HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println(); // Headers must conclude with a blank line
            
            // 2. Send the HTML content for the web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            
            // 3. Add CSS styling to format and center the buttons
            client.println("<style>body { font-family: Helvetica; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // 4. Send the body of the web page with the Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // 5. Create two buttons: One points to the URL "/H" (ON), the other to "/L" (OFF)
            client.println("<p><a href=\"/H\"><button class=\"button\">Turn ON</button></a></p>");
            client.println("<p><a href=\"/L\"><button class=\"button button2\">Turn OFF</button></a></p>");
            client.println("</body></html>");
            
            // The HTTP response must end with another blank line
            client.println();
            
            // Break out of the while loop to stop reading data and close the connection
            break;
          } else { 
            // If we got a newline but the current line wasn't empty, clear it for the next line
            currentLine = "";
          }
        } else if (c != '\r') {  // If the character is not a carriage return ('\r')
          currentLine += c;      // Append it to the end of the current line
        }

        // --- Execute Commands Based on the HTTP Request ---
        
        // If the client requested "GET /H" (They clicked the "Turn ON" button)
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(ledPin, HIGH);               // Turn the physical LED on
        }
        // If the client requested "GET /L" (They clicked the "Turn OFF" button)
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(ledPin, LOW);                // Turn the physical LED off
        }
      }
    }
    // Close the connection with the client
    client.stop();
  }
}