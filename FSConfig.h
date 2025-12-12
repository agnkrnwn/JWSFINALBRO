// PrayerTimes Variables
double times[7];  // 7 prayer times
int ihti = 2;

uint8_t tmpinfo;

String XML;


//----------------------------------------------------------------------
// CONSTANTS - Magic Numbers Replacement
#define WIFI_CONNECT_TIMEOUT_MS 10000
#define XML_UPDATE_INTERVAL_MS 1000
#define DISPLAY_REFRESH_RATE_MS 35
#define MAX_VOLUME 30
#define MIN_BRIGHTNESS 15
#define MAX_BRIGHTNESS 254
#define XML_BUFFER_SIZE 2048
#define JSON_CONFIG_SMALL 128
#define JSON_CONFIG_MEDIUM 512
#define JSON_CONFIG_LARGE 512

// Durasi waktu iqomah
struct ConfigJws {
   int iqmhs;
   int iqmhd;
   int iqmha;
   int iqmhm;
   int iqmhi;
   int durasiadzan;
   float latitude;
   float longitude;
   int zonawaktu;

   // Enable/Disable per waktu sholat (1 = enabled, 0 = disabled)
   uint8_t enable_tanbih;
   uint8_t enable_imsak;
   uint8_t enable_subuh;
   uint8_t enable_dzuhur;
   uint8_t enable_ashar;
   uint8_t enable_maghrib;
   uint8_t enable_isya;

   // Koreksi waktu per waktu sholat (dalam menit)
   int koreksi_tanbih;
   int koreksi_imsak;
   int koreksi_subuh;
   int koreksi_dzuhur;
   int koreksi_ashar;
   int koreksi_maghrib;
   int koreksi_isya;

   // Dimming settings
   int dim_start_hour;
   int dim_start_min;
   int dim_end_hour;
   int dim_end_min;
   int dim_brightness;
 };

struct ConfigInfo {
  char nama[64];
  char info1[512];
  char info2[512];
};

int iqmh;
int menitiqmh;
int detikiqmh = 60;

struct ConfigWifi {
  char wifissid[64];
  char wifipassword[64];
  char ssid[64];
  char password[64];
};

struct ConfigDisp {
  int kecerahan;
  int panel;
};

// Setting Panel
uint8_t intro1p;

struct ConfigDf {
  int volume;
};

String jsonjws;

const char *fileconfigdisp = "/configdisp.json";
ConfigDisp configdisp;

const char *fileconfigdf = "/configdf.json";
ConfigDf configdf;

const char *fileconfigjws = "/configjws.json";
ConfigJws configjws;

const char *fileconfiginfo = "/configinfo.json";
ConfigInfo configinfo;

const char *fileconfigwifi = "/configwifi.json";
ConfigWifi configwifi;



void LoadDataAwal() {


  if (configjws.iqmhs == 0) {
    configjws.iqmhs = 12;    
  }

  if (configjws.iqmhd == 0) {
    configjws.iqmhd = 8;    
  }

  if (configjws.iqmha == 0) {
    configjws.iqmha = 6;    
  }

  if (configjws.iqmhm == 0) {
    configjws.iqmhm = 5;    
  }

  if (configjws.iqmhi == 0) {
    configjws.iqmhi = 5;    
  }

  if (configjws.durasiadzan == 0) {
    configjws.durasiadzan = 4;
  }

  // Default enable semua waktu sholat (sudah di-handle di loadJwsConfig dengan default 1)
  // Tidak perlu set ulang di sini karena sudah di-load dari file atau default di loadJwsConfig

  // Default koreksi per waktu sudah di-handle di loadJwsConfig dengan default 1
  // Tidak perlu set ulang di sini

  if (configjws.latitude == 0) {
    configjws.latitude = -6.16;    
  }

  if (configjws.longitude == 0) {
    configjws.longitude = 106.61;    
  }

  if (configjws.zonawaktu == 0) {
    configjws.zonawaktu = 7;    
  }

  if (strlen(configinfo.nama) == 0) {
    strlcpy(configinfo.nama, "Nama Tempat", sizeof(configinfo.nama));
  }

  if (strlen(configinfo.info1) == 0) {
    strlcpy(configinfo.info1, "info 1", sizeof(configinfo.info1));
  }

  if (strlen(configinfo.info2) == 0) {
    strlcpy(configinfo.info2, "info 2", sizeof(configinfo.info2));
  }

  if (strlen(configwifi.wifissid) == 0) {
    strlcpy(configwifi.wifissid, "WiFi Kamu", sizeof(configwifi.wifissid));
  }

  if (strlen(configwifi.ssid) == 0) {
    strlcpy(configwifi.ssid, "JWS", sizeof(configwifi.ssid));
  }

  if (strlen(configwifi.password) == 0) {
    strlcpy(configwifi.password, "1234567890", sizeof(configwifi.password));
  }


  if (configdisp.kecerahan == 0) {
    configdisp.kecerahan = 100;    
  }

  if (configdisp.panel == 0) {
    configdisp.panel = 1;
  }

  if (configdf.volume == 0) {
    configdf.volume = 20;    
  }
  
}


