int sendPostRequest(char* serverUrl, String key_name, int value) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Specify the URL
    http.begin(serverUrl);
    // Specify content type
    http.addHeader("Content-Type", "application/json");

    // JSON data to send
    String jsonData = "{\"" + key_name + "\":" + String(value) + "}";
    Serial.println(jsonData);

    // Send the POST request
    int httpResponseCode = http.POST(jsonData);
    // Check for the response
    while (httpResponseCode != 200) {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }
    String response = http.getString();
    Serial.println("Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
    // Free resources
    http.end();
    return httpResponseCode;
  }
  else {
    Serial.println("WiFi not connected");
  }
}

void wifi_connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
