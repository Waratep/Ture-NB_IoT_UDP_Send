#include <Arduino.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)      // Arduino UNO
    #include <AltSoftSerial.h>
    AltSoftSerial bc95serial;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)   // Arduino MEGA2560
    #define bc95serial Serial1
#endif

#include "BC95Udp.h"

BC95UDP client;

char payload[32];

void setup() {

    client.begin(7000);
    client.beginPacket("35.230.122.14",7000);
    
    bc95serial.begin(9600);
    BC95.begin(bc95serial);
    BC95.reset();
    
    Serial.begin(9600);
    Serial.println(F("Microgear Arduino NB-IoT Start!"));
    Serial.print(F("IMEI: "));
    Serial.println(BC95.getIMEI());
    Serial.print(F("IMSI: "));
    Serial.println(BC95.getIMSI());

    Serial.print(F("Attach Network..."));
    while (!BC95.attachNetwork()) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(F("\nNB-IOT attached!"));
    Serial.print(F("RSSI: "));
    Serial.println(BC95.getSignalStrength());
    Serial.print(F("IPAddress: "));
    Serial.println(BC95.getIPAddress());
    client.write("Connected",8);
}

void loop() {
    if(client.available()){
       client.write("Hello",4);
    }
    Serial.print(F("Sent Signal Strength: "));
    Serial.println(BC95.getSignalStrength());

    delay(1000);
}
