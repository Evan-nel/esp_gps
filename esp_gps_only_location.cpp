#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Pin definitions based on your wiring
#define TFT_CS     15
#define TFT_RST    2
#define TFT_DC     4

// Create the display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Create a GPS object
TinyGPSPlus gps;
HardwareSerial mySerial(1); // Use Serial1 for GPS

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX for GPS
  
  // Initialize the display
  tft.begin();
  tft.setRotation(1); // Set to landscape mode
  tft.fillScreen(ILI9341_BLACK);
  
  // Set text color and size
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  // Display initial message higher up on the screen
  tft.setCursor(30, 30); // Move the cursor higher for waiting message
  tft.print("Waiting for GPS signal...");
}

void loop() {
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read());
    
    // Update the display every second
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 1000) {
      lastUpdate = millis();

      // Clear the previous location
      tft.fillRect(30, 30, 200, 80, ILI9341_BLACK); // Clear the area for waiting message
      
      if (gps.location.isUpdated()) {
        // Clear the waiting message area
        tft.fillRect(30, 30, 200, 20, ILI9341_BLACK); // Clear just the waiting message area
        
        // Display latitude and longitude
        tft.setCursor(30, 50); // Position for latitude
        tft.print("Lat: ");
        tft.println(gps.location.lat(), 6); // 6 decimal places
        tft.setCursor(30, 80); // Position for longitude
        tft.print("Lng: ");
        tft.println(gps.location.lng(), 6); // 6 decimal places

        // Display altitude if available
        if (gps.altitude.isUpdated()) {
          tft.setCursor(30, 110); // Position for altitude
          tft.print("Alt: ");
          tft.println(gps.altitude.meters(), 2); // Display altitude in meters
        }

        // Display number of satellites
        tft.setCursor(30, 140); // Position for satellites
        tft.print("Satellites: ");
        tft.println(gps.satellites.value()); // Display number of satellites
      } else {
        // If GPS data is not updated, show waiting message
        tft.setCursor(30, 30); // Keep the waiting message higher
        tft.print("Waiting for GPS signal...");
      }
    }
  }
}
