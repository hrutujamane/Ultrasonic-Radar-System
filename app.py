from flask import Flask, jsonify, render_template
import math
import threading
import time

try:
    import serial
except ImportError:
    serial = None

app = Flask(__name__)

# Update this to match your Arduino port if needed.
SERIAL_PORT = "COM6"
BAUD_RATE = 9600

latest = {
    "angle": 90,
    "distance": -1,
    "connected": False,
    "mode": "demo"
}

lock = threading.Lock()


def serial_worker():
    """Read `angle,distance` CSV lines from Arduino."""
    if serial is None:
        return

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2)

        with lock:
            latest["connected"] = True
            latest["mode"] = "serial"

        while True:
            raw = ser.readline().decode("utf-8", errors="ignore").strip()
            if not raw:
                continue

            try:
                angle_text, distance_text = raw.split(",", 1)
                angle = int(angle_text)
                distance = int(float(distance_text))

                with lock:
                    latest["angle"] = max(0, min(180, angle))
                    latest["distance"] = distance
            except (ValueError, TypeError):
                pass

    except Exception:
        with lock:
            latest["connected"] = False
            latest["mode"] = "demo"


def demo_worker():
    """Generate sweep data only when no serial device is connected."""
    angle = 15
    direction = 1

    while True:
        with lock:
            if not latest["connected"]:
                latest["angle"] = angle
                # Fake object distance for UI preview only.
                latest["distance"] = int(
                    55 + 25 * math.sin(math.radians(angle * 2.2))
                )

        angle += direction * 2
        if angle >= 165:
            angle = 165
            direction = -1
        elif angle <= 15:
            angle = 15
            direction = 1

        time.sleep(0.05)


@app.route("/")
def home():
    return render_template("index.html")


@app.route("/api/data")
def api_data():
    with lock:
        return jsonify(dict(latest))


if __name__ == "__main__":
    threading.Thread(target=serial_worker, daemon=True).start()
    threading.Thread(target=demo_worker, daemon=True).start()
    app.run(debug=False)
