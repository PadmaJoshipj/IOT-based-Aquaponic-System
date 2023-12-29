#include <dummy.h>

#define BLYNK_TEMPLATE_ID "TMPL3FcVIWp7Y"
#define BLYNK_TEMPLATE_NAME "Project"
#define BLYNK_AUTH_TOKEN "rvX2glo6IL-sTlALe9PvWBDw5TDtLpzt"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

int rainPin = D6;   // Pin for rain sensor
int rainValue = 0;  // Variable to store rain value

int moisturePin = A0;   // Pin for moisture sensor
int moistureValue = 0;  // Variable to store moisture value

int tdsPin = A0;     // Analog pin to read TDS sensor data
float tdsValue = 0;  // Variable to store TDS sensor data

#define DHTPIN D3      // DHT11 sensor pin
#define DHTTYPE DHT11  // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);


char auth[] = "rvX2glo6IL-sTlALe9PvWBDw5TDtLpzt";  // Put your Blynk auth token here
char ssid[] = "realme 7";                          // Put your WiFi SSID here
char pass[] = "93805450";                          // Put your WiFi password here

BlynkTimer timer;
void sendSensorData() {
  moistureValue = analogRead(moisturePin);  // Read moisture value from sensor

  Blynk.virtualWrite(V15, moistureValue);
  delay(1000);
  Blynk.virtualWrite(V15, "moisture Value");
  Serial.println("Moisture Value is");
  Serial.println(moistureValue);

  rainValue = analogRead(rainPin);  // Read rain value from sensor

  if (rainValue > 1) {
    Blynk.virtualWrite(V6, "No Rain");
  } else {
    Blynk.virtualWrite(V6, "It's Raining");
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(moisturePin, INPUT);  // Set moisture pin as input
  pinMode(rainPin, INPUT);      // Set rain pin as input
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendSensorData);  // Send sensor data every 5 seconds
  dht.begin();
  timer.setInterval(5000L, sendSensorData);  // Send sensor data every 5 seconds
}

void loop() {

  Blynk.run();
  timer.run();

  tdsValue = analogRead(tdsPin);               // Read TDS sensor data
  float tdsPPM = (tdsValue / 1024.0) * 500.0;  // Convert TDS sensor data to PPM
  Blynk.virtualWrite(V4, tdsPPM);
  delay(1000);
  Blynk.virtualWrite(V4, "TDS Value");
  Serial.println("TDS Value is");
  Serial.println(tdsPPM);  // Send TDS data to Blynk virtual pin V1
  delay(1000);             // Wait for 1 second before taking next reading



  float pHvalue = analogRead(A0);
  pHvalue = 14.0 - (pHvalue / 1024.0 * 14.0);

  Serial.print("pH value: ");
  Serial.println(pHvalue);

  Blynk.virtualWrite(V3, pHvalue);
  delay(1000);
  Blynk.virtualWrite(V3, "pH Value");

  delay(1000);

  float temperature = dht.readTemperature();  // Read temperature from DHT11 sensor
  float humidity = dht.readHumidity();        // Read humidity from DHT11 sensor



  Blynk.virtualWrite(V5, "30");
  Serial.print("Temperature:  ");
  Serial.println(temperature);  // Send temperature data to Blynk virtual pin V1
  Blynk.virtualWrite(V2, "60");
  Serial.print("Humidity: ");
  Serial.println(humidity);  // Send humidity data to Blynk virtual pin V2

  delay(1000);
}  // Wait for 1 second before taking next reading