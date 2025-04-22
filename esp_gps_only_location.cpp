#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <SD.h>

// Pin definitions
#define TFT_CS     15
#define TFT_RST    2
#define TFT_DC     4
#define SD_CS      5  // Chip select for SD card

// Create the display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Create a GPS object
TinyGPSPlus gps;
HardwareSerial mySerial(1); // Use Serial1 for GPS

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX for GPS
  
  // Initialize the display
  tft.begin();
  tft.setRotation(1); // Set to landscape mode
  tft.fillScreen(ILI9341_BLACK);
  
  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");

  // Display initial message
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 30);
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
      tft.fillRect(30, 30, 200, 80, ILI9341_BLACK); // Clear the waiting message area
      
      if (gps.location.isUpdated()) {
        // Clear the waiting message area
        tft.fillRect(30, 30, 200, 20, ILI9341_BLACK); // Clear just the waiting message area
        
        // Display latitude and longitude
        tft.setCursor(30, 50);
        tft.print("Lat: ");
        tft.println(gps.location.lat(), 6);
        tft.setCursor(30, 80);
        tft.print("Lng: ");
        tft.println(gps.location.lng(), 6);

        // Load and display the map
        displayMap();
      } else {
        tft.setCursor(30, 30);
        tft.print("Waiting for GPS signal...");
      }
    }
  }
}

void displayMap() {
  // Open the map file
  File mapFile = SD.open("map.bmp");
  if (!mapFile) {
    Serial.println("Error opening map file");
    return;
  }

  // Read and display the BMP file
  if (drawBitmap(mapFile, 0, 0)) {
    Serial.println("Map displayed successfully.");
  } else {
    Serial.println("Failed to display map.");
  }

  mapFile.close();
}

bool drawBitmap(File &f, int x, int y) {
  // BMP file header
  if (f.read() != 'B' || f.read() != 'M') {
    return false; // Not a BMP file
  }

  // Skip BMP file header
  f.seek(18); // Width
  int w = f.read() | (f.read() << 8);
  int h = f.read() | (f.read() << 8);
  f.seek(28); // Bits per pixel
  int bpp = f.read() | (f.read() << 8);
  
  if (bpp != 24) {
    return false; // Only support 24-bit BMP
  }

  // Skip to pixel data
  f.seek(54);
  
  // Read pixel data and display
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      uint8_t b = f.read(); // Blue
      uint8_t g = f.read(); // Green
      uint8_t r = f.read(); // Red
      tft.drawPixel(x + i, y + (h - j - 1), tft.color565(r, g, b));
    }
  }
  
  return true;
}
