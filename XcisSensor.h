#ifndef XcisSensor_h
#define XcisSensor_h

#include "Arduino.h"
#include "Sensor.h"

#define numberOfSensors 20

class XcisSensor
{
    public:
    XcisSensor();
    String listSensors(bool serial);
    void displaySensor(int scanNumber);
    void streamSensor(int scanNumber);
    void addSensor(int scanNumber, String loraID, String deviceType);
    void deleteSensor();
    void setSensorData(int scanNumber, String data);
    String getSensorData(int scanNumber);
    String getSensorData(String loraID);
    void setDeviceMode(int scanNumber, String state, unsigned long timeStamp);
    String getDeviceMode(String loraID);
    String getSensorLoraID(int scanNumber);
    int getSensorScanNumber(String loraID);
    int scanNextSensor();
    void checkSensorsOnline();
    int getSensorListLength();

    int nextSensor;
    private:
    Sensor sensors[numberOfSensors];
};


#endif