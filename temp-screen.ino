#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <GxEPD2_BW.h> // Include the correct library for your e-paper display model
#include <Fonts/FreeMonoBold9pt7b.h> // Including a font for display
#include "credentials.h"

// E-paper display initialization
// GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=*/5, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));
GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=*/5, /*DC=*/17, /*RST=*/16, /*BUSY=*/4)); // DEPG0213BN 122x250, SSD1680

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  display.init();
}

String fetchTemperature() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(ha_url);
    http.addHeader("Authorization", token);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      http.end(); // Close connection
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      String temperature = doc["state"].as<String>(); // Extract temperature
      Serial.println(temperature); // Debugging: print temperature
      return temperature;
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      http.end(); // Close connection
      return "Error";
    }
  } else {
    return "WiFi Disconnected";
  }
}

void loop() {
  String temperature = fetchTemperature() + "°C"; // Fetch and prepare the temperature string

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE); // Clear the screen to white
    display.setTextColor(GxEPD_BLACK); // Set the text color to black

    // Set font; this also affects spacing and alignment
    display.setFont(&FreeMonoBold9pt7b);

    int16_t tbx, tby; // Text box x and y positions
    uint16_t tbw, tbh; // Text box width and height
    String text = "Temp: " + temperature + "°C"; // Concatenate temperature value

    // Calculate width and height of the text to center it
    display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);

    // Calculate x and y to center the text
    int x = (display.width() - tbw) / 2;
    int y = (display.height() + tbh) / 2;

    display.setCursor(x, y); // Set cursor to calculated position
    display.print(text); // Print the text

    display.display(); // Make sure to update the display to show changes
  } while (display.nextPage());

  delay(60000); // Update every 60 seconds
}
