#include <WiFi.h>        // Library to handle Wi-Fi functionality
#include <WebServer.h>   // Simple web server library for ESP32
#include <DHT.h>         // Library for DHT sensor

// Define the pin where the DHT sensor is connected
#define DHTPIN 4       

// Define the type of DHT sensor (DHT11 or DHT22)
#define DHTTYPE DHT11   

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Create a web server object that listens on port 80
WebServer server(80);    // default port for http traffic

// Wi-Fi credentials (used for Access Point mode)
const char* ssid = "ESP32_Humidity_AP";  // Name of the ESP32 Wi-Fi network
const char* password = "12345678";       // Password for the AP

// HTML page -- done by shahsi
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Humidity Data Display</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; }
        .humidity-container { width: 80%; margin: auto; background: #ddd; height: 50px; border-radius: 10px; overflow: hidden; }
        .humidity-strip { width: 0%; height: 100%; background-color: #009688; transition: width 0.5s ease-in-out; }
    </style>
</head>
<body>
    <h1>Humidity Data Project</h1>
    <h3>Team Name: Esp32 Humidity Webserver</h3>
    <h3>Team Members: Keval, Shashi, Adarsh</h3>
    
    <div class="humidity-container">
        <div class="humidity-strip" id="humidity-bar"></div>
    </div>
    <h2 id="humidity-value">Humidity: --%</h2>
    
    <script>
        async function fetchHumidity() {
            try {
                // Fetch the humidity data from the ESP32 server
                const response = await fetch('/humidity');
                const data = await response.json();
                
                // Update the displayed humidity value
                document.getElementById('humidity-value').innerText = `Humidity: ${data.humidity}%`;
                
                // Update the progress bar width based on humidity value
                document.getElementById('humidity-bar').style.width = `${data.humidity}%`;
            } catch (error) {
                console.error('Error fetching humidity:', error);
            }
        }
        
        // Fetch humidity data every 5 seconds
        setInterval(fetchHumidity, 5000);
    </script>
</body>
</html>
)rawliteral";

// Function to handle the root webpage request
void handleRoot() {
    server.send(200, "text/html", index_html);
}

// Function to handle the humidity data request
void handleHumidity() {
    float humidity = dht.readHumidity();  // Read humidity from the sensor

    // Check if the reading is valid
    if (isnan(humidity)) {
        server.send(500, "text/plain", "Failed to read from sensor");  // Return an error response
        return;
    }

    // Create a JSON response
    String jsonResponse = "{\"humidity\":" + String(humidity) + "}";
    
    // Send the JSON response back to the client
    server.send(200, "application/json", jsonResponse);  //jSon beacuse its lightwieght and stable
}

void setup() {
    Serial.begin(115200);  // Start the serial monitor for debugging

    // Initialize Wi-Fi in Access Point (AP) mode
    WiFi.softAP(ssid, password);
    
    // Print the AP details in Serial Monitor
    Serial.println("ESP32 AP Mode Started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());   //prints ip address

    dht.begin();  // Start the DHT sensor

    // Define server routes
    server.on("/", handleRoot);         // Serve the HTML page
    server.on("/humidity", handleHumidity);  // Serve humidity data in JSON format

    server.begin();  // Start the server
}

void loop() {
    server.handleClient();  // Handle client requests
}
// hardware and software work done by keval and Adarsh
