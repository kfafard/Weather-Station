# Weather Station 🌦️

This project is a Wi-Fi-enabled weather station built using the Arduino UNO R4 WiFi board and PlatformIO. It reads environmental data from connected sensors and transmits the information to the cloud.

## 🚀 Features

- 📡 Wi-Fi connectivity using UNO R4 WiFi
- 🌡️ Temperature and pressure readings via BMP280 sensor
- ☀️ Light detection (optional, depending on connected hardware)
- 🧪 Air quality measurement via MQ-135 (if connected)
- 📊 Remote data logging (e.g., ThingSpeak)
- 💾 Built with PlatformIO for modularity and ease of development

## 🧰 Hardware Requirements

- Arduino UNO R4 WiFi
- Adafruit BMP280 (or compatible)
- MQ-135 air quality sensor *(optional)*
- LDR light sensor *(optional)*
- Other I2C/SPI compatible sensors as needed
- USB cable for programming
- Wi-Fi access point

## 📦 Software Requirements

- [PlatformIO](https://platformio.org/)
- VS Code or compatible editor
- Git

## 🛠️ Setup Instructions

1. **Clone this repository**:
   ```bash
   git clone git@github.com:kfafard/Weather-Station.git
   cd Weather-Station
   ```

2. **Install PlatformIO**:
   Follow instructions at: https://platformio.org/install

3. **Configure secrets**:
   Create a file at `include/secrets.h`:
   ```cpp
   #define WIFI_SSID "YourNetwork"
   #define WIFI_PASS "YourPassword"
   #define THINGSPEAK_API_KEY "YourThingSpeakKey"
   ```

4. **Build and upload**:
   ```bash
   pio run --target upload
   ```

5. **Monitor the serial output**:
   ```bash
   pio device monitor
   ```

## 📁 File Structure

```
Weather-Station/
├── include/            # Header files (e.g., secrets.h)
├── lib/                # Custom libraries (if added)
├── src/                # Source code (main.cpp)
├── .pio/               # PlatformIO build system (auto-generated)
├── platformio.ini      # Project config
└── README.md           # This file
```

## 📡 Cloud Integration

This project supports uploading data to ThingSpeak. To use it:
- Create an account at https://thingspeak.com
- Create a new channel and note your **Write API Key**
- Add the key to `secrets.h` as shown above

## 📜 License

This project is open-source under the MIT License.

## 🙌 Credits

Built by [@kfafard](https://github.com/kfafard) using PlatformIO and Arduino libraries.