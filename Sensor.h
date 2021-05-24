#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor
{
    public:
    Sensor();
    void displaySensor();
    void changeModeUp();
    void changeModeDown();
    String outputSensor();
   
    String deviceID;
    String loraID;
    String deviceName;
    String deviceType;
    String deviceMode;
    String sensorData;
    String initialised;
    unsigned long lastScanTime;
    
    inline void setdeviceID(String nNewValue) {
          this -> deviceID = nNewValue;}
    inline void setLoraID(String nNewValue) {
          this -> loraID = nNewValue;}
      inline void setLastScanTime(unsigned long nNewValue){
            this-> lastScanTime = nNewValue;}

    inline void setdeviceMode(String nNewValue) {
          this -> deviceMode = nNewValue;}
    inline void setsensorData(String nNewValue) {
          this -> sensorData = nNewValue;}
      inline void setInit(String nNewValue) {
          this -> initialised = nNewValue;}
      inline void setdeviceType(String nNewValue) {
          this -> deviceType = nNewValue;}
};
#endif