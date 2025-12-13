# Audio Generator for JWS Mosque Controller

Tool untuk generate file audio Quran dari berbagai qori untuk digunakan di JWS (Jadwal Waktu Sholat) Mosque Controller.

## Fitur

- ✅ Pilih hingga 12 qori dari database lengkap
- ✅ Preview audio qori sebelum download
- ✅ Generate link download otomatis untuk 114 surah
- ✅ Export HTML template untuk web UI
- ✅ Export JSON untuk script download Python
- ✅ Download otomatis dengan Python script

## Struktur File Output

```
quran/
├── 01/           # Audio adzan (manual)
├── 02/           # Qori 1 - 001.mp3 sampai 114.mp3
├── 03/           # Qori 2
├── ...
├── 13/           # Qori 12
└── 14/           # Audio doa (manual)
```

## Cara Penggunaan

### 1. Setup
- Pastikan file `datas/audio.json` ada di folder yang sama
- Buka `audio_generator_v2.html` di browser modern

### 2. Pilih Qori
- Scroll daftar qori yang tersedia
- Klik icon play untuk preview audio (surah Al-Fatihah)
- Centang checkbox qori yang diinginkan (maksimal 12)
- Jika sudah 12, checkbox lainnya akan disabled otomatis

### 3. Generate Files
- Klik tombol "Generate Files"
- Link download akan muncul (bisa di-toggle show/hide)
- HTML template akan di-generate untuk playlist select
- JSON data akan di-generate untuk Python download

### 4. Download Files
- Klik "Download HTML" untuk template playlist
- Klik "Download JSON" untuk data download
- Jalankan Python script: `python download_audio.py`

### 5. Update Web UI
- Buka file `WebPage_V4.h` di Arduino IDE
- Cari bagian playlist select sekitar line 436
- Replace kode HTML lama dengan yang di-generate
- Compile dan upload ke ESP8266

### 6. Copy ke SD Card
- Copy folder `quran/` ke root SD card DFPlayer
- Masukkan SD card ke modul DFPlayer
- Restart ESP8266
- Enjoy audio baru di controller!

## File yang Dibutuhkan

- `audio_generator_v2.html` - Interface web untuk generate
- `download_audio.py` - Script Python untuk download
- `datas/audio.json` - Database qori dari Quranicaudio

## Dependencies Python

```bash
pip install requests
```

## Preview Audio

Setiap qori memiliki icon play di sebelah nama. Klik untuk mendengarkan preview surah 1 (Al-Fatihah) dari qori tersebut.

## Troubleshooting

### Audio tidak bisa diputar
- Pastikan koneksi internet stabil
- Coba browser lain (Chrome/Firefox)

### Download gagal
- Cek koneksi internet
- Jalankan ulang script Python
- Script akan skip file yang sudah ada

### SD Card tidak terdeteksi
- Format SD card ke FAT32
- Pastikan struktur folder benar

## Lisensi

Untuk penggunaan pribadi di JWS Mosque Controller.

## Kontak

Dibuat untuk komunitas JWS Indonesia.