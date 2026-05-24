# ESP8266 WiFi Weather Station 

A real-time IoT Weather Station built using ESP8266 NodeMCU and a 20x4 I2C LCD display.  
This project fetches live weather information from WeatherAPI and displays it beautifully on the LCD screen with animated loading effects and environmental details.
## Features
WiFi-based live weather monitoring
Temperature in Celsius & Fahrenheit
 Feels-like temperature display
Humidity monitoring
UV Index display
Air Quality Index (AQI)
Precipitation measurement
Automatic WiFi reconnection
Animated loading interface
Error handling system
20x4 I2C LCD visualization

## Hardware Requirements
 ESP8266 NodeMCU
20x4 I2C LCD Display
Jumper wires
Breadboard (optional)
WiFi connection

## Libraries Used
Install these libraries from Arduino Library Manager:
LiquidCrystal_I2C
ArduinoJson
ESP8266WiFi
Wire

## Wiring Diagram
| LCD I2C | ESP8266 NodeMCU |
|--------|----------------|
| VCC    | 3V3 / VIN      |
| GND    | GND            |
| SDA    | D2 (GPIO4)     |
| SCL    | D1 (GPIO5)     |

## Configuration

### 1. Add Your WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

### 2. Get WeatherAPI Key

Create a free account from:
[![WeatherAPI](https://img.shields.io/badge/API-WeatherAPI-blue)](https://www.weatherapi.com/)

Then replace:

const String apiKey = "YOUR_API_KEY";
### 3. Set Your Location
const String location = "Dhaka";
You can change it to any city or location.

### Display Information
The LCD displays:
Line 1 : Current Temperature (°C & °F)
Line 2 : Feels Like Temperature
Line 3:  AQI Status | Rain/Precipitation
Line 4 : Humidity | UV Index
