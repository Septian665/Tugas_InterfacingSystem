#include <ESP8266WiFi.h>
#include <DHT.h>
#include "FirebaseESP8266.h"

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht11(DHTPIN, DHTTYPE);

#define FIREBASE_HOST "suhu-2e648-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "T2xC3vQGdFK413YZoGD2bR6uOA3fcniFVnvRa0zn"

#define WIFI_SSID "XIAOMI"
#define WIFI_PASSWORD "Xiaomi123"

FirebaseData firebaseData;

void setup(){
  Serial.begin(115200);

  dht11.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connected");
  while (WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  float t = dht11.readTemperature();
  float h = dht11.readHumidity();

  if (isnan(t) || isnan(h)){
    Serial.println("Failed");
    delay(1000);
    return;
  }

  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembapan : ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  if(Firebase.setFloat(firebaseData,"/Hasil_Testing/Suhu", t)){
    Serial.println("suhu terkirim");
  }else{
    Serial.println("suhu tidak terkirim");
    Serial.println("karena : "+firebaseData.errorReason());
  }

   if(Firebase.setFloat(firebaseData,"/Hasil_Testing/kelembapan", h)){
    Serial.println("kelembaban terkirim");
  }else{
    Serial.println("kelembaban tidak terkirim");
    Serial.println("karena : "+firebaseData.errorReason());
  }
  delay(100);
}
