const char webpage[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>JWS Murottal V4</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Arial, sans-serif;
            background: #1a1a1a;
            color: #e0e0e0;
            line-height: 1.6;
            min-height: 100vh;
        }
        
        /* ===== MOBILE FIRST ===== */
        
        .header {
            background: #252525;
            padding: 20px;
            border-bottom: 1px solid #333;
            position: sticky;
            top: 0;
            z-index: 100;
        }
        
        .header h1 {
            font-size: 1.4rem;
            color: #4CAF50;
            margin-bottom: 4px;
            font-weight: 700;
        }
        
        .header p {
            color: #999;
            font-size: 0.8rem;
        }
        
        .status-bar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-top: 12px;
            padding-top: 12px;
            border-top: 1px solid #333;
        }
        
        .status-indicator {
            display: flex;
            align-items: center;
            gap: 6px;
            font-size: 0.8rem;
        }
        
        .status-dot {
            width: 6px;
            height: 6px;
            border-radius: 50%;
            background: #e74c3c;
        }
        
        .status-dot.online {
            background: #4CAF50;
        }
        
        /* Container */
        .container {
            padding: 0;
            max-width: 100%;
        }
        
        /* ===== STATS SECTION ===== */
        .stats {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            gap: 8px;
            padding: 16px;
            background: #222;
        }
        
        .stat {
            background: #2a2a2a;
            padding: 12px;
            border-radius: 6px;
            text-align: center;
            border-left: 3px solid #4CAF50;
        }
        
        .stat-value {
            font-size: 1rem;
            font-weight: 700;
            color: #4CAF50;
            font-family: monospace;
            word-break: break-all;
        }
        
        .stat-label {
            color: #888;
            font-size: 0.7rem;
            text-transform: uppercase;
            margin-top: 6px;
        }
        
        /* ===== SECTIONS ===== */
        .section {
            padding: 16px;
            margin: 8px 0;
            background: #252525;
            border-top: 3px solid #4CAF50;
        }
        
        .section-title {
            font-size: 1rem;
            color: #4CAF50;
            margin-bottom: 16px;
            font-weight: 700;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        
        /* ===== FORM ELEMENTS ===== */
        .form-group {
            margin-bottom: 12px;
        }
        
        label {
            display: block;
            color: #999;
            font-size: 0.75rem;
            margin-bottom: 4px;
            text-transform: uppercase;
            font-weight: 700;
            letter-spacing: 0.5px;
        }
        
        input, select, textarea {
            width: 100%;
            padding: 10px;
            background: #1a1a1a;
            border: 1px solid #444;
            color: #e0e0e0;
            font-size: 0.9rem;
            border-radius: 4px;
            font-family: inherit;
        }
        
        input::placeholder, textarea::placeholder {
            color: #666;
        }
        
        input:focus, select:focus, textarea:focus {
            outline: none;
            border-color: #4CAF50;
            background: #2a2a2a;
        }
        
        /* ===== BUTTONS ===== */
        .btn {
            padding: 10px 16px;
            border: none;
            cursor: pointer;
            font-size: 0.8rem;
            font-weight: 700;
            border-radius: 4px;
            transition: all 0.2s;
            text-transform: uppercase;
            letter-spacing: 0.5px;
            width: 100%;
            margin-bottom: 8px;
        }
        
        .btn-primary {
            background: #4CAF50;
            color: #fff;
        }
        
        .btn-primary:active {
            background: #45a049;
        }
        
        .btn-secondary {
            background: #2196F3;
            color: #fff;
        }
        
        .btn-secondary:active {
            background: #1976d2;
        }
        
        .btn-danger {
            background: #e74c3c;
            color: #fff;
        }
        
        .btn-danger:active {
            background: #c0392b;
        }
        
        .btn-warning {
            background: #f39c12;
            color: #fff;
        }
        
        .btn-warning:active {
            background: #d68910;
        }
        
        /* ===== MEDIA CONTROLS ===== */
        .media-controls {
            display: flex;
            justify-content: center;
            gap: 8px;
            padding: 16px 0;
            flex-wrap: wrap;
        }
        
        .media-btn {
            width: 48px;
            height: 48px;
            border: none;
            background: #2a2a2a;
            color: #4CAF50;
            font-size: 1.2rem;
            cursor: pointer;
            border-radius: 4px;
            border: 1px solid #444;
            transition: all 0.2s;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        
        .media-btn:active {
            background: #4CAF50;
            color: #fff;
        }
        
        .media-btn.main {
            width: 56px;
            height: 56px;
            font-size: 1.5rem;
            background: #4CAF50;
            color: #fff;
            border: none;
        }
        
        .media-btn.main:active {
            background: #45a049;
        }
        
        /* ===== TABLE ===== */
        table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 12px;
        }
        
        th {
            background: #2a2a2a;
            padding: 10px;
            text-align: left;
            font-size: 0.75rem;
            font-weight: 700;
            color: #999;
            text-transform: uppercase;
            border-bottom: 1px solid #444;
        }
        
        td {
            padding: 10px;
            border-bottom: 1px solid #333;
            font-size: 0.9rem;
        }
        
        .time-badge {
            background: #4CAF50;
            color: #fff;
            padding: 4px 10px;
            border-radius: 3px;
            font-family: monospace;
            font-weight: 700;
            display: inline-block;
            font-size: 0.85rem;
        }
        
        /* ===== GRID ===== */
        .grid-2 {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 12px;
        }
        
        .grid-3 {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 12px;
        }
        
        /* ===== DIVIDER ===== */
        .divider {
            height: 1px;
            background: #333;
            margin: 16px 0;
        }
        
        /* ===== INFO BOX ===== */
        .info-box {
            background: rgba(76, 175, 80, 0.1);
            border-left: 3px solid #4CAF50;
            padding: 12px;
            border-radius: 4px;
            margin-top: 12px;
            font-size: 0.8rem;
            color: #aaa;
            line-height: 1.5;
        }
        
        .info-box strong {
            color: #4CAF50;
        }
        
        /* ===== TOAST ===== */
        #toast {
            position: fixed;
            bottom: -60px;
            left: 16px;
            right: 16px;
            background: #4CAF50;
            color: #fff;
            padding: 12px 16px;
            border-radius: 4px;
            font-weight: 700;
            transition: bottom 0.3s ease;
            z-index: 1000;
            font-size: 0.85rem;
        }
        
        #toast.show {
            bottom: 16px;
        }
        
        /* ===== SPACING ===== */
        .spacer {
            height: 16px;
        }
        
        /* ===== TABLET & DESKTOP ===== */
        @media (min-width: 768px) {
            .header {
                padding: 24px 32px;
            }
            
            .stats {
                grid-template-columns: repeat(3, 1fr);
                gap: 16px;
                padding: 24px 32px;
            }
            
            .section {
                padding: 24px 32px;
                margin: 12px 32px;
                border-radius: 8px;
            }
            
            .btn {
                width: auto;
                margin-bottom: 0;
                margin-right: 8px;
            }
            
            .grid-2 {
                grid-template-columns: 1fr 1fr;
                gap: 20px;
            }
            
            .grid-3 {
                gap: 20px;
            }
        }
        
        @media (min-width: 1024px) {
            .container {
                max-width: 1000px;
                margin: 0 auto;
            }
        }
    </style>
