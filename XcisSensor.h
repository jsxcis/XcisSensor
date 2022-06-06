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
    void addSensor(int scanNumber, String loraID, String deviceType, String state);
    void addSensor(int scanNumber, String loraID, String deviceType, String deviceVersion, String state);
    void deleteSensor();
    void setSensorData(int scanNumber, String data);
    String getSensorData(int scanNumber);
    String getSensorData(String loraID);
    String getSensorDataBrief_v2(String loraID);
    String getSensorDataBrief_v3(String loraID);
    void setDeviceMode(int scanNumber, String state, unsigned long timeStamp);
    String getDeviceMode(String loraID);
    String getDeviceInitState(String loraID);
    String getSensorLoraID(int scanNumber);
    int getSensorScanNumber(String loraID);
    int scanNextSensor();
    void checkSensorsOnline();
    int getSensorListLength();
    String getSensorVersion(int scanNumber);
    String getSensorDeviceType(int scanNumber);

    inline int getNextSensorToScan() { return nextSensor;};

    int nextSensor;
    private:
    Sensor sensors[numberOfSensors];
    String getValue(String message,String name);
};


#endif