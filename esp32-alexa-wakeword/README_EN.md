# 🎤 ESP32-S3 Alexa Wake Word Detector

A simple project to test the "Alexa" wake word on ESP32-S3 using INMP441 (I2S) microphone and ESP-SR libraries.

## 📋 Requirements

### Hardware
- **ESP32-S3** Development Board (with USB)
- **INMP441** I2S MEMS Microphone
- Dupont wires for connections
- LED (optional) + 220Ω resistor
- USB cable for programming and power

### Software
- **ESP-IDF** v5.0 or newer
- **Python 3.8+** (for running scripts)
- **VSCode** with Espressif IDF extension (optional)

## 🔌 Hardware Connections

### INMP441 → ESP32-S3

| INMP441 Pin | ESP32-S3 Pin | Description |
|-------------|--------------|-------------|
| VCC         | 3.3V         | Power Supply |
| GND         | GND          | Ground |
| SCK (BCLK)  | GPIO18       | I2S Bit Clock |
| L/R (WS)    | GPIO5        | I2S Word Select |
| SD (DATA)   | GPIO4        | I2S Data Input |

### LED (Optional)

| LED Pin | ESP32-S3 Pin | Description |
|---------|--------------|-------------|
| Anode (+) | GPIO2 → 220Ω → LED | Visual Indicator |
| Cathode (-) | GND | Ground |

### Wiring Diagram

```
ESP32-S3                    INMP441
┌─────────┐                ┌─────────┐
│         │                │         │
│  3.3V   ├────────────────┤  VCC    │
│  GND    ├────────────────┤  GND    │
│  GPIO18 ├────────────────┤  SCK    │
│  GPIO5  ├────────────────┤  L/R    │
│  GPIO4  ├────────────────┤  SD     │
│         │                │         │
│  GPIO2  ├───[220Ω]───LED │         │
└─────────┘                └─────────┘
```

## 🚀 Quick Start

### 1. Install ESP-IDF

```bash
# Clone ESP-IDF
git clone -b v5.1 --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh esp32s3

# Activate environment
. ./export.sh
```

### 2. Clone Project

```bash
cd ~/projects
git clone <your-repo-url> esp32-alexa-wakeword
cd esp32-alexa-wakeword
```

### 3. Add ESP-SR Library (Optional - for real detection)

```bash
# Clone ESP-SR into components folder
cd components
git clone https://github.com/espressif/esp-sr.git
cd ..
```

> **Note:** The project works without ESP-SR using a simple energy-based detector. For real "Alexa" detection, ESP-SR must be added.

### 4. Configure Project

```bash
# Set target to ESP32-S3
idf.py set-target esp32s3

# Open configuration menu (optional)
idf.py menuconfig
```

### 5. Build and Flash

#### Method 1: Using Helper Script

```bash
# Use helper script (Linux/Mac)
./tools/flash_and_monitor.sh /dev/ttyUSB0

# Or on Windows
./tools/flash_and_monitor.sh COM3
```

#### Method 2: Manual Commands

```bash
# Build project
idf.py build

# Flash to board (change port for your system)
idf.py -p /dev/ttyUSB0 flash

# Open serial monitor
idf.py -p /dev/ttyUSB0 monitor
```

> **To exit monitor:** Press `Ctrl + ]`

## 📊 Usage

### After Flashing

1. Open serial monitor (`idf.py monitor`)
2. System information and configuration will be displayed
3. Say **"Alexa"** near the microphone
4. On detection:
   - Message printed in monitor: `🎤 WAKE WORD 'ALEXA' DETECTED!`
   - LED blinks 3 times (if connected)

## 🔧 Advanced Configuration

### Change I2S Pins

Edit `main/i2s_config.h`:

```c
#define I2S_BCK_PIN     18  // Change to desired pin
#define I2S_WS_PIN      5
#define I2S_DATA_IN_PIN 4
```

### Change Sample Rate

Edit in `main/i2s_config.h`:

```c
#define SAMPLE_RATE     16000  // 8000, 16000, 44100, etc.
```

## 🐛 Troubleshooting

### Issue: Microphone not reading audio

**Solutions:**
1. Check connections (especially VCC → 3.3V not 5V)
2. Verify I2S pins are correct in code
3. Try reversing L/R (connect to GND or VCC)
4. Check I2S logs in monitor

### Issue: Build error - ESP-SR not found

**Solution:**
```bash
# Ensure ESP-SR exists in components
ls components/esp-sr

# If not present, clone it
cd components
git clone https://github.com/espressif/esp-sr.git
```

## 📁 Project Structure

```
esp32-alexa-wakeword/
├── CMakeLists.txt              # Main CMake configuration
├── sdkconfig.defaults          # Default SDK settings
├── README.md                   # Arabic documentation
├── README_EN.md                # This file
├── main/
│   ├── CMakeLists.txt          # Main component config
│   ├── main.c                  # Main program
│   ├── i2s_config.h            # I2S definitions
│   ├── i2s_config.c            # I2S implementation
│   ├── wake_word_detector.h    # Wake word detector definitions
│   └── wake_word_detector.c    # Detector implementation
├── components/
│   └── esp-sr/                 # ESP-SR library (must be cloned)
└── tools/
    ├── pack_model.py           # Model packing script
    └── flash_and_monitor.sh    # Build and flash script
```

## 📚 References

- [ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [ESP-SR GitHub](https://github.com/espressif/esp-sr)
- [INMP441 Datasheet](https://invensense.tdk.com/products/digital/inmp441/)
- [ESP32-S3 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf)

## 📝 License

This project is licensed under the MIT License - see LICENSE file for details.

---

**Made with ❤️ for the maker community**

🌟 If you like this project, don't forget to give it a star on GitHub!