</head>
<body onload="init()">
    
    <div class="container">
        
        <!-- Header -->
        <div class="header">
            <h1>🕌 JWS Murottal</h1>
            <p>Smart Mosque Controller V4.0</p>
            <div class="status-bar">
                <div class="status-indicator">
                    <span class="status-dot" id="status-dot"></span>
                    <span id="status-text">Offline</span>
                </div>
            </div>
        </div>
        
        <!-- Stats -->
        <div class="stats">
            <div class="stat">
                <div class="stat-value" id="clock">00:00:00</div>
                <div class="stat-label">Waktu</div>
            </div>
            <div class="stat">
                <div class="stat-value" id="date">--:--</div>
                <div class="stat-label">Tanggal</div>
            </div>
            <div class="stat">
                <div class="stat-value"><span id="temp">--</span>°</div>
                <div class="stat-label">Suhu</div>
            </div>
        </div>
        
        <!-- Audio Player -->
        <div class="section" id="player">
            <div class="section-title">🎵 Audio</div>
            
            <div class="form-group">
                <label>Volume</label>
                <input type="number" min="0" max="30" value="15" id="volume">
            </div>
            
            <button class="btn btn-primary" onclick="sendVolume()">Set Volume</button>
            
            <div class="form-group" style="margin-top: 16px;">
                <label>Playlist</label>
                <select id="playlist">
                    <option value="p1">Al Quran - All</option>
                    <option value="p2">Saad Alghamdi</option>
                    <option value="p3">Juz Amma - Saad</option>
                    <option value="p4">Mishary Rasyid</option>
                    <option value="p5">Juz Amma - Mishary</option>
                    <option value="p6">As Sudais</option>
                    <option value="p7">Juz Amma - Sudais</option>
                    <option value="p8">Al Budair</option>
                    <option value="p9">Juz Amma - Budair</option>
                    <option value="pl1">Al Muaiqly</option>
                    <option value="pl2">Juz Amma - Muaiqly</option>
                    <option value="pl3">Al Hudhaifi</option>
                    <option value="pl4">Juz Amma - Hudhaifi</option>
                    <option value="pl5">Lain-lain</option>
                </select>
            </div>
            
            <button class="btn btn-secondary" onclick="sendAudioSettings()">Apply Playlist</button>
            
            <div class="form-group" style="margin-top: 16px;">
                <label>Equalizer</label>
                <select id="equalizer">
                    <option value="e1">Normal</option>
                    <option value="e2">Pop</option>
                    <option value="e3">Rock</option>
                    <option value="e4">Jazz</option>
                    <option value="e5">Classic</option>
                    <option value="e6">Bass</option>
                </select>
            </div>
            
            <button class="btn btn-secondary" onclick="sendAudioSettings()">Apply EQ</button>
            
            <div class="media-controls">
                <button class="media-btn" onclick="sendPrev()">⏮</button>
                <button class="media-btn" onclick="sendStop()">⏹</button>
                <button class="media-btn main" onclick="sendPlay()">▶</button>
                <button class="media-btn" onclick="sendPause()">⏸</button>
                <button class="media-btn" onclick="sendNext()">⏭</button>
            </div>
            
            <button class="btn btn-secondary" onclick="sendRandom()">🔀 Random</button>
        </div>
        
        <!-- Display -->
        <div class="section" id="display">
            <div class="section-title">🖥️ Display</div>

            <div class="form-group">
                <label>Brightness (15-254)</label>
                <input type="number" min="15" max="254" value="100" id="kecerahan">
            </div>

            <div class="form-group">
                <label>Panel</label>
                <select id="panel">
                    <option value="1">1 Panel</option>
                    <option value="2">2 Panel</option>
                </select>
            </div>

            <div class="form-group">
                <label>Dim Start Time</label>
                <input type="time" id="dim_start_time" value="22:00">
            </div>

            <div class="form-group">
                <label>Dim End Time</label>
                <input type="time" id="dim_end_time" value="02:00">
            </div>

            <div class="form-group">
                <label>Dim Brightness (15-254)</label>
                <input type="number" min="15" max="254" id="dim_brightness" value="70">
            </div>

            <button class="btn btn-primary" onclick="setJws()">Save Dim Settings</button>

            <div class="grid-2">
                <button class="btn btn-warning" onclick="sendModeJam()">Mode Jam</button>
                <button class="btn btn-secondary" onclick="sendModeMP3()">Mode Audio</button>
            </div>

            <div class="grid-2">
                <button class="btn btn-warning" onclick="sendTesLED()">Test LED</button>
                <button class="btn btn-primary" onclick="sendKecerahan()">Apply Brightness</button>
            </div>
        </div>
        
        <!-- Masjid Info -->
        <div class="section" id="masjid">
            <div class="section-title">🕌 Info Masjid</div>
            
            <div class="form-group">
                <label>Nama Masjid</label>
                <input type="text" id="nama" placeholder="Masukkan nama masjid">
            </div>
            
            <div class="form-group">
                <label>Running Text 1</label>
                <textarea id="info1" rows="2"></textarea>
            </div>
            
            <div class="form-group">
                <label>Running Text 2</label>
                <textarea id="info2" rows="2"></textarea>
            </div>
            
            <button class="btn btn-primary" onclick="sendNama()">Simpan</button>
        </div>
        
        <!-- Jadwal Sholat -->
        <div class="section" id="jadwal">
            <div class="section-title">🕋 Jadwal Sholat</div>
            
            <table>
                <thead>
                    <tr>
                        <th>Sholat</th>
                        <th style="text-align: right;">Jam</th>
                        <th style="text-align: center;">Enable</th>
                        <th style="text-align: center;">Koreksi</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>Tanbih</td>
                        <td style="text-align: right;"><span id="jtanbih" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_tanbih" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_tanbih" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Imsak</td>
                        <td style="text-align: right;"><span id="jimsak" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_imsak" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_imsak" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Subuh</td>
                        <td style="text-align: right;"><span id="jsubuh" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_subuh" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_subuh" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Dzuhur</td>
                        <td style="text-align: right;"><span id="jdzuhur" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_dzuhur" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_dzuhur" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Ashar</td>
                        <td style="text-align: right;"><span id="jashar" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_ashar" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_ashar" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Maghrib</td>
                        <td style="text-align: right;"><span id="jmaghrib" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_maghrib" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_maghrib" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                    <tr>
                        <td>Isya</td>
                        <td style="text-align: right;"><span id="jisya" class="time-badge">--:--</span></td>
                        <td style="text-align: center;"><input type="checkbox" id="enable_isya" checked></td>
                        <td style="text-align: center;"><input type="number" id="koreksi_isya" style="width:60px;padding:5px;" placeholder="1"></td>
                    </tr>
                </tbody>
            </table>
            
            <label style="display: block; margin: 16px 0 12px 0;">Iqomah (menit)</label>
            <div class="grid-3">
                <div class="form-group"><label>Subuh</label><input type="number" id="iqmhs" placeholder="12"></div>
                <div class="form-group"><label>Dzuhur</label><input type="number" id="iqmhd" placeholder="8"></div>
                <div class="form-group"><label>Ashar</label><input type="number" id="iqmha" placeholder="6"></div>
                <div class="form-group"><label>Maghrib</label><input type="number" id="iqmhm" placeholder="5"></div>
                <div class="form-group"><label>Isya</label><input type="number" id="iqmhi" placeholder="5"></div>
                <div class="form-group"><label>Durasi Adzan</label><input type="number" id="durasiadzan" placeholder="1"></div>
            </div>
            
            <button class="btn btn-primary" onclick="setJws()">Simpan Jadwal</button>
        </div>
        
        <!-- Lokasi & Waktu -->
        <div class="section" id="lokasi">
            <div class="section-title">📍 Lokasi & Waktu</div>
            
            <div class="grid-2">
                <div class="form-group">
                    <label>Tanggal</label>
                    <input type="date" id="tanggal">
                </div>
                <div class="form-group">
                    <label>Jam</label>
                    <input type="time" id="jam">
                </div>
            </div>
            
            <button class="btn btn-primary" onclick="sendTanggalJam()">Set Waktu</button>
            
            <label style="display: block; margin: 16px 0 12px 0;">Koordinat</label>
            <div class="grid-2">
                <div class="form-group"><label>Latitude</label><input type="number" step="any" id="latitude" placeholder="-6.16"></div>
                <div class="form-group"><label>Longitude</label><input type="number" step="any" id="longitude" placeholder="106.61"></div>
                <div class="form-group"><label>Zona Waktu</label><input type="number" id="zonawaktu" placeholder="7"></div>
            </div>
            
            <button class="btn btn-secondary" onclick="window.open('https://easystem.co.id/latlong/', '_blank')" style="margin-bottom: 8px;">📍 Cek Latitude & Longitude</button>
            
            <button class="btn btn-primary" onclick="setJws()">Simpan Lokasi</button>
        </div>
        
        <!-- WiFi -->
        <div class="section" id="wifi">
            <div class="section-title">📡 WiFi</div>
            
            <label style="display: block; margin-bottom: 12px; color: #4CAF50; font-weight: 700;">Station Mode</label>
            <div class="grid-2">
                <div class="form-group">
                    <label>SSID</label>
                    <input type="text" id="wifissid" placeholder="WiFi name">
                </div>
                <div class="form-group">
                    <label>Password</label>
                    <input type="password" id="wifipassword" placeholder="Password">
                </div>
            </div>
            
            <div class="divider"></div>
            
            <label style="display: block; margin-bottom: 12px; color: #4CAF50; font-weight: 700;">Access Point</label>
            <div class="grid-2">
                <div class="form-group">
                    <label>SSID</label>
                    <input type="text" id="ssid" placeholder="JWS">
                </div>
                <div class="form-group">
                    <label>Password</label>
                    <input type="password" id="password" placeholder="Min. 8 char">
                </div>
            </div>
            
            <button class="btn btn-primary" onclick="setWifi()">Simpan WiFi</button>
        </div>
        
        <!-- System -->
        <div class="section" id="system">
            <div class="section-title">⚙️ System</div>

            <button class="btn btn-danger" onclick="resetDevice()">⚠️ Restart</button>

            <div class="info-box">
                <strong>Free Heap:</strong> <span id="heap">--</span> KB
            </div>
        </div>
        
        <div class="spacer"></div>
        
    </div>
    
    <!-- Toast -->
    <div id="toast">✓ Saved!</div>
    
    <script>
        let ws;
        let wsConnected = false;
        let reconnectAttempts = 0;
        let maxReconnectAttempts = 10;
        let xmlHttp = new XMLHttpRequest();
        
        function init() {
            console.log('🚀 JWS V4 Init');
            initWebSocket();
            startDataSync();
        }
        
        let messageQueue = [];
        let isSending = false;
        
        function initWebSocket() {
            try {
                ws = new WebSocket('ws://' + window.location.hostname + ':81/');
                
                ws.onopen = () => {
                    console.log('✓ WS Connected');
                    wsConnected = true;
                    reconnectAttempts = 0;
                    updateStatus(true);
                    toast('Connected');
                    processQueue();
                };
                
                ws.onclose = () => {
                    console.log('✗ WS Disconnected');
                    wsConnected = false;
                    updateStatus(false);
                    
                    if (reconnectAttempts < maxReconnectAttempts) {
                        reconnectAttempts++;
                        let delay = Math.min(1000 * Math.pow(2, reconnectAttempts - 1), 30000);
                        setTimeout(initWebSocket, delay);
                    }
                };
                
                ws.onerror = (e) => {
                    console.error('WS Error:', e);
                    updateStatus(false);
                };
                
                ws.onmessage = (e) => console.log('📩', e.data);
                
            } catch(e) {
                console.error('WS Init Error:', e);
                reconnectAttempts++;
                if (reconnectAttempts < maxReconnectAttempts) {
                    setTimeout(initWebSocket, 2000);
                }
            }
        }
        
        function sendWS(data) {
            messageQueue.push(data);
            processQueue();
        }
        
        function processQueue() {
            if (!wsConnected || isSending || messageQueue.length === 0) return;
            
            isSending = true;
            const message = messageQueue.shift();
            
            try {
                ws.send(message);
                console.log('📤', message);
                setTimeout(() => {
                    isSending = false;
                    processQueue();
                }, 100);
            } catch(e) {
                console.error('Send error:', e);
                messageQueue.unshift(message);
                isSending = false;
            }
        }
        
        function updateStatus(online) {
            const dot = document.getElementById('status-dot');
            const text = document.getElementById('status-text');
            if (online) {
                dot.className = 'status-dot online';
                text.textContent = 'Online';
            } else {
                dot.className = 'status-dot';
                text.textContent = 'Offline';
            }
        }
        
        function toast(msg) {
            const t = document.getElementById('toast');
            t.textContent = msg;
            t.className = 'show';
            setTimeout(() => t.className = '', 3000);
        }
        
        function startDataSync() {
            syncConfig();
            syncRealtime();
            setInterval(syncRealtime, 1000);
        }
        
        function syncConfig() {
            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open('GET', 'xml', true);
                xmlHttp.onreadystatechange = handleConfig;
                xmlHttp.send(null);
            }
        }
        
        function syncRealtime() {
            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open('GET', 'realxml', true);
                xmlHttp.onreadystatechange = handleRealtime;
                xmlHttp.send(null);
            }
        }
        
        function handleConfig() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                const xml = xmlHttp.responseXML;
                const getVal = (tag) => {
                    const el = xml.getElementsByTagName(tag);
                    return el.length > 0 ? el[0].firstChild.nodeValue : '';
                };
                
                const fields = ['nama', 'info1', 'info2', 'iqmhs', 'iqmhd', 'iqmha', 'iqmhm', 'iqmhi',
                               'durasiadzan', 'latitude', 'longitude', 'zonawaktu', 'panel', 'dim_brightness',
                               'ssid', 'password', 'wifissid', 'wifipassword'];
                
                fields.forEach(id => {
                    const el = document.getElementById(id);
                    if (el && document.activeElement !== el) {
                        const val = getVal('r' + id.charAt(0).toUpperCase() + id.slice(1));
                        if (val) el.value = val;
                    }
                });
                
                // Load enable/disable per waktu
                const enableFields = ['enable_tanbih', 'enable_imsak', 'enable_subuh', 'enable_dzuhur', 
                                    'enable_ashar', 'enable_maghrib', 'enable_isya'];
                enableFields.forEach(id => {
                    const el = document.getElementById(id);
                    if (el) {
                        const val = getVal('r' + id.charAt(0).toUpperCase() + id.slice(1));
                        el.checked = (val === '1' || val === 'true' || val === '');
                    }
                });
                
                // Load koreksi per waktu
                const koreksiFields = ['koreksi_tanbih', 'koreksi_imsak', 'koreksi_subuh', 'koreksi_dzuhur',
                                      'koreksi_ashar', 'koreksi_maghrib', 'koreksi_isya'];
                koreksiFields.forEach(id => {
                    const el = document.getElementById(id);
                    if (el && document.activeElement !== el) {
                        const val = getVal('r' + id.charAt(0).toUpperCase() + id.slice(1));
                        if (val) el.value = val;
                    }
                });

                // Load dim time inputs
                const startHour = getVal('rDimStartHour');
                const startMin = getVal('rDimStartMin');
                const endHour = getVal('rDimEndHour');
                const endMin = getVal('rDimEndMin');
                if (startHour && startMin) {
                    document.getElementById('dim_start_time').value = ('0' + startHour).slice(-2) + ':' + ('0' + startMin).slice(-2);
                }
                if (endHour && endMin) {
                    document.getElementById('dim_end_time').value = ('0' + endHour).slice(-2) + ':' + ('0' + endMin).slice(-2);
                }

                ['jtanbih', 'jsubuh', 'jdzuhur', 'jashar', 'jmaghrib', 'jisya'].forEach(id => {
                    const val = getVal('r' + id.charAt(1).toUpperCase() + id.slice(2));
                    if (val) {
                        // Extract time from "Sholat HH:MM" format
                        const timeMatch = val.match(/(\d{2}:\d{2})/);
                        if (timeMatch) {
                            document.getElementById(id).textContent = timeMatch[1];
                        } else {
                            document.getElementById(id).textContent = val.replace(/^\w+\s+/, '');
                        }
                    }
                });
                
                // Imsak
                const imsakVal = getVal('rImsak');
                if (imsakVal) {
                    const timeMatch = imsakVal.match(/(\d{2}:\d{2})/);
                    if (timeMatch) {
                        document.getElementById('jimsak').textContent = timeMatch[1];
                    } else {
                        document.getElementById('jimsak').textContent = imsakVal.replace(/^\w+\s+/, '');
                    }
                }
            }
        }
        
        function handleRealtime() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                const xml = xmlHttp.responseXML;
                const getVal = (tag) => {
                    const el = xml.getElementsByTagName(tag);
                    return el.length > 0 ? el[0].firstChild.nodeValue : '';
                };
                
                const h = getVal('rHour');
                const m = getVal('rMinute');
                const s = getVal('rSecond');
                document.getElementById('clock').textContent = `${h}:${m}:${s}`;
                
                const d = getVal('rDay');
                const mo = getVal('rMonth');
                const y = getVal('rYear');
                const months = ['Jan','Feb','Mar','Apr','Mei','Jun','Jul','Agt','Sep','Okt','Nov','Des'];
                document.getElementById('date').textContent = `${d} ${months[parseInt(mo)-1] || ''} ${y}`;
                
                document.getElementById('temp').textContent = getVal('rTemp');
                
                const volEl = document.getElementById('volume');
                if (document.activeElement !== volEl) {
                    const vol = getVal('rVolume');
                    if (vol) volEl.value = vol;
                }
                
                const kecEl = document.getElementById('kecerahan');
                if (document.activeElement !== kecEl) {
                    const kec = getVal('rKecerahan');
                    if (kec) kecEl.value = kec;
                }
                
                const heap = getVal('rHeap');
                if (heap) document.getElementById('heap').textContent = (parseInt(heap)/1024).toFixed(1);
            }
        }
        
        function sendVolume() {
            const vol = Math.min(30, Math.max(0, parseInt(document.getElementById('volume').value)));
            document.getElementById('volume').value = vol;
            sendWS('#{"volume":' + vol + '}');
            toast('Volume: ' + vol);
        }
        
        function sendPlay() { sendWS('dplay'); toast('Play'); }
        function sendPause() { sendWS('dpause'); toast('Pause'); }
        function sendStop() { sendWS('dstop'); toast('Stop'); }
        function sendNext() { sendWS('dnext'); toast('Next'); }
        function sendPrev() { sendWS('dprev'); toast('Previous'); }
        function sendRandom() { sendWS('drandom'); toast('Random'); }
        
        function sendAudioSettings() {
            const playlist = document.getElementById('playlist').value;
            const eq = document.getElementById('equalizer').value;
            sendWS(playlist);
            setTimeout(() => sendWS(eq), 150);
            toast('Settings Applied');
        }
        
        function sendModeJam() { sendWS('dmodejam'); toast('Mode Jam'); }
        function sendModeMP3() { sendWS('dmodemp3'); toast('Mode Audio'); }
        function sendTesLED() { sendWS('dtesled'); toast('Test LED'); }
        
        function sendKecerahan() {
            const kec = Math.min(254, Math.max(15, parseInt(document.getElementById('kecerahan').value)));
            const panel = document.getElementById('panel').value;
            document.getElementById('kecerahan').value = kec;
            sendWS('c{"kecerahan":' + kec + ',"panel":' + panel + '}');
            toast('Display Updated');
        }
        
        function sendNama() {
            const data = {
                nama: document.getElementById('nama').value,
                info1: document.getElementById('info1').value,
                info2: document.getElementById('info2').value
            };
            sendWS('i' + JSON.stringify(data));
            toast('Info Saved');
        }
        
        function setJws() {
            const data = {
                iqmhs: parseInt(document.getElementById('iqmhs').value) || 12,
                iqmhd: parseInt(document.getElementById('iqmhd').value) || 8,
                iqmha: parseInt(document.getElementById('iqmha').value) || 6,
                iqmhm: parseInt(document.getElementById('iqmhm').value) || 5,
                iqmhi: parseInt(document.getElementById('iqmhi').value) || 5,
                durasiadzan: parseInt(document.getElementById('durasiadzan').value) || 1,
                latitude: parseFloat(document.getElementById('latitude').value) || -6.16,
                longitude: parseFloat(document.getElementById('longitude').value) || 106.61,
                zonawaktu: parseInt(document.getElementById('zonawaktu').value) || 7,
                // Enable/Disable per waktu
                enable_tanbih: document.getElementById('enable_tanbih').checked ? 1 : 0,
                enable_imsak: document.getElementById('enable_imsak').checked ? 1 : 0,
                enable_subuh: document.getElementById('enable_subuh').checked ? 1 : 0,
                enable_dzuhur: document.getElementById('enable_dzuhur').checked ? 1 : 0,
                enable_ashar: document.getElementById('enable_ashar').checked ? 1 : 0,
                enable_maghrib: document.getElementById('enable_maghrib').checked ? 1 : 0,
                enable_isya: document.getElementById('enable_isya').checked ? 1 : 0,
                // Koreksi per waktu
                koreksi_tanbih: parseInt(document.getElementById('koreksi_tanbih').value) || 1,
                koreksi_imsak: parseInt(document.getElementById('koreksi_imsak').value) || 1,
                koreksi_subuh: parseInt(document.getElementById('koreksi_subuh').value) || 1,
                koreksi_dzuhur: parseInt(document.getElementById('koreksi_dzuhur').value) || 1,
                koreksi_ashar: parseInt(document.getElementById('koreksi_ashar').value) || 1,
                koreksi_maghrib: parseInt(document.getElementById('koreksi_maghrib').value) || 1,
                koreksi_isya: parseInt(document.getElementById('koreksi_isya').value) || 1,
                // Dimming settings
                dim_start_hour: parseInt(document.getElementById('dim_start_time').value.split(':')[0]) || 22,
                dim_start_min: parseInt(document.getElementById('dim_start_time').value.split(':')[1]) || 0,
                dim_end_hour: parseInt(document.getElementById('dim_end_time').value.split(':')[0]) || 2,
                dim_end_min: parseInt(document.getElementById('dim_end_time').value.split(':')[1]) || 0,
                dim_brightness: parseInt(document.getElementById('dim_brightness').value) || 70
            };
            sendWS('s' + JSON.stringify(data));
            toast('JWS Config Saved');
        }
        
        function sendTanggalJam() {
            const tgl = document.getElementById('tanggal').value;
            const jam = document.getElementById('jam').value;
            if (tgl) {
                sendWS('t' + tgl.replace(/-/g, ''));
                setTimeout(() => {
                    if (jam) sendWS('j' + jam.replace(':', ''));
                }, 150);
                toast('Time Updated');
            }
        }
        
        function setWifi() {
            const data = {
                wifissid: document.getElementById('wifissid').value,
                wifipassword: document.getElementById('wifipassword').value,
                ssid: document.getElementById('ssid').value,
                password: document.getElementById('password').value
            };
            sendWS('w' + JSON.stringify(data));
            toast('WiFi Saved. Restart to apply.');
        }
        
        function resetDevice() {
            if (confirm('Restart device?')) {
                sendWS('z');
                toast('Restarting...');
                setTimeout(() => location.reload(), 5000);
            }
        }
    </script>
</body>
</html>


)=====";
