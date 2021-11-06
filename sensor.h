#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
String tempSensor(){
  bme.begin(0x76);
  float sensor=0;
  for(int i=0; i<10;i++){
    sensor +=  bme.readTemperature();
  }
   return String(sensor = sensor/10);
}

String humSensor(){
  bme.begin(0x76);
  float sensor=0;
  for(int i=0; i<10;i++){
    sensor +=  bme.readHumidity();
  }
   return String(sensor = sensor/10);
}

String altSensor(){
  bme.begin(0x76);
  float sensor=0;
  for(int i=0; i<10;i++){
    sensor += bme.readAltitude(SEALEVELPRESSURE_HPA);
  }
   return String(sensor = sensor/10);
}
void bmesetup(){
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
    // Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
    // Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    // Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    // Serial.print("        ID of 0x60 represents a BME 280.\n");
    // Serial.print("        ID of 0x61 represents a BME 680.\n");
//    while (true) delay(10);
  }
}
String soilSensor(int pin){
  float sensor=0;
  for(int i=0; i<100;i++){
    sensor += analogRead(pin);
    delay(20);
  }
  sensor = sensor/100;
  sensor = analogRead(pin);
  
  return String(sensor);
}
String battVolt(int pin){
  float sensor=0;
  for(int i=0; i<100;i++){
    sensor += analogRead(pin);
    delay(20);
  }
  sensor = sensor/100;
  sensor = analogRead(pin);
  return String((sensor+163.11)/220.96);
//return sensor;
}

String pvVolt(int pin){
  float sensor=0;
  for(int i=0; i<100;i++){
    sensor += analogRead(pin);
    delay(20);
  }
  sensor = sensor/100;
//  sensor = analogRead(pin);
  return String((sensor+45.639)/146.36);
//return sensor;
}


// String GPSlocation(){
//   GPSpin.begin(9600);
//   while (GPSpin.available()>0)
//     if (gps.encode(GPSpin.read()))
//     if(gps.location.isValid()){
//       Serial.print(gps.location.lat(), 6);
//     Serial.print(F(","));
//     Serial.print(gps.location.lng(), 6);
//     return (String(gps.location.lat()) + "," + String(gps.location.lng()));
//     }
//     else{
//       return "0,0";
//     }
//     GPSpin.end();
// }