# ESP8266 WiFi Weather Station
A real-time IoT Weather Station built using ESP8266 NodeMCU and a 20x4 I2C LCD. This project connects to the internet through WiFi, fetches live weather information from WeatherAPI, processes JSON data, and displays environmental information on the LCD screen with a clean monitoring interface and animated loading system.

## Project Overview
This project demonstrates how an ESP8266 microcontroller can communicate with an online weather server through HTTP requests and display real-time weather information on an LCD module. The system automatically connects to WiFi, sends requests to WeatherAPI, receives weather data in JSON format, extracts important environmental parameters, and continuously updates the display every 5 minutes.
The project combines embedded systems, IoT communication, API handling, JSON parsing, and LCD interfacing into a single weather monitoring system.

## Features
1. Real-time WiFi-based weather monitoring
2. Temperature display in Celsius and Fahrenheit
3. Feels like temperature monitoring
4. Humidity monitoring
5. UV Index monitoring
6. Air Quality Index display
7. Precipitation measurement
8. Automatic WiFi reconnection
9. Animated loading interface during API communication
10. Error handling for API and JSON failures
11. 20x4 I2C LCD visualization system
12. Automatic data refresh every 5 minutes
13. Serial Monitor debugging support

## Hardware Requirements
1. ESP8266 NodeMCU
2. 20x4 I2C LCD Display
3. Jumper wires
4. Breadboard (optional)
5. WiFi internet connection
6. USB cable for programming

## Software Requirements
1. Arduino IDE
2. ESP8266 Board Package
3. WeatherAPI account and API key

## Libraries Used
Install the following libraries from Arduino Library Manager:
1. LiquidCrystal_I2C
2. ArduinoJson
3. ESP8266WiFi
4. Wire

## Wiring Diagram

| LCD I2C | ESP8266 NodeMCU |
|----------|----------------|
| VCC      | 3V3 / VIN      |
| GND      | GND            |
| SDA      | D2 (GPIO4)     |
| SCL      | D1 (GPIO5)     |

## Configuration
### Add Your WiFi Credentials

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
Replace the API key inside the code:
const String apiKey = "YOUR_API_KEY";
Set Your Location
const String location = "Dhaka";

### How The System Works
When the ESP8266 powers on, the LCD initializes and displays the WiFi connection process. The microcontroller attempts to connect to the configured wireless network using the provided SSID and password. After establishing a successful internet connection, the ESP8266 creates an HTTP request and sends it to the WeatherAPI server. The API request contains the user's API key and selected location.

Example API Request:
/v1/current.json?key=YOUR_API_KEY&q=Dhaka&aqi=yes

The WeatherAPI server responds with live environmental data in JSON format. The ESP8266 receives this JSON response and processes it using the ArduinoJson library. The system extracts multiple environmental parameters from the JSON response, including:
1. Current temperature
2. Feels like temperature
3. Humidity
4. UV Index
5. Air Quality Index
6. Precipitation level

The extracted data is then formatted and displayed on the 20x4 LCD screen.
During API communication, the LCD displays an animated loading bar to indicate background data processing and server communication.
If WiFi disconnects or the API server fails to respond, the system automatically displays an error message and attempts reconnection.
The weather information refreshes automatically every 5 minutes to maintain updated environmental monitoring.

### LCD Display Information
Line 1: Current Temperature in Celsius and Fahrenheit

Example:
Temp: 31.2C | 88.1F

Line 2: Feels Like Temperature

Example:
Feels: 35.4C | 95.7F

Line 3: Air Quality Index and Precipitation

Example:
AQI: 82 Moderate | 0.2mm

Line 4: Humidity and UV Index

Example:
Humidity: 78% | UV: 6.4
AQI Classification System

### The project converts AQI values into readable environmental conditions.
AQI Value	Air Quality
0 - 50	Good
51 - 100	Moderate
101 - 150	Unhealthy
151 - 200	Very Unhealthy
200+	Hazardous
Error Handling System

### The project includes multiple error-handling mechanisms:
1. WiFi disconnection detection
2. Automatic WiFi reconnection
3. API timeout detection
4. JSON parsing error detection
5. LCD error notifications
6. Serial Monitor debugging messages
7. Serial Monitor Output
8. The Serial Monitor displays debugging and connection information, including:
9. WiFi connection status
10. IP Address
11. API connection errors
12. JSON parsing errors
13. Server timeout information

### Technologies Used
1. ESP8266 IoT Development
2. Arduino Embedded C++
3. REST API Communication
4. JSON Data Parsing
5. I2C LCD Communication
6. Embedded Systems Programming
7. Internet of Things


### My Future Improvements for this project
1. Add local environmental sensors such as DHT11 or DHT22
2. Add OLED display support
3. Create a web dashboard interface
4. Develop an Android monitoring application
5. Add weather forecasting support
6. Store weather history logs
7. Add MQTT cloud communication
8. Add buzzer-based severe weather alerts
