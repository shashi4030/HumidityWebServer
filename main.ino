#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4        // Pin where the DHT sensor is connected
#define DHTTYPE DHT11   // Type of DHT sensor (DHT11 or DHT22)

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

const char* ssid = "ESP32_Humidity_AP";  // Name of the ESP32 Wi-Fi network
const char* password = "12345678";       // Password for the AP

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
    <h3>Team Name: Esp01 Humidity Webserver</h3>
    <h3>Team Members: Keval, Shashi, Adarsh</h3>
    
    <div class="humidity-container">
        <div class="humidity-strip" id="humidity-bar"></div>
    </div>
    <h2 id="humidity-value">Humidity: --%</h2>
    
    <script>
        async function fetchHumidity() {
            try {
                const response = await fetch('/humidity');
                const data = await response.json();
                document.getElementById('humidity-value').innerText = `Humidity: ${data.humidity}%`;
                document.getElementById('humidity-bar').style.width = `${data.humidity}%`;
            } catch (error) {
                console.error('Error fetching humidity:', error);
            }
        }
        setInterval(fetchHumidity, 5000);
    </script>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", index_html);
}

void handleHumidity() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        server.send(500, "text/plain", "Failed to read from sensor");
        return;
    }
    String jsonResponse = "{\"humidity\":" + String(humidity) + "}";
    server.send(200, "application/json", jsonResponse);
}

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.println("ESP32 AP Mode Started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    
    dht.begin();
    
    server.on("/", handleRoot);
    server.on("/humidity", handleHumidity);
    server.begin();
}

void loop() {
    server.handleClient();
}