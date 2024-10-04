#include <WiFi.h>
#include "DHT.h"
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <HTTPClient.h>

// Insert your network credentials
//#define WIFI_SSID "AIUB Student Wi-Fi"

#define WIFI_SSID "Yasar22B"
#define WIFI_PASS "1131411314"

// Insert Firebase project API Key
#define API_KEY "AIzaSyD7fCvOtReJI3qu3ed9mAzMb22vX6HhDqk"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp32-dht11-data-3e83d-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Server URL
char* humURL = "https://agro-fusion.vercel.app/api/humidity";
char* waterURL = "https://agro-fusion.vercel.app/api/water_level";

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
#define interval 10000

#define DHT_pin 4
#define SoilMoisturePin 36
#define WaterSensor 35
#define TurbidityPin 34

DHT dht(DHT_pin, DHT11);

#define VREF 3.3              // analog reference voltage(Volt) of the ADC
#define SCOUNT  30            // sum of sample point
int analogBuffer[SCOUNT], analogBufferTemp[SCOUNT], analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;     // current temperature for compensation

void setup() {
  Serial.begin(115200);
  wifi_connect();

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(SoilMoisturePin, INPUT);
  pinMode(WaterSensor, INPUT);
  pinMode(TurbidityPin, INPUT);
  dht.begin();
}

void loop() {
  int turbidity = map(analogRead(TurbidityPin), 0, 2800, 100, 1);
  int moisture = map(analogRead(SoilMoisturePin), 0, 4095, 100, 0);
  int waterLevel = map(analogRead(WaterSensor), 0, 4095, 0, 100);
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();

  if (WiFi.status() == WL_CONNECTED && Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > interval || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.setFloat(&fbdo, "ESP32/SoilMoisture1", moisture)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "ESP32/WaterLevel1", waterLevel)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "ESP32/Humidity", hum)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "ESP32/Temperature", temp)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "ESP32/Turbidity", turbidity)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    sendPostRequest(humURL, "humidity", hum);
    sendPostRequest(waterURL, "water_level", waterLevel);

    delay(5000);
    ESP.restart();
  }
}
