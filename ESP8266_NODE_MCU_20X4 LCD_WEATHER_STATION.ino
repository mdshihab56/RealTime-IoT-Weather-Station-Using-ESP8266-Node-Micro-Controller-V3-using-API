#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// Initialize 20x4 LCD (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// WiFi Credentials
const char* ssid = "TP Link C64";
const char* password = "Netgear@shihab1209";

// WeatherAPI Configuration
const String apiKey = "8cc01394f36742d4842180219251205";
const String location = "Dhaka";
const String endpoint = "/v1/current.json?key=" + apiKey + "&q=" + location + "&aqi=yes";

// Loading animation frames
const char* loadingFrames[] = {"[    ]", "[=   ]", "[==  ]", "[=== ]", "[ ===]", "[  ==]", "[   =]", "[    ]"};
int frameIndex = 0;
unsigned long lastFrameTime = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    showLoadingScreen();
    
    String payload = getWeatherData();
    
    if (payload == "ERROR") {
      showError("API Connection Failed", "Retrying...");
      delay(5000);
      return;
    }

    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      showError("Data Parsing Error", "Check Serial Monitor");
      Serial.print("JSON Error: ");
      Serial.println(error.c_str());
      delay(5000);
      return;
    }
    
    // Extract all weather data
    float temp_c = doc["current"]["temp_c"];
    float temp_f = doc["current"]["temp_f"];
    float feelslike_c = doc["current"]["feelslike_c"];
    float feelslike_f = doc["current"]["feelslike_f"];
    int humidity = doc["current"]["humidity"];
    float uv = doc["current"]["uv"];
    int aqi = doc["current"]["air_quality"]["us-epa-index"];
    float precip_mm = doc["current"]["precip_mm"];

    // Display weather data
    displayWeather(temp_c, temp_f, feelslike_c, feelslike_f, humidity, uv, aqi, precip_mm);
    
    delay(300000); // 5-minute delay between updates
  } else {
    showError("WiFi Disconnected", "Reconnecting...");
    WiFi.reconnect();
    delay(5000);
  }
}

void connectToWiFi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi:");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 3);
    lcd.print("Status: ");
    lcd.print(WiFi.status());
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  lcd.setCursor(0, 1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());
  delay(2000);
}

String getWeatherData() {
  WiFiClient client;
  String payload = "";
  
  if (client.connect("api.weatherapi.com", 80)) {
    client.print(String("GET ") + endpoint + " HTTP/1.1\r\n");
    client.print("Host: api.weatherapi.com\r\n");
    client.print("Connection: close\r\n\r\n");
    
    // Wait for response with timeout
    unsigned long startTime = millis();
    while (!client.available() && millis() - startTime < 10000) {
      updateLoadingAnimation();
      delay(100);
    }
    
    if (!client.available()) {
      Serial.println("API Timeout!");
      client.stop();
      return "ERROR";
    }
    
    // Skip headers
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") break;
    }
    
    // Get payload
    while (client.available()) {
      payload = client.readStringUntil('\n');
    }
  } else {
    Serial.println("Connection failed!");
    return "ERROR";
  }
  
  client.stop();
  return payload;
}

void showLoadingScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fetching Weather Data");
  lastFrameTime = millis();
}

void updateLoadingAnimation() {
  if (millis() - lastFrameTime > 200) { // Update every 200ms
    frameIndex = (frameIndex + 1) % 8;
    lcd.setCursor(7, 2);
    lcd.print(loadingFrames[frameIndex]);
    lastFrameTime = millis();
  }
}

void displayWeather(float temp_c, float temp_f, float feelslike_c, float feelslike_f, 
                   int humidity, float uv, int aqi, float precip_mm) {
  lcd.clear();
  
  // Line 1: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp_c, 1);
  lcd.print("C | ");
  lcd.print(temp_f, 1);
  lcd.print("F");
  
  // Line 2: Feels Like
  lcd.setCursor(0, 1);
  lcd.print("Feels: ");
  lcd.print(feelslike_c, 1);
  lcd.print("C | ");
  lcd.print(feelslike_f, 1);
  lcd.print("F");
  
  // Line 3: AQI and Precipitation
  lcd.setCursor(0, 2);
  lcd.print("AQI: ");
  lcd.print(aqi);
  lcd.print(" (");
  lcd.print(getAQIQuality(aqi));
  lcd.print(") | ");
  lcd.print(precip_mm);
  lcd.print("mm");
  
  // Line 4: Humidity and UV
  lcd.setCursor(0, 3);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("% | UV: ");
  lcd.print(uv, 1);
}

String getAQIQuality(int aqi) {
  if (aqi <= 50) return "Good";
  else if (aqi <= 100) return "Moderate";
  else if (aqi <= 150) return "Unhealthy";
  else if (aqi <= 200) return "Very Unhealthy";
  else return "Hazardous";
}

void showError(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(line1);
  lcd.setCursor(0, 2);
  lcd.print(line2);
}