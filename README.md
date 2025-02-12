# ESP32 Humidity Web Server

This project sets up an **ESP32 as a Wi-Fi access point** that hosts a **web server** to display real-time humidity data from a **DHT11** sensor.

## Features
- **ESP32 SoftAP Mode**: Creates a local Wi-Fi network
- **DHT11 Sensor Integration**: Reads humidity data
- **Web Dashboard**: Displays real-time humidity with a progress bar
- **JSON API Endpoint**: Serves humidity data in JSON format
- **Auto Refresh**: Updates every 5 seconds

## Hardware Requirements
- ESP32 Devkit V1
- DHT11 Humidity Sensor
- Jumper Wires
- Power Source (USB or Battery Pack)

## Pin Configuration
| Component  | ESP32 Pin |
|------------|-----------|
| DHT11 Data | GPIO 4    |
| VCC        | 3.3V      |
| GND        | GND       |

## Software & Libraries
- **Arduino IDE** (or PlatformIO)
- **ESP32 Board Package**
- Libraries:
  - `WiFi.h` → Enables ESP32's Wi-Fi
  - `WebServer.h` → Runs the web server
  - `DHT.h` → Reads sensor data

## Installation
1. **Clone the Repository:**
   ```sh
   git clone https://github.com/shashi4030/HumidityWebServer.git
   cd esp32-humidity-webserver
   ```

2. **Install Required Libraries:**
   - Open Arduino IDE
   - Go to **Sketch > Include Library > Manage Libraries**
   - Search for and install `DHT sensor library` and `ESP32 WebServer`.

3. **Upload the Code to ESP32:**
   - Connect the ESP32 to your PC via USB
   - Select **ESP32 Dev Module** as the board
   - Compile and upload the code

## Usage
1. **Power on the ESP32**
2. **Connect to the Wi-Fi network**: `ESP32_Humidity_AP` (Password: `12345678`)
3. **Open a browser** and go to `192.168.4.1`
4. **View real-time humidity updates!**

## API Endpoints
| Endpoint      | Description |
|--------------|------------|
| `/`          | Serves the HTML web page |
| `/humidity`  | Returns humidity data in JSON |

Example JSON response from `/humidity`:
```json
{ "humidity": 56.7 }
```


**Team**:Adarsh,keval and shashi

