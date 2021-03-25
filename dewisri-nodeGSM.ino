#include <SoftwareSerial.h>
SoftwareSerial SerialAT(7, 8); // RX, TX

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
#define TINY_GSM_DEBUG Serial
// #define LOGGING  // <- Logging is for the HTTP library
// Range to attempt to autobaud
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200
#define TINY_GSM_USE_GPRS true
#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, Serial);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif
// set GSM PIN, if any
#define GSM_PIN ""
// Your GPRS credentials, if any
const char apn[]  = "internet"; //APN TELKOMSEL
const char gprsUser[] = "";
const char gprsPass[] = "";


const char server[] = "";
const char resource[] = "";
const int  port = 443; //https
TinyGsmClient client(modem);
HttpClient http(client, server, port);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialAT.begin(9600);
  Serial.println("Initializing modem...");
  modem.init();
  Serial.print("modem info: ");
  Serial.println(modem.getModemInfo());
  
  // Unlock your SIM card with a PIN if needed
  if ( GSM_PIN && modem.getSimStatus() != 3 ) {
    modem.simUnlock(GSM_PIN);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
    Serial.print(F("Connecting to "));
    Serial.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      Serial.println(" fail");
      delay(1000);
      return;
    }
    Serial.println(" success");

    if (modem.isGprsConnected()) {
      Serial.println("GPRS connected");
    }
    
}
