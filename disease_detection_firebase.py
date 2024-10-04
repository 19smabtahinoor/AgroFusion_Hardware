import torch
import cv2
import sys
import pathlib
import firebase_admin
from firebase_admin import credentials, db

pathlib.PosixPath = pathlib.WindowsPath

model_path = r'plant.pt'
model = torch.hub.load('ultralytics/yolov5', 'custom',
                       path=model_path)
model.conf = 0.85  # Confidence threshold (0-1)
model.iou = 0.2

# Path to your Firebase Admin SDK credentials file
cred = credentials.Certificate("secret_key.json")

# Initialize the Firebase app
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://esp32-dht11-data-3e83d-default-rtdb.asia-southeast1.firebasedatabase.app/' 
})

def send_data_to_firebase(data, path):
    ref = db.reference(path) 
    ref.set(data) 
    print(f"Data sent to {path}: {data}")

def detect(image):
    # image = r'Plant Disease Detection\test\chilli bacterial leaf spot.jpg'
    # frame = cv2.imread(image)

    frame = image
    # frame = cv2.resize(frame, (534, 474))
    detections = model(frame[..., ::-1])
    results = detections.pandas().xyxy[0].to_dict(orient="records")

    if len(results) > 0:
        print(results)
        print('\n')

    for result in results:
        cs = result['name']
        con = round((result['confidence'])*100, 2)
        x1 = int(result['xmin'])
        y1 = int(result['ymin'])
        x2 = int(result['xmax'])
        y2 = int(result['ymax'])

        cv2.rectangle(frame, (x1, y1+40), (x2, y1),
                      (255, 0, 255), cv2.FILLED)
        cv2.putText(frame, f"{cs} {con}%", (x1, y1+30),
                    cv2.FONT_HERSHEY_PLAIN, 1, (255, 255, 255), 1)
        cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 255), 2)
        
        print(f'Disease Name: {cs}')
        print(f'Confidence: {con}%')
        send_data_to_firebase(cs, "Webcam/disease_name")

    cv2.imshow('Output', frame)

    if cv2.waitKey(1) == 32:
        cv2.destroyAllWindows()
        sys.exit()


if __name__ == "__main__":
    webcam = cv2.VideoCapture(0)
    while True:
        ret, im = webcam.read()
        if ret:
            detect(im)


