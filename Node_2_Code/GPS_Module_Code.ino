void GPS_Reading() {
  unsigned long start = millis();
  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }
    if (gps.location.isUpdated()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      altitude = gps.altitude.meters();
      hdop = (gps.hdop.value() / 100.0);
      satelites = gps.satellites.value();
    }
  }
}