void loadDispConfig(const char *fileconfigdisp, ConfigDisp &configdisp) {

  File configFileDisp = SPIFFS.open(fileconfigdisp, "r");

  if (!configFileDisp) {
    Serial.println("Gagal membuka fileconfigdisp untuk dibaca - menggunakan default");
    configdisp.kecerahan = 100;
    configdisp.panel = 1;
    return;
  }

  size_t size = configFileDisp.size();
  if (size == 0 || size > 512) {
    Serial.println("File configdisp tidak valid - menggunakan default");
    configFileDisp.close();
    configdisp.kecerahan = 100;
    configdisp.panel = 1;
    return;
  }
  
  std::unique_ptr<char[]> buf(new char[size + 1]);
  configFileDisp.readBytes(buf.get(), size);
  buf[size] = '\0';
  configFileDisp.close();

  // Optimasi: Config kecil hanya butuh 128 bytes
  DynamicJsonDocument doc(JSON_CONFIG_SMALL);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.print("Gagal parse fileconfigdisp: ");
    Serial.println(error.c_str());
    configdisp.kecerahan = 100;
    configdisp.panel = 1;
    return;
  }  
  
  configdisp.kecerahan = doc["kecerahan"] | 100;
  configdisp.panel = doc["panel"] | 1;
  
  // Validasi nilai
  if (configdisp.kecerahan < MIN_BRIGHTNESS) configdisp.kecerahan = MIN_BRIGHTNESS;
  if (configdisp.kecerahan > MAX_BRIGHTNESS) configdisp.kecerahan = MAX_BRIGHTNESS;
  if (configdisp.panel < 1 || configdisp.panel > 2) configdisp.panel = 1;

}



