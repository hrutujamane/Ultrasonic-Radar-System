#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// Replace with your Wi-Fi credentials before use.
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const int TRIG_PIN = D5;
const int ECHO_PIN = D6;   // MUST be level-shifted to 3.3 V
const int SERVO_PIN = D2;

Servo radarServo;
ESP8266WebServer server(80);

volatile int currentAngle = 15;
volatile long currentDistance = -1;

long measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1;
  return (long)(duration * 0.0343 / 2.0);
}

String pageHtml() {
  return R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP8266 Ultrasonic Radar</title>
<style>
body{font-family:Arial;background:#0b1410;color:#dfffea;text-align:center;padding:30px}
.card{max-width:420px;margin:auto;background:#122219;border-radius:18px;padding:24px}
.big{font-size:42px;font-weight:bold}
small{color:#9fc1aa}
</style>
</head>
<body>
<div class="card">
<h2>📡 Ultrasonic Radar</h2>
<p>Angle</p><div class="big"><span id="a">--</span>°</div>
<p>Distance</p><div class="big"><span id="d">--</span> cm</div>
<small>ESP8266 prototype</small>
</div>
<script>
setInterval(async()=>{
  const r=await fetch('/data');
  const j=await r.json();
  document.getElementById('a').textContent=j.angle;
  document.getElementById('d').textContent=j.distance;
},250);
</script>
</body>
</html>
)rawliteral";
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  radarServo.attach(SERVO_PIN);
  radarServo.write(currentAngle);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Open http://");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", pageHtml());
  });

  server.on("/data", []() {
    String json = "{\"angle\":" + String(currentAngle) +
                  ",\"distance\":" + String(currentDistance) + "}";
    server.send(200, "application/json", json);
  });

  server.begin();
}

void loop() {
  server.handleClient();

  static int direction = 1;
  static unsigned long lastMove = 0;

  if (millis() - lastMove >= 60) {
    lastMove = millis();

    currentAngle += direction * 2;
    if (currentAngle >= 165) {
      currentAngle = 165;
      direction = -1;
    } else if (currentAngle <= 15) {
      currentAngle = 15;
      direction = 1;
    }

    radarServo.write(currentAngle);
    delay(20);
    currentDistance = measureDistanceCm();
  }
}
