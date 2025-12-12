# JWS Murottal V4.2 - Smart Mosque Controller

[![ESP8266](https://img.shields.io/badge/ESP8266-1.0.6-blue.svg)](https://github.com/esp8266/Arduino)
[![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-1.8.19-green.svg)](https://www.arduino.cc/en/software)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**JWS Murottal V4.2** adalah sistem kontroler masjid cerdas berbasis ESP8266 yang dirancang untuk mengelola jadwal sholat, audio murottal, tampilan LED, dan berbagai fitur otomatisasi masjid lainnya. Sistem ini menyediakan antarmuka web modern untuk konfigurasi dan kontrol real-time.

## ✨ Fitur Utama

### 🎵 **Audio System**
- **DFPlayer Mini** untuk pemutaran murottal Al-Quran
- **30 level volume** dengan kontrol real-time
- **Multiple playlists** (Saad Alghamdi, Mishary Rasyid, dll)
- **6 preset equalizer** (Normal, Pop, Rock, Jazz, Classic, Bass)
- **Media controls** lengkap (Play, Pause, Stop, Next, Previous, Random)

### 🖥️ **Display System**
- **P10 LED Matrix** (2x1 panel, 64x16 pixel)
- **Dual font support** (Latin & Arabic)
- **Automatic brightness dimming** berdasarkan jadwal
- **Multiple display modes** (Jam, Audio, Test LED)
- **Scrolling text** untuk informasi masjid

### 🕋 **Prayer Management**
- **Automatic prayer times calculation** menggunakan algoritma Karachi
- **Per-prayer configuration** (enable/disable, time correction)
- **Iqomah countdown** dengan durasi yang dapat dikonfigurasi
- **Adzan playback** dengan durasi yang dapat disesuaikan
- **Tanbih & Imsak** reminder

### 🌐 **Web Interface**
- **Modern responsive UI** dengan dark theme
- **Real-time WebSocket** communication
- **Mobile-friendly** design
- **Live monitoring** (heap memory, temperature, connection status)
- **Configuration panels** untuk semua settings

### 📡 **Connectivity**
- **Dual WiFi mode** (AP + Station simultaneous)
- **Auto-reconnect** dengan fallback ke AP mode
- **WebSocket server** (port 81) untuk real-time control
- **HTTP server** (port 80) untuk web interface
- **DNS captive portal** untuk setup awal

### ⚙️ **System Features**
- **SPIFFS file system** untuk penyimpanan konfigurasi
- **Watchdog timer** (60 detik timeout) untuk stability
- **Message queue system** untuk non-blocking operations
- **RTC DS3231** untuk timekeeping akurat
- **Temperature monitoring** dari RTC sensor

## 🛠️ Hardware Requirements

### Komponen Utama
- **ESP8266 NodeMCU** (ESP-12E)
- **RTC DS3231** module (I2C)
- **DFPlayer Mini** MP3 module
- **P10 LED Matrix** (2 panel, 32x16 pixel each)
- **HJS589 LED driver** board
- **Buzzer** (connected to GPIO3/RX)
- **MicroSD card** untuk audio files

### Pin Configuration
```cpp
// ESP8266 Pin Mapping
#define BUZZER_PIN      3   // GPIO3 (RX) - Buzzer
#define SDA_PIN         4   // GPIO4 - I2C SDA (RTC)
#define SCL_PIN         5   // GPIO5 - I2C SCL (RTC)
#define DFPLAYER_TX     1   // GPIO1 (TX) - DFPlayer Serial
#define DFPLAYER_RX     3   // GPIO3 (RX) - DFPlayer Serial (shared with buzzer)
```

### Power Requirements
- **Input Voltage:** 5V DC
- **Current Draw:** 2-3A (tergantung brightness LED)
- **Recommended PSU:** 5V 2A adapter

## 📚 Software Requirements

### Arduino IDE Setup
```bash
# Required Libraries (install via Library Manager)
ESP8266WiFi           # v2.7.4
ESP8266WebServer      # v1.0.0
WebSocketsServer      # v1.0.0
ArduinoJson           # v6.21.2
RtcDS3231             # v2.0.0
DFMiniMp3             # v1.0.5
HJS589                # Custom library
PrayerTimes           # Custom library
```

### Board Configuration
- **Board:** NodeMCU 1.0 (ESP-12E Module)
- **Upload Speed:** 115200
- **CPU Frequency:** 80 MHz
- **Flash Size:** 4MB (FS:2MB, OTA:~1019KB)

## 🚀 Installation & Setup

### 1. Hardware Assembly
1. Hubungkan RTC DS3231 ke I2C pins (SDA: GPIO4, SCL: GPIO5)
2. Hubungkan DFPlayer Mini ke Serial pins (TX: GPIO1, RX: GPIO3)
3. Hubungkan P10 LED Matrix ke HJS589 driver
4. Hubungkan buzzer ke GPIO3
5. Masukkan MicroSD card dengan audio files

### 2. Audio Files Structure
```
SD Card Root:
├── 01/           # Saad Alghamdi
│   ├── 001.mp3   # Al-Fatihah
│   ├── 002.mp3   # Al-Baqarah
│   └── ...
├── 02/           # Mishary Rasyid
├── 03/           # Juz Amma - Saad
└── 04/           # Adzan files
    ├── 001.mp3   # Adzan
    └── 002.mp3   # Iqomah beep
```

### 3. Arduino IDE Setup
1. Install ESP8266 board support
2. Install required libraries
3. Open `jws_v42.ino`
4. Configure WiFi credentials di `WebServer_V4.h`
5. Upload sketch ke ESP8266

### 4. First Boot Configuration
1. Device akan boot dalam AP mode
2. Connect ke WiFi "JWS" (password: 1234567890)
3. Akses `http://192.168.4.1`
4. Configure WiFi settings untuk connect ke router
5. Set location coordinates dan timezone
6. Configure prayer times dan audio settings

## 📖 Usage Guide

### Web Interface Access
- **AP Mode:** `http://192.168.4.1`
- **WiFi Mode:** `http://[ESP8266_IP_ADDRESS]`

### Main Sections

#### 🎵 Audio Control
- Set volume (0-30)
- Select playlist
- Choose equalizer preset
- Control playback (Play/Pause/Stop/Next/Prev/Random)

#### 🖥️ Display Settings
- Adjust brightness (15-254)
- Configure panel count (1-2)
- Set dimming schedule
- Switch display modes

#### 🕌 Mosque Information
- Set mosque name
- Configure scrolling text (2 lines)
- Update location info

#### 🕋 Prayer Schedule
- Enable/disable individual prayers
- Set time corrections per prayer
- Configure iqomah duration
- Set adzan duration

#### 📍 Location & Time
- Set date/time manually
- Configure latitude/longitude
- Set timezone offset
- Use coordinate finder tool

#### 📡 WiFi Configuration
- Station mode (connect to existing WiFi)
- Access Point mode (create hotspot)
- Auto-reconnect settings

## 🔧 API Documentation

### WebSocket Commands

#### Audio Control
```javascript
// Volume control
ws.send('#{"volume": 20}');

// Media controls
ws.send('dplay');      // Play
ws.send('dpause');     // Pause
ws.send('dstop');       // Stop
ws.send('dnext');      // Next track
ws.send('dprev');      // Previous track
ws.send('drandom');    // Random play

// Playlist selection
ws.send('p1');         // All Quran
ws.send('p2');         // Saad Alghamdi
ws.send('p3');         // Juz Amma - Saad

// Equalizer
ws.send('e1');         // Normal
ws.send('e2');         // Pop
ws.send('e6');         // Bass
```

#### Display Control
```javascript
// Brightness & panel config
ws.send('c{"kecerahan": 150, "panel": 2}');

// Display modes
ws.send('dmodejam');   // Clock mode
ws.send('dmodemp3');   // Audio mode
ws.send('dtesled');    // Test LED
```

#### Configuration Updates
```javascript
// Mosque info
ws.send('i{"nama": "Masjid Al-Ikhlas", "info1": "Jumat Berkah", "info2": "Sholat Berjamaah"}');

// Prayer settings
ws.send('s{"iqmhs": 12, "enable_subuh": 1, "koreksi_subuh": 2}');

// WiFi settings
ws.send('w{"wifissid": "MyWiFi", "wifipassword": "password123"}');

// Time settings
ws.send('t20231225');  // Set date (YYYYMMDD)
ws.send('j143000');    // Set time (HHMMSS)
```

### HTTP Endpoints

#### Configuration Data
```http
GET /xml        # Full configuration XML
GET /realxml    # Real-time data XML
```

#### XML Response Format
```xml
<t>
  <rNama>Masjid Al-Ikhlas</rNama>
  <rVolume>20</rVolume>
  <rKecerahan>150</rKecerahan>
  <rSubuh>Subuh 05:30</rSubuh>
  <rTemp>28.5</rTemp>
  <rHeap>35840</rHeap>
</t>
```

## 🏗️ Architecture

### System Components

```
┌─────────────────────────────────────────┐
│         JWS MUROTTAL V4.2              │
├─────────────────────────────────────────┤
│                                         │
│  ┌──────────┐  ┌──────────┐            │
│  │ WiFi AP  │  │ WiFi STA │            │
│  │  Mode    │  │   Mode   │            │
│  └────┬─────┘  └────┬─────┘            │
│       │             │                   │
│       └──────┬──────┘                   │
│              │                          │
│      ┌───────▼────────┐                │
│      │  DNS Server    │ (Captive)      │
│      │  Web Server    │ (Port 80)      │
│      │  WebSocket     │ (Port 81)      │
│      │  Message Queue │                │
│      │  Watchdog      │ (60s timeout)  │
│      └───────┬────────┘                │
│              │                          │
│  ┌───────────▼─────────────┐          │
│  │  Hardware Controllers    │          │
│  ├─────────────────────────┤          │
│  │ • RTC DS3231             │          │
│  │ • P10 LED Display        │          │
│  │ • DFPlayer MP3           │          │
│  │ • Buzzer                 │          │
│  └─────────────────────────┘          │
└─────────────────────────────────────────┘
```

### Code Structure
```
jws_v4/
├── jws_v42.ino         # Main sketch & setup/loop
├── WebPage_V4.h        # Modern web UI (HTML/CSS/JS)
├── WebServer_V4.h      # WiFi, WebSocket, message queue
├── FSConfig.h          # Configuration management
├── Display.h           # P10 LED control
├── DFPlayer.h          # MP3 player control
├── RTC.h               # Time management
└── JWS.h               # Prayer logic & display functions
```

## 🔍 Troubleshooting

### WiFi Issues
**Problem:** Cannot connect to WiFi
```
Solution:
1. Check SSID/password
2. Ensure 2.4GHz network (not 5GHz)
3. Check signal strength
4. Try manual restart
```

**Problem:** AP mode not working
```
Solution:
1. Check power supply (minimum 2A)
2. Verify antenna connection
3. Reset to factory settings
```

### Display Issues
**Problem:** LED display not working
```
Solution:
1. Check HJS589 connections
2. Verify power supply to LED panels
3. Check panel configuration (1 or 2 panels)
4. Test with LED test mode
```

**Problem:** Dimming not working
```
Solution:
1. Verify dim time settings
2. Check current RTC time
3. Ensure dim brightness > 15
4. Restart device
```

### Audio Issues
**Problem:** No sound from DFPlayer
```
Solution:
1. Check MicroSD card format (FAT32)
2. Verify audio files in correct folders
3. Check DFPlayer connections
4. Test volume level
```

### Memory Issues
**Problem:** Device restarts randomly
```
Solution:
1. Monitor Free Heap (>20KB normal)
2. Clear old configurations
3. Reduce WebSocket message frequency
4. Check for memory leaks
```

## 📊 Performance Metrics

| Metric | Value | Notes |
|--------|-------|-------|
| **Flash Usage** | ~800KB | Out of 1MB |
| **RAM Usage** | 25-35KB | Free heap |
| **Web Page Load** | <1s | Compressed |
| **WebSocket Latency** | <50ms | Local network |
| **RTC Accuracy** | ±2ppm | DS3231 spec |
| **Power Consumption** | 2-3W | Full brightness |

## 🔄 Changelog

### V4.2 (Current)
- ✅ **Automatic LED Dimming** with scheduling
- ✅ **Input Persistence** fixes for all settings
- ✅ **Production Code Cleanup** (removed debug prints)
- ✅ **Memory Monitoring** with real-time heap display
- ✅ **Enhanced WiFi System** (dual mode, auto-reconnect)

### V4.1
- ✅ Modern flat UI design
- ✅ Improved mobile responsiveness
- ✅ Better error handling
- ✅ WebSocket message queue
- ✅ Watchdog timer implementation

### V4.0
- ✅ Initial release with ESP8266
- ✅ Basic prayer time calculation
- ✅ Web interface for configuration
- ✅ DFPlayer audio integration
- ✅ P10 LED display support

## 🚀 Future Enhancements

### Planned Features
1. **MQTT Integration** - Remote control via MQTT broker
2. **SD Card Logging** - Log all events to SD card
3. **Multi-language Support** - ID/EN/AR interface
4. **Authentication System** - Login for web config
5. **Telegram Bot** - Control via Telegram
6. **Weather API Integration** - Display weather info
7. **Backup/Restore** - Configuration backup to cloud
8. **OTA Updates** - Over-the-air firmware updates

### Hardware Expansions
1. **Multiple Display Panels** (up to 4 panels)
2. **External Antenna** for better WiFi range
3. **Battery Backup** with UPS system
4. **Multiple Audio Zones** with amplifiers

## 🤝 Contributing

We welcome contributions! Please follow these steps:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Development Guidelines
- Follow Arduino coding standards
- Add comments for complex logic
- Test on actual hardware before submitting
- Update documentation for new features
- Maintain backward compatibility

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **PrayerTimes library** by Meeus/Jones/Conway
- **HJS589 library** for P10 LED control
- **ESP8266 community** for excellent documentation
- **IslamicFinder** for prayer calculation algorithms

## 📞 Support

### Serial Monitor
- **Baud Rate:** 115200
- **Debug Output:** Enabled for troubleshooting
- **Essential Logs:** WiFi status, memory usage

### Common Serial Messages
```
✓ Success indicators
✗ Error indicators
→ Process indicators
[WS] WebSocket events
[HTTP] HTTP requests
```

### Getting Help
1. Check [Issues](../../issues) for similar problems
2. Enable serial debug and share logs
3. Include hardware setup details
4. Specify firmware version and ESP8266 board

---

**Version:** 4.2  
**Last Updated:** December 2025  
**Platform:** ESP8266  
**Status:** Production Ready ✅

🕌 **JWS Murottal V4.2 - Smart Mosque Controller**  
*Built with ❤️ for the Muslim community*
