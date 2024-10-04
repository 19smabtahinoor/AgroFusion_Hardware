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
