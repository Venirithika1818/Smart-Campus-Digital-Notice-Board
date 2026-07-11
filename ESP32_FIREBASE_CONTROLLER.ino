#include <WiFi.h>
#include <FirebaseESP32.h>

#define SSID     "Rithukumar"
#define PASSWORD "rithukumar818"

#define FIREBASE_HOST "display-23c68-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "4zwDf0YoQf9hguuT9oEWq0lsNiqRLAaWOIKiqLQo"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String lastData = "";

void setup()
{
  Serial.begin(9600);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.getString(fbdo, "/display"))
  {
    String data = fbdo.stringData();
    Serial.println(data);

    if (data != lastData)
    {
      Serial2.println(data);   
      lastData = data;
    }
  }

  delay(1000);
}
