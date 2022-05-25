#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// DEFINE DHT 11
//#define DHTTYPE DHT11

//Conectarse a WiFi
const char* ssid = "itesm-servicios";
const char* password = "appletam";

// IP Raspberry Pi
const char* mqtt_server = "10.34.156.137";
const char* clientID = "SensorHT_1";

// Configurar el ESP como cliente en el servidor MQTT
WiFiClient ESP8266_1;
PubSubClient client(mqtt_server, 1883, ESP8266_1);


// Inicializar el DHT11
DHT dht(D1, DHT11);

long now = millis();
long lastMeasure = 0;

void setup_wifi() {
  delay(50);
  // Connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connected to MQTT failed...");
  }
}

void setup() {
  dht.begin();
  Serial.begin(9600);
  setup_wifi();
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connected to MQTT failed...");
  }
}

void loop() {
  if (!client.connect(clientID)) {
    reconnect();
  }


  now = millis();
  
  
  if (now - lastMeasure > 10000) {
    lastMeasure = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    static char temperatureTemp[7];
    dtostrf(hic, 6, 2, temperatureTemp);

    static char humidityTemp[7];
    dtostrf(h, 6, 2, humidityTemp);

    //
    client.publish("/ITESM/PUEBLA/temperature", temperatureTemp);
    client.publish("/ITESM/PUEBLA/humidity", humidityTemp);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(hic);
    Serial.print(" °C ");  
    Serial.println("");  
  }
}
