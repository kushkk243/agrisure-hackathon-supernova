#define BLYNK_TEMPLATE_ID "TMPL3V3qSI-M4"
#define BLYNK_TEMPLATE_NAME "Parth"
#define BLYNK_AUTH_TOKEN "kZe6zuBivQAde3-2rk_2PjyKG0XHvwky"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define BLYNK_PRINT Serial
#define DHTPIN 2
#define DHTTYPE DHT11  // DHT 11



char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "wine party";  // type your wifi name
char pass[] = "12345678";  // type your wifi password

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


BlynkTimer timer;

BLYNK_WRITE(V3) {
  Serial.println("HI");
  int x = param.asInt();  // assigning incoming value from pin V5 to a variable
  digitalWrite(D1, LOW);

  Serial.println(x);

  if (x == 0)
    digitalWrite(D0, LOW);
  else
    digitalWrite(D0, HIGH);
}

void sendSensor() {
  int value = analogRead(A0);
  Serial.print("Soil Moisture : ");
  Serial.print(value);
  Blynk.virtualWrite(V2, value);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("\nError reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Blynk.virtualWrite(V0, event.temperature);
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Blynk.virtualWrite(V1, event.relative_humidity);
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));


  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
