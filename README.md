# Temperature Display Project
This Arduino project displays the current temperature from a Home Assistant sensor on an e-paper display using an ESP32. It demonstrates fetching data from a Home Assistant API and handling WiFi connectivity to update an e-paper screen regularly.

## Features
 - Fetches temperature data from a Home Assistant instance via REST API.
 - Displays the temperature on an e-paper display module.
 - Dynamically updates the display every 60 seconds.
 - Utilizes WiFi connectivity for network requests.
 - Separates sensitive information (WiFi and API credentials) into a credentials.h file for better security and modularity.

## Hardware Requirements
 - ESP32 Development Board
 - E-paper display module (GxEPD2 compatible)
 - Appropriate connecting cables

## Software Requirements
Arduino IDE with Libraries:
 - WiFi
 - HTTPClient
 - ArduinoJson
 - GxEPD2 for e-paper displays
 - Fonts (e.g., FreeMonoBold9pt7b)

## Setup
 - Clone the Repository: Clone this repository to your local machine or download the source code.
``` bash
git clone <https://github.com/OriAshkenazi/temp-screen-ha.git>
```
 - Install Required Libraries: Ensure all required libraries are installed in your Arduino IDE. You can install these through the Library Manager in the Arduino IDE.
 - Credentials File: Create a credentials.h file in the same directory as your temp-screen.ino sketch with the following structure, replacing placeholder values with your actual credentials:
``` cpp
// credentials.h

// WiFi credentials
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Home Assistant API details
#define HA_URL "your_home_assistant_url/api/states/sensor.your_sensor"
#define HA_TOKEN "Bearer your_long_lived_access_token"
```
 - Upload the Sketch: Open temp-screen.ino with the Arduino IDE, select your ESP32 board, and upload the sketch.
Power and Watch: Power your ESP32 board and watch the e-paper display update with the current temperature.

### Note
This project is designed for educational purposes and serves as a template for IoT projects utilizing ESP32 and e-paper displays. Ensure that your Home Assistant instance is properly configured to provide temperature data via its REST API.
