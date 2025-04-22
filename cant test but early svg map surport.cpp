#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TinyGPS++.h>
#include <SD.h>

// Pin definitions
#define TFT_CS     15
#define TFT_RST    4
#define TFT_DC     2
#define SD_CS      5

// Create display and GPS objects
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
TinyGPSPlus gps;

// Function to convert GPS coordinates to screen coordinates
void gpsToScreen(float lat, float lon, int &x, int &y) {
    // Simple conversion for demonstration; adjust based on your map scale
    x = map(lon, -180, 180, 0, tft.width());
    y = map(lat, -90, 90, tft.height(), 0); // Invert y for screen coordinates
}

// Function to draw a simple vector line (for demonstration)
void drawLine(int x1, int y1, int x2, int y2) {
    tft.drawLine(x1, y1, x2, y2, ILI9341_WHITE);
}

// Function to load and draw a map segment from SD card
void drawMapSegment() {
    // Example: Draw a hardcoded line segment
    // In a real implementation, you would read vector data from a file
    drawLine(50, 50, 150, 150); // Example line
}

// Setup function
void setup() {
    Serial.begin(9600);
    tft.begin();
    tft.setRotation(3); // Adjust based on your setup
    tft.fillScreen(ILI9341_BLACK);

    if (!SD.begin(SD_CS)) {
        Serial.println("SD card initialization failed!");
        return;
    }
    
    // Draw the initial map segment
    drawMapSegment();
}

// Main loop
void loop() {
    while (Serial.available() > 0) {
        gps.encode(Serial.read());
        
        if (gps.location.isUpdated()) {
            float lat = gps.location.lat();
            float lon = gps.location.lng();
            int x, y;
            gpsToScreen(lat, lon, x, y);

            // Clear the previous position
            tft.fillCircle(tft.width()/2, tft.height()/2, 5, ILI9341_BLACK);
            // Draw the current position
            tft.fillCircle(x, y, 5, ILI9341_RED);
        }
    }
}