void handleSettingDispUpdate(String datadisp) {

  timer0_detachInterrupt();  
  
  // Optimasi: Config kecil hanya butuh 128 bytes
  DynamicJsonDocument doc(JSON_CONFIG_SMALL);
  DeserializationError error = deserializeJson(doc, datadisp);

  File configFileDisp = SPIFFS.open(fileconfigdisp, "w");
  
  if (!configFileDisp) {
    Serial.println("Gagal membuka Display configFile untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileDisp);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileDisp.close();
    Serial.println("Berhasil mengubah configFileDisp");


    loadDispConfig(fileconfigdisp, configdisp);
    
    Disp_init();

    Disp.setBrightness(configdisp.kecerahan);
    Disp.clear();
  
  }  

}


void loadDfConfig(const char *fileconfigdf, ConfigDf &configdf) {  

  File configFileDf = SPIFFS.open(fileconfigdf, "r");

  if (!configFileDf) {
    Serial.println("Gagal membuka fileconfigdf untuk dibaca - menggunakan default");
    configdf.volume = 20;
    return;
  }

  size_t size = configFileDf.size();
  if (size == 0 || size > 256) {
    Serial.println("File configdf tidak valid - menggunakan default");
    configFileDf.close();
    configdf.volume = 20;
    return;
  }
  
  std::unique_ptr<char[]> buf(new char[size + 1]);
  configFileDf.readBytes(buf.get(), size);
  buf[size] = '\0';
  configFileDf.close();

  // Optimasi: Config sangat kecil hanya butuh 128 bytes
  DynamicJsonDocument doc(JSON_CONFIG_SMALL);
  DeserializationError error = deserializeJson(doc, buf.get());  

  if (error) {
    Serial.print("Gagal parse fileconfigdf: ");
    Serial.println(error.c_str());
    configdf.volume = 20;
    return;
  }
  
  configdf.volume = doc["volume"] | 20;
  
  // Validasi nilai
  if (configdf.volume > MAX_VOLUME) configdf.volume = MAX_VOLUME;
  if (configdf.volume < 0) configdf.volume = 0;

}



void handleSettingDfUpdate(String datadf) {

  timer0_detachInterrupt();

  // Optimasi: Config kecil hanya butuh 128 bytes
  DynamicJsonDocument doc(JSON_CONFIG_SMALL);
  DeserializationError error = deserializeJson(doc, datadf);

  File configFileDf = SPIFFS.open(fileconfigdf, "w");
  
  if (!configFileDf) {
    Serial.println("Gagal membuka DFPlayer configFile untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileDf);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileDf.close();
    Serial.println("Berhasil mengubah configFileDf");


    loadDfConfig(fileconfigdf, configdf);

    timer0_attachInterrupt(refresh);
 
    mp3.setVolume(configdf.volume);
  
  }  

}



void loadInfoConfig(const char *fileconfiginfo, ConfigInfo &configinfo) {  

  File configFileInfo = SPIFFS.open(fileconfiginfo, "r");

  if (!configFileInfo) {
    Serial.println("Gagal membuka fileconfiginfo untuk dibaca - menggunakan default");
    strlcpy(configinfo.nama, "MASJID AL KAUTSAR", sizeof(configinfo.nama));
    strlcpy(configinfo.info1, "Ini adalah isi INFO 1", sizeof(configinfo.info1));
    strlcpy(configinfo.info2, "Ini adalah isi INFO 2", sizeof(configinfo.info2));
    return;
  }

  size_t size = configFileInfo.size();
  if (size == 0 || size > 2048) {
    Serial.println("File configinfo tidak valid - menggunakan default");
    configFileInfo.close();
    strlcpy(configinfo.nama, "MASJID AL KAUTSAR", sizeof(configinfo.nama));
    strlcpy(configinfo.info1, "Ini adalah isi INFO 1", sizeof(configinfo.info1));
    strlcpy(configinfo.info2, "Ini adalah isi INFO 2", sizeof(configinfo.info2));
    return;
  }
  
  std::unique_ptr<char[]> buf(new char[size + 1]);
  configFileInfo.readBytes(buf.get(), size);
  buf[size] = '\0';
  configFileInfo.close();

  // Optimasi: Config medium butuh 512 bytes
  DynamicJsonDocument doc(JSON_CONFIG_MEDIUM);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.print("Gagal parse fileconfiginfo: ");
    Serial.println(error.c_str());
    strlcpy(configinfo.nama, "MASJID AL KAUTSAR", sizeof(configinfo.nama));
    strlcpy(configinfo.info1, "Ini adalah isi INFO 1", sizeof(configinfo.info1));
    strlcpy(configinfo.info2, "Ini adalah isi INFO 2", sizeof(configinfo.info2));
    return;
  }  
  
  strlcpy(configinfo.nama, doc["nama"] | "MASJID AL KAUTSAR", sizeof(configinfo.nama));
  strlcpy(configinfo.info1, doc["info1"] | "Ini adalah isi INFO 1", sizeof(configinfo.info1));
  strlcpy(configinfo.info2, doc["info2"] | "Ini adalah isi INFO 2", sizeof(configinfo.info2));

}



void handleSettingInfoUpdate(String datainfo) {

  timer0_detachInterrupt();

  // Optimasi: Config medium butuh 512 bytes
  DynamicJsonDocument doc(JSON_CONFIG_MEDIUM);
  DeserializationError error = deserializeJson(doc, datainfo);

  File configFileInfo = SPIFFS.open(fileconfiginfo, "w");
  
  if (!configFileInfo) {
    Serial.println("Gagal membuka configFileInfo untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileInfo);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileInfo.close();
    Serial.println("Berhasil mengubah configFileInfo");


    loadInfoConfig(fileconfiginfo, configinfo);

    timer0_attachInterrupt(refresh);
  
  }  

}



void loadJwsConfig(const char *fileconfigjws, ConfigJws &configjws) {  

  File configFileJws = SPIFFS.open(fileconfigjws, "r");

  if (!configFileJws) {
    Serial.println("Gagal membuka fileconfigjws untuk dibaca - menggunakan default");
    // Default values akan di-set di LoadDataAwal()
    return;
  }

  size_t size = configFileJws.size();
  if (size == 0 || size > 1024) {
    Serial.println("File configjws tidak valid - menggunakan default");
    configFileJws.close();
    return;
  }
  
  std::unique_ptr<char[]> buf(new char[size + 1]);
  configFileJws.readBytes(buf.get(), size);
  buf[size] = '\0';
  configFileJws.close();

  // Optimasi: Config besar butuh 1024 bytes
  DynamicJsonDocument doc(JSON_CONFIG_LARGE);
  DeserializationError error = deserializeJson(doc, buf.get());  

  if (error) {
    Serial.print("Gagal parse fileconfigjws: ");
    Serial.println(error.c_str());
    return;
  }
  
  configjws.iqmhs = doc["iqmhs"] | 12;
  configjws.iqmhd = doc["iqmhd"] | 8;
  configjws.iqmha = doc["iqmha"] | 6;
  configjws.iqmhm = doc["iqmhm"] | 5;
  configjws.iqmhi = doc["iqmhi"] | 5;
  configjws.durasiadzan = doc["durasiadzan"] | 4;
  configjws.latitude = doc["latitude"] | -6.16;
  configjws.longitude = doc["longitude"] | 106.61;
  configjws.zonawaktu = doc["zonawaktu"] | 7;

  // Load enable/disable per waktu (default 1 = enabled)
  configjws.enable_tanbih = doc["enable_tanbih"] | 1;
  configjws.enable_imsak = doc["enable_imsak"] | 1;
  configjws.enable_subuh = doc["enable_subuh"] | 1;
  configjws.enable_dzuhur = doc["enable_dzuhur"] | 1;
  configjws.enable_ashar = doc["enable_ashar"] | 1;
  configjws.enable_maghrib = doc["enable_maghrib"] | 1;
  configjws.enable_isya = doc["enable_isya"] | 1;

  // Load koreksi per waktu (default 1 menit)
  int defaultKoreksi = 1;
  configjws.koreksi_tanbih = doc["koreksi_tanbih"] | defaultKoreksi;
  configjws.koreksi_imsak = doc["koreksi_imsak"] | defaultKoreksi;
  configjws.koreksi_subuh = doc["koreksi_subuh"] | defaultKoreksi;
  configjws.koreksi_dzuhur = doc["koreksi_dzuhur"] | defaultKoreksi;
  configjws.koreksi_ashar = doc["koreksi_ashar"] | defaultKoreksi;
  configjws.koreksi_maghrib = doc["koreksi_maghrib"] | defaultKoreksi;
  configjws.koreksi_isya = doc["koreksi_isya"] | defaultKoreksi;

  // Load dimming settings (default 22:00-02:00, brightness 15)
  configjws.dim_start_hour = doc["dim_start_hour"] | 22;
  configjws.dim_start_min = doc["dim_start_min"] | 0;
  configjws.dim_end_hour = doc["dim_end_hour"] | 2;
  configjws.dim_end_min = doc["dim_end_min"] | 0;
  configjws.dim_brightness = doc["dim_brightness"] | 70;

}



void handleSettingJwsUpdate(String datajws) {

   timer0_detachInterrupt();

   // Optimasi: Config besar butuh 1024 bytes
   DynamicJsonDocument doc(JSON_CONFIG_LARGE);
   DeserializationError error = deserializeJson(doc, datajws);

   if (error) {
     Serial.print(F("deserializeJson() gagal: "));
     Serial.println(error.c_str());
     timer0_attachInterrupt(refresh);
     return;
   }

   File configFileJws = SPIFFS.open(fileconfigjws, "w");

   if (!configFileJws) {
     Serial.println("Gagal membuka Info configFileJws untuk ditulis");
     timer0_attachInterrupt(refresh);
     return;
   }

   serializeJson(doc, configFileJws);
   configFileJws.close();

   Serial.println("Berhasil mengubah configFileJws");

   // Verifikasi file tersimpan
   File checkFile = SPIFFS.open(fileconfigjws, "r");
   if (checkFile) {
     size_t size = checkFile.size();
     checkFile.close();
     Serial.printf("File configjws.json size: %d bytes\n", size);
   } else {
     Serial.println("Gagal verifikasi file configjws.json");
   }

   loadJwsConfig(fileconfigjws, configjws);

   timer0_attachInterrupt(refresh);

 }



void loadWifiConfig(const char *fileconfigwifi, ConfigWifi &configwifi) {  

  File configFileWifi = SPIFFS.open(fileconfigwifi, "r");

  if (!configFileWifi) {
    Serial.println("Gagal membuka fileconfigwifi untuk dibaca - menggunakan default");
    strlcpy(configwifi.wifissid, "WiFi Kamu", sizeof(configwifi.wifissid));
    strlcpy(configwifi.wifipassword, "", sizeof(configwifi.wifipassword));
    strlcpy(configwifi.ssid, "JWS", sizeof(configwifi.ssid));
    strlcpy(configwifi.password, "1234567890", sizeof(configwifi.password));
    return;
  }

  size_t size = configFileWifi.size();
  if (size == 0 || size > 1024) {
    Serial.println("File configwifi tidak valid - menggunakan default");
    configFileWifi.close();
    strlcpy(configwifi.wifissid, "WiFi Kamu", sizeof(configwifi.wifissid));
    strlcpy(configwifi.wifipassword, "", sizeof(configwifi.wifipassword));
    strlcpy(configwifi.ssid, "JWS", sizeof(configwifi.ssid));
    strlcpy(configwifi.password, "1234567890", sizeof(configwifi.password));
    return;
  }
  
  std::unique_ptr<char[]> buf(new char[size + 1]);
  configFileWifi.readBytes(buf.get(), size);
  buf[size] = '\0';
  configFileWifi.close();

  // Optimasi: Config besar butuh 1024 bytes
  DynamicJsonDocument doc(JSON_CONFIG_LARGE);
  DeserializationError error = deserializeJson(doc, buf.get());  

  if (error) {
    Serial.print("Gagal parse fileconfigwifi: ");
    Serial.println(error.c_str());
    strlcpy(configwifi.wifissid, "WiFi Kamu", sizeof(configwifi.wifissid));
    strlcpy(configwifi.wifipassword, "", sizeof(configwifi.wifipassword));
    strlcpy(configwifi.ssid, "JWS", sizeof(configwifi.ssid));
    strlcpy(configwifi.password, "1234567890", sizeof(configwifi.password));
    return;
  }
  
  strlcpy(configwifi.wifissid, doc["wifissid"] | "WiFi Kamu", sizeof(configwifi.wifissid));
  strlcpy(configwifi.wifipassword, doc["wifipassword"] | "", sizeof(configwifi.wifipassword));
  strlcpy(configwifi.ssid, doc["ssid"] | "JWS", sizeof(configwifi.ssid));
  strlcpy(configwifi.password, doc["password"] | "1234567890", sizeof(configwifi.password));

  // Sanity check for corruption
  bool corrupted = false;
  size_t len = strlen(configwifi.ssid);
  if (len == 0 || len > 32) corrupted = true;
  else {
    for (size_t i = 0; i < len; i++) {
      if (!isprint(configwifi.ssid[i])) {
        corrupted = true;
        break;
      }
    }
  }

  if (corrupted) {
    Serial.println("SSID corrupted or invalid! Resetting to default.");
    strlcpy(configwifi.ssid, "WiFi Kamu", sizeof(configwifi.ssid));
    strlcpy(configwifi.password, "12345678", sizeof(configwifi.password));
  }

  Serial.println("Loaded WiFi Config:");
  Serial.print("WiFi SSID: "); Serial.println(configwifi.wifissid);
  Serial.print("WiFi Pass: "); Serial.println(configwifi.wifipassword);
  Serial.print("AP SSID: "); Serial.println(configwifi.ssid);
  Serial.print("AP Pass: "); Serial.println(configwifi.password);

  configFileWifi.close();

}



void handleSettingWifiUpdate(String datawifi) {

  timer0_detachInterrupt();

  // Optimasi: Config besar butuh 1024 bytes
  DynamicJsonDocument doc(JSON_CONFIG_LARGE);
  DeserializationError error = deserializeJson(doc, datawifi);

  File configFileWifi = SPIFFS.open(fileconfigwifi, "w");
  
  if (!configFileWifi) {
    Serial.println("Gagal membuka Info configFileWifi untuk ditulis");
    return;
  }
  
  serializeJson(doc, configFileWifi);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileWifi.close();
    Serial.println("Berhasil mengubah configFileWifi");

    loadWifiConfig(fileconfigwifi, configwifi);

    timer0_attachInterrupt(refresh);    
  
  }

}


void JadwalSholat() {

  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting

    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi

    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night

    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  
  */

  RtcDateTime now = Rtc.GetDateTime();
  
  int tahun = now.Year();
  int bulan = now.Month();
  int tanggal = now.Day();
  
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(tahun, bulan, tanggal, configjws.latitude, configjws.longitude, configjws.zonawaktu, times);

}


//----------------------------------------------------------------------
// XML UNTUK JEMBATAN DATA MESIN DENGAN WEB

void realXML(){

  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  
  char buffer[64];
  
  // Optimasi: Clear dan reserve memory
  XML = "";
  XML.reserve(XML_BUFFER_SIZE);

  XML = "<?xml version='1.0'?><t>";
  
  // Year
  snprintf(buffer, sizeof(buffer), "<rYear>%d</rYear>", now.Year());
  XML += buffer;
  
  // Month
  snprintf(buffer, sizeof(buffer), "<rMonth>%d</rMonth>", now.Month());
  XML += buffer;
  
  // Day
  snprintf(buffer, sizeof(buffer), "<rDay>%d</rDay>", now.Day());
  XML += buffer;
  
  // Hour (dengan leading zero)
  snprintf(buffer, sizeof(buffer), "<rHour>%02d</rHour>", now.Hour());
  XML += buffer;
  
  // Minute (dengan leading zero)
  snprintf(buffer, sizeof(buffer), "<rMinute>%02d</rMinute>", now.Minute());
  XML += buffer;
  
  // Second (dengan leading zero)
  snprintf(buffer, sizeof(buffer), "<rSecond>%02d</rSecond>", now.Second());
  XML += buffer;
  
  // Temperature
  snprintf(buffer, sizeof(buffer), "<rTemp>%.1f</rTemp>", temp.AsFloatDegC() - 5.0);
  XML += buffer;
  
  // Volume
  snprintf(buffer, sizeof(buffer), "<rVolume>%d</rVolume>", configdf.volume);
  XML += buffer;
  
  // Brightness
  snprintf(buffer, sizeof(buffer), "<rKecerahan>%d</rKecerahan>", configdisp.kecerahan);
  XML += buffer;
  
  // Free Heap (untuk monitoring memory)
  snprintf(buffer, sizeof(buffer), "<rHeap>%d</rHeap>", ESP.getFreeHeap());
  XML += buffer;
  
  XML += "</t>"; 
}

void buildXML(){

  JadwalSholat();

  static uint8_t i;
  int hours, minutes;
  char jtanbih[14];
  char jsubuh[14];
  char jdzuhur[14];
  char jashar[14];
  char jmaghrib[14];
  char jisya[14];

  // Tanbih dengan koreksi per waktu
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configjws.koreksi_tanbih;
  if (minutes < 11) {
    minutes = 60 - minutes;
    hours --;
  } else {
    minutes = minutes - 10;
  }
  snprintf(jtanbih, sizeof(jtanbih), "Tanbih %02d:%02d", hours, minutes);
  
  // Subuh dengan koreksi per waktu
  get_float_time_parts(times[0], hours, minutes);  
  minutes = minutes + configjws.koreksi_subuh;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }  
  snprintf(jsubuh, sizeof(jsubuh), "Subuh %02d:%02d", hours, minutes);
  
  // Dzuhur dengan koreksi per waktu
  get_float_time_parts(times[2], hours, minutes);  
  minutes = minutes + configjws.koreksi_dzuhur;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }  
  snprintf(jdzuhur, sizeof(jdzuhur), "Dzuhur %02d:%02d", hours, minutes);

  // Ashar dengan koreksi per waktu
  get_float_time_parts(times[3], hours, minutes);  
  minutes = minutes + configjws.koreksi_ashar;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }  
  snprintf(jashar, sizeof(jashar), "Ashar %02d:%02d", hours, minutes);

  // Maghrib dengan koreksi per waktu
  get_float_time_parts(times[5], hours, minutes);  
  minutes = minutes + configjws.koreksi_maghrib;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }  
  snprintf(jmaghrib, sizeof(jmaghrib), "Maghrib %02d:%02d", hours, minutes);

  // Isya dengan koreksi per waktu
  get_float_time_parts(times[6], hours, minutes);  
  minutes = minutes + configjws.koreksi_isya;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }  
  snprintf(jisya, sizeof(jisya), "Isya %02d:%02d", hours, minutes);

  // Optimasi: Clear dan reserve memory
  XML = "";
  XML.reserve(XML_BUFFER_SIZE);
  
  char buffer[128];
  
  XML = "<?xml version='1.0'?><t>";
  
  // WiFi Config
  snprintf(buffer, sizeof(buffer), "<rWifissid>%s</rWifissid>", configwifi.wifissid);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rWifipassword>%s</rWifipassword>", configwifi.wifipassword);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rSsid>%s</rSsid>", configwifi.ssid);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rPassword>%s</rPassword>", configwifi.password);
  XML += buffer;
  
  // JWS Config
  snprintf(buffer, sizeof(buffer), "<rIqmhs>%d</rIqmhs>", configjws.iqmhs);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rIqmhd>%d</rIqmhd>", configjws.iqmhd);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rIqmha>%d</rIqmha>", configjws.iqmha);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rIqmhm>%d</rIqmhm>", configjws.iqmhm);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rIqmhi>%d</rIqmhi>", configjws.iqmhi);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDurasiadzan>%d</rDurasiadzan>", configjws.durasiadzan);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rLatitude>%.6f</rLatitude>", configjws.latitude);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rLongitude>%.6f</rLongitude>", configjws.longitude);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rZonawaktu>%d</rZonawaktu>", configjws.zonawaktu);
  XML += buffer;
  
  // Info Config
  snprintf(buffer, sizeof(buffer), "<rNama>%s</rNama>", configinfo.nama);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rInfo1>%s</rInfo1>", configinfo.info1);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rInfo2>%s</rInfo2>", configinfo.info2);
  XML += buffer;

  // Jadwal Sholat
  snprintf(buffer, sizeof(buffer), "<rTanbih>%s</rTanbih>", jtanbih);
  XML += buffer;
  
  // Imsak (hitung terpisah)
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configjws.koreksi_imsak;
  if (minutes < 11) {
    minutes = 60 - minutes;
    hours --;
  } else {
    minutes = minutes - 10;
  }
  char jimsak[14];
  snprintf(jimsak, sizeof(jimsak), "Imsak %02d:%02d", hours, minutes);
  snprintf(buffer, sizeof(buffer), "<rImsak>%s</rImsak>", jimsak);
  XML += buffer;
  
  snprintf(buffer, sizeof(buffer), "<rSubuh>%s</rSubuh>", jsubuh);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDzuhur>%s</rDzuhur>", jdzuhur);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rAshar>%s</rAshar>", jashar);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rMaghrib>%s</rMaghrib>", jmaghrib);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rIsya>%s</rIsya>", jisya);
  XML += buffer;
  
  // Enable/Disable per waktu
  snprintf(buffer, sizeof(buffer), "<rEnable_tanbih>%d</rEnable_tanbih>", configjws.enable_tanbih);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_imsak>%d</rEnable_imsak>", configjws.enable_imsak);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_subuh>%d</rEnable_subuh>", configjws.enable_subuh);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_dzuhur>%d</rEnable_dzuhur>", configjws.enable_dzuhur);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_ashar>%d</rEnable_ashar>", configjws.enable_ashar);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_maghrib>%d</rEnable_maghrib>", configjws.enable_maghrib);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rEnable_isya>%d</rEnable_isya>", configjws.enable_isya);
  XML += buffer;

  // Koreksi per waktu
  snprintf(buffer, sizeof(buffer), "<rKoreksi_tanbih>%d</rKoreksi_tanbih>", configjws.koreksi_tanbih);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_imsak>%d</rKoreksi_imsak>", configjws.koreksi_imsak);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_subuh>%d</rKoreksi_subuh>", configjws.koreksi_subuh);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_dzuhur>%d</rKoreksi_dzuhur>", configjws.koreksi_dzuhur);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_ashar>%d</rKoreksi_ashar>", configjws.koreksi_ashar);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_maghrib>%d</rKoreksi_maghrib>", configjws.koreksi_maghrib);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rKoreksi_isya>%d</rKoreksi_isya>", configjws.koreksi_isya);
  XML += buffer;

  // Dimming settings
  snprintf(buffer, sizeof(buffer), "<rDimStartHour>%d</rDimStartHour>", configjws.dim_start_hour);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDimStartMin>%d</rDimStartMin>", configjws.dim_start_min);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDimEndHour>%d</rDimEndHour>", configjws.dim_end_hour);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDimEndMin>%d</rDimEndMin>", configjws.dim_end_min);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rDim_brightness>%d</rDim_brightness>", configjws.dim_brightness);
  XML += buffer;
  snprintf(buffer, sizeof(buffer), "<rPanel>%d</rPanel>", configdisp.panel);
  XML += buffer;
  
  XML += "</t>"; 
}
