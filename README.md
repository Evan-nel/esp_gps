# 🌍 ESP32 Portable GPS

**Note:** As of now, the project has only been tested in an emulator environment.

## 📖 Overview
The GPS Map Project aims to create a portable mapping solution using an ESP32 microcontroller, GPS module, and ILI9341 display. This project enables users to view and interact with vector-based maps stored on an SD card, providing functionalities such as zooming and panning based on GPS coordinates.

## 🛠️ Components
- **ESP32:** Main microcontroller for processing and connectivity.
- **GPS Module:** Obtains location data (latitude and longitude).
- **ILI9341 Display:** TFT display for rendering the map interface.
- **SD Card Module:** Stores and reads vector map data.
- **Power Supply:** Battery or USB power for portability.

## ✨ Features
- Display vector-based maps from data stored on an SD card.
- Show current GPS coordinates (latitude and longitude).
- Interactive features such as zooming and panning on the map.
- Visual enhancements for an improved user experience.

## 📅 Project Plan
### Phase 1: Setup and Basic Functionality
- **Hardware Integration:**
  - Connect the ESP32, GPS module, and ILI9341 display.
  - Test basic functionality to display GPS coordinates.
- **Basic Display:**
  - Create a simple interface to show latitude and longitude.
  - Implement error handling for GPS data retrieval.

### Phase 2: Map Integration
- **SD Card Setup:**
  - Connect an SD card module to the ESP32.
  - Implement functionality to read vector map data from the SD card.
- **Vector Data Loading:**
  - Define a custom vector format or use GeoJSON for map data.
  - Implement parsing logic to read vector data from the SD card.
- **Map Rendering:**
  - Draw basic vector shapes (lines, polygons) on the display based on GPS coordinates.

### Phase 3: User Interaction
- **Zoom and Pan:**
  - Implement zooming functionality for detailed map views.
  - Add panning capabilities to navigate around the map.
- **Visual Enhancements:**
  - Improve the layout and design of the display.
  - Add icons or markers for specific locations.

### Phase 4: Testing and Optimization
- **Field Testing:**
  - Test functionality in various environments to ensure accuracy and reliability.
  - Gather user feedback for further improvements.
- **Performance Optimization:**
  - Optimize code for speed and efficiency.
  - Reduce memory usage and improve power management.

## 🚀 Future Enhancements
Implement additional features such as:
- Offline map storage and usage.
- Integration with other sensors (e.g., compass, accelerometer).
- User settings for customization (e.g., units, themes).

## 🛠️ Getting Started
### Prerequisites
- Arduino IDE installed.
- Required Libraries:
  - Adafruit ILI9341
  - Adafruit GFX
  - TinyGPS++
  - SD

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Evan-nel/esp_gps
