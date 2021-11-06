#include <SoftwareSerial.h>
// SoftwareSerial SerialAT(3, 4); // RX, TX
// SoftwareSerial SerialAT(2, 3); // RX, TX
#include "sensor.h"
// #include <TinyGPS++.h>
// SoftwareSerial GPSpin(8, 7);
// TinyGPSPlus gps;
// tinyGSM Library configuration
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 650
#endif
// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS
// Define the serial console for debug prints, if needed
// #define TINY_GSM_DEBUG Serial
// #define LOGGING  // <- Logging is for the HTTP library

// Add a reception delay - may be needed for a fast processor at a slow baud rate
// #define TINY_GSM_YIELD() { delay(2); }

// Range to attempt to autobaud
// #define GSM_AUTOBAUD_MIN 9600
// #define GSM_AUTOBAUD_MAX 115200
// #define TINY_GSM_USE_GPRS true
// #ifdef DUMP_AT_COMMANDS
//   #include <StreamDebugger.h>
//   StreamDebugger debugger(SerialAT, Serial);
//   TinyGsm modem(debugger);
// #else
  TinyGsm modem(SerialAT);
// #endif
// set GSM PIN, if any
// #define GSM_PIN ""
// Your GPRS credentials, if any
const char apn[]  = "internet"; //APN TELKOMSEL
// const char gprsUser[] = "";
// const char gprsPass[] = "";


char server[] = "https://pl2pmd9w21.execute-api.us-east-1.amazonaws.com";
char resource[] = "dev/create-sensor-data";
const int  port = 443; //https
TinyGsmClient client(modem);
HttpClient http(client, server, port);

// #include <ArduinoJson.h>

// #include <TimeLib.h>


void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  // TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialAT.begin(9600);
  // GPSpin.begin(9600);
  SerialAT.listen();
  // Serial.println("Initializing modem...");
  // modem.init();
  // Serial.print("modem info: ");
  // Serial.println(modem.getModemInfo());
  
  // Unlock your SIM card with a PIN if needed
  // if ( GSM_PIN && modem.getSimStatus() != 3 ) {
  //   modem.simUnlock(GSM_PIN);
  // }
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  bmesetup();

}
// DynamicJsonDocument doc(192);
// float latitude = 0, longitude = 0;
void loop() {
  // put your main code here, to run repeatedly:
      
    // modem.isGprsConnected();
    if (modem.isGprsConnected()) {
      Serial.println("GPRS connected");
    }
    else {
      // Serial.print(F("Connecting to APN "));
      // Serial.print(apn);
    if (!modem.gprsConnect(apn, "", "")) {
  Serial.println(" fail");
      digitalWrite(10,HIGH);
      delay(500);
      digitalWrite(10,LOW);
      delay(1000);
      digitalWrite(10,HIGH);
      delay(10000);
      return;
    }
Serial.println("SUCCESS");
    }
    
    // GPSpin.listen();
    // delay(200);
    // while (GPSpin.available()>0)
    //   {Serial.write(GPSpin.read());
    // }
    // if (gps.encode(GPSpin.read()))
    // if(gps.location.isValid()){
    // latitude = gps.location.lat();
    //Serial.print(gps.location.lat(), 6);
    //Serial.print(F(","));
    // longitude = gps.location.lng();
    //Serial.print(gps.location.lng(), 6);
    // }
  //   if (gps.date.isValid() && gps.time.isValid())
  // {
  //   if(timeStatus()==0){
  //     setTime(gps.time.hour(),gps.time.minute(),gps.time.second(),gps.date.day(),gps.date.month(),gps.date.year());
  //   }
  // }
    // String postData = "{\"s1\":"+ soilSensor(0) +",\"s2\":"+ soilSensor(1) +",\"alt\":" + altSensor() + ",\"hum\":"+humSensor() +",\"bv\":"+ battVolt(2) +",\"pv\":"+ pvVolt(3) +",\"lat\":"+ "0" +",\"lon\":"+ "0" +",\"ts\":"+ "0"+",\"id\":\"9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d\"}";
    // String postData = String(soilSensor(0)) + "," +  String(soilSensor(1)) + "," + String(altSensor()) + "," + String(humSensor()) + "," + String(battVolt(2)) + "," + String(pvVolt(3)) + "," + String(latitude) + "," + String(longitude) + "," + "9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d";
    String postData = "{\"s1\":"+ String(123) +",\"s2\":"+ String(123) +",\"alt\":" + String(1234.56) + ",\"hum\":"+String(34.23) +",\"bv\":"+ String(123.45) +",\"pv\":"+ String(123.45) +",\"lat\":"+ "0" +",\"lon\":"+ "0" +",\"ts\":"+ "0"+",\"id\":\"9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d\"}";
    // doc["s1"] = soilSensor(0);
    // doc["s2"] = soilSensor(1);
    // doc["alt"] = altSensor();
    // doc["hum"] = humSensor();
    // doc["bv"] = battVolt(2);
    // doc["pv"] = pvVolt(3);
    // doc["lat"] = latitude;
    // doc["lon"] = longitude;
    // doc["ts"] = now();
    // doc["id"] = "9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d";
    // serializeJson(doc, postData);
//Serial.println();
    SerialAT.listen();
    http.beginRequest();
    http.post(resource);
    http.sendHeader(HTTP_HEADER_CONTENT_TYPE,"application/json");
    // http.sendHeader("x-api-key","S5iloPRjt18t7G1oLOcto9u8gBn24bhC7TH6mbn7");
    http.beginBody();
    http.print(postData);
    http.endRequest();

    // int statusCode = http.responseStatusCode();
    // String response = http.responseBody();

  // Serial.print("Status code: ");
  // Serial.println(statusCode);
  // Serial.print("Response: ");
  // Serial.println(response);
}
