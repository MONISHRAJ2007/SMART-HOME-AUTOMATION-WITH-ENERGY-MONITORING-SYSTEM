import cv2
import numpy as np
from tensorflow.keras.models import load_model
import requests
import time
import os

print("Current Folder:", os.getcwd())
print("Model exists:", os.path.exists("keras_model.h5"))

# ---------------- CONFIG ---------------- #
ESP32_IP = "http://192.168.181.146"
AUTHORIZED_LABEL = "Class 1"
CONFIDENCE_THRESHOLD = 0.75

MODEL_PATH = "keras_model.h5"
LABELS_PATH = "labels.txt"

# ---------------- LOAD MODEL ---------------- #
print("Loading AI model... please wait.")

np.set_printoptions(suppress=True)

try:
    model = load_model(MODEL_PATH, compile=False)
except Exception as e:
    print(f"❌ MODEL ERROR: {e}")
    exit()

try:
    with open(LABELS_PATH, "r") as f:
        class_names = f.readlines()
except:
    print("❌ labels.txt not found!")
    exit()

print("✅ Model Loaded Successfully!")

# ---------------- NETWORK SESSION ---------------- #
session = requests.Session()

# ---------------- CAMERA ---------------- #
cam = cv2.VideoCapture(0)

if not cam.isOpened():
    print("❌ Camera not working!")
    exit()

print("📷 Camera Started... System Ready!")

last_trigger = 0

# ---------------- MAIN LOOP ---------------- #
while True:
    ret, frame = cam.read()
    if not ret:
        print("❌ Camera read failed")
        break

    # -------- PREPROCESS -------- #
    image = cv2.resize(frame, (224, 224))
    image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)
    image = (image / 127.5) - 1

    # -------- PREDICTION -------- #
    prediction = model.predict(image, verbose=0)
    index = np.argmax(prediction)

    raw_class_name = class_names[index].strip()
    clean_class_name = raw_class_name.split(" ", 1)[1] if " " in raw_class_name else raw_class_name
    confidence_score = prediction[0][index]

    print(f"Detected: {clean_class_name} | Confidence: {confidence_score:.2f}")

    # -------- LOGIC -------- #
    if clean_class_name == AUTHORIZED_LABEL and confidence_score >= CONFIDENCE_THRESHOLD:
        status_text = f"UNLOCKING - {clean_class_name} ({confidence_score*100:.0f}%)"
        color = (0, 255, 0)

        if time.time() - last_trigger > 5:
            print("📡 Sending request to ESP32...")

            success = False

            # 🔁 Retry 3 times
            for attempt in range(3):
                try:
                    response = session.get(
                        ESP32_IP + "/unlock",
                        timeout=5,
                        headers={"Connection": "close"}
                    )

                    print("✅ ESP32 Response:", response.text)
                    print("🚪 Trigger SUCCESS")
                    success = True
                    break

                except Exception as e:
                    print(f"⚠️ Attempt {attempt+1} failed:", e)
                    time.sleep(1)

            if not success:
                print("❌ ESP32 FAILED after retries")

            last_trigger = time.time()

    else:
        status_text = f"LOCKED - {clean_class_name} ({confidence_score*100:.0f}%)"
        color = (0, 0, 255)

    # -------- DISPLAY -------- #
    cv2.putText(frame, status_text, (10, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)

    cv2.imshow("Smart Security Camera", frame)

    if cv2.waitKey(1) == 27:
        break

# ---------------- CLEANUP ---------------- #
cam.release()
cv2.destroyAllWindows()


#& "D:\project\face reg\python 3.10\python.exe" teachable_unlock.py