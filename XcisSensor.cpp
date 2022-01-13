#include "Arduino.h"
#include "XcisSensor.h"
#include <stdio.h>
#include <string.h>


XcisSensor::XcisSensor()
{
  // Constructor
  #ifdef debug
  //Serial.println("XcisSensor::Constructor");
  #endif
  nextSensor = 0;
}
int XcisSensor::getSensorListLength()
{
    int sensorCount = 0;
    for (int i =0; i < numberOfSensors; i++)
    {
        if (sensors[i].initialised == "false")
        {
            return sensorCount;
        }
        sensorCount++;
    }
    return 0;
}
int XcisSensor::scanNextSensor()
{
    //Serial.println("XcisSensor::scanNextSensor");
    if (nextSensor == numberOfSensors)
        nextSensor = 0;
    int sensorToScan = nextSensor;
    if (sensors[sensorToScan].initialised == "false")
    {
        nextSensor = 0;
        return -1;
    }
    /*
    if (sensors[sensorToScan].initialised == "new")
    {
        // Dont scan this since not initialised
        nextSensor = 0; //skip it
        return -1;
    }
    */
    nextSensor++;
    return sensorToScan;
}
String XcisSensor::getSensorLoraID(int scanNumber)
{
    return sensors[scanNumber].loraID;
}
String XcisSensor::getSensorVersion(int scanNumber)
{
    return sensors[scanNumber].deviceVersion;
}
String XcisSensor::getSensorDeviceType(int scanNumber)
{
    return sensors[scanNumber].deviceType;
}
String XcisSensor::getSensorData(int scanNumber)
{
    return sensors[scanNumber].sensorData;
}
String XcisSensor::getSensorData(String loraID)
{
    String sensorData = "NOT FOUND";
    for (int i =0; i< numberOfSensors; i++)
    {
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            #ifdef debug
            //Serial.print("Found sensor Data:" + String(i)+ ":");
            //sensors[i].displaySensor();
            #endif
            //sensorData = sensors[i].loraID + ":" + sensors[i].sensorData;
            sensorData = sensors[i].sensorData;
            break;
        }
    }
    return sensorData;
}
String XcisSensor::getSensorDataBrief_v2(String loraID)
{
    String sensorData = "NOT FOUND";
    String briefData = "NOT FOUND";
    String deviceType = "NULL";
    String initState = "NULL";
    for (int i =0; i< numberOfSensors; i++)
    {
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            //#ifdef debug
            //Serial.print("Found sensor Data:" + String(i)+ ":");
            //sensors[i].displaySensor();
            //#endif
            sensorData = sensors[i].sensorData;
            deviceType = sensors[i].deviceType;
            initState = sensors[i].initialised;
            if (initState == "new")
            {
                briefData = getValue(sensorData, "ID") +  "," + getValue(sensorData,"UID") + "," + deviceType + ",";
                break;
            }
            if (deviceType == "RainGauge")
            {
                briefData = getValue(sensorData, "ID") +  "," + getValue(sensorData,"B") + ","  + getValue(sensorData,"V") + "," + getValue(sensorData,"T") + ",";
                break;
            }
            if (deviceType == "Trough")
            {
                briefData = getValue(sensorData, "ID") + "," + getValue(sensorData,"Value") + ",";
                break;
            }
            if (deviceType == "Fence")
            {
                briefData = getValue(sensorData, "ID") + "," + getValue(sensorData,"Value") + ",";
                break;
            }
            if (deviceType == "Tank")
            {
                briefData = getValue(sensorData, "ID") + "," + getValue(sensorData,"Value") + "," + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "FlowMeter")
            {
                briefData = getValue(sensorData, "ID") +  "," + getValue(sensorData,"B") + ","  + getValue(sensorData,"V") + "," + getValue(sensorData,"T") + ",";
                break;
            }
            if (deviceType == "NULL")
            {
                briefData = getValue(sensorData, "ID") +  ",";
                break;
            }
        }
    }
    return briefData;
}
String XcisSensor::getSensorDataBrief_v3(String loraID)
{
    String sensorData = "NOT FOUND";
    String briefData = "NOT FOUND";
    String deviceType = "NULL";
    String initState = "NULL";
    for (int i =0; i< numberOfSensors; i++)
    {
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            //#ifdef debug
            //Serial.print("Found sensor Data:" + String(i)+ ":");
            //sensors[i].displaySensor();
            //#endif
            sensorData = sensors[i].sensorData;
            deviceType = sensors[i].deviceType;
            initState = sensors[i].initialised;
            if (initState == "new")
            {
                briefData = getValue(sensorData, "ID") +  "," + getValue(sensorData,"UID") + "," + deviceType + ",";
                break;
            }
            if (deviceType == "RainGauge")
            {
                briefData = getValue(sensorData, "ID")  + ","  + getValue(sensorData,"V") + "," + getValue(sensorData,"T") + ","  + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "Trough")
            {
                briefData = getValue(sensorData, "ID") + "," + getValue(sensorData,"V") +  "," + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "Fence")
            {
                briefData = getValue(sensorData, "ID") +  "," + getValue(sensorData,"V") +  "," + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "Tank")
            {
                briefData = getValue(sensorData, "ID") + "," + getValue(sensorData,"V") + "," + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "FlowMeter")
            {
                briefData = getValue(sensorData, "ID") +  ","  + getValue(sensorData,"V") + "," + getValue(sensorData,"T") + ","  + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "Bore")
            {
                briefData = getValue(sensorData, "ID") +  ","  + getValue(sensorData,"V") + "," + getValue(sensorData,"P") + "," + getValue(sensorData,"T") + "," + getValue(sensorData,"S") + ","  + getValue(sensorData,"B") + ",";
                break;
            }
            if (deviceType == "NULL")
            {
                briefData = getValue(sensorData, "ID") +  ",";
                break;
            }
        }
    }
    return briefData;
}
int XcisSensor::getSensorScanNumber(String loraID)
{
    int counter = 0;
    for (int i =0; i< numberOfSensors; i++)
    {
        counter = i;
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            #ifdef debug
            //Serial.print("Found sensor:" + String(i)+ ":");
            #endif
            //sensors[i].displaySensor();
            break;
        }
        
    }
    return counter;
}
String XcisSensor::listSensors(bool serial)
{
    //Serial.println("XcisSensor::listSensors");
    String output;
    for (int i =0; i< numberOfSensors; i++)
    {
        if (serial == false)
        {
            Serial.print("ScanNumber:");
            Serial.print(i);
            Serial.print(",");
            sensors[i].displaySensor();
        }
        else
        {
            output += "Sensor,";
            output += String(i);
            output +=  ",";
            output += sensors[i].outputSensor();
            output +="\r\n";
        }
        
    }
    return output;
}
void XcisSensor::checkSensorsOnline()
{
    long timeCheck = 0;
    //Serial.println("XcisSensor::checkSensorsOnline");
    for (int i =0; i< numberOfSensors; i++)
    {
        sensors[i].displaySensor();
        timeCheck = millis() - 400000;
        if (timeCheck < 0 )
            return;
        //Serial.println(millis());
        //Serial.println(sensors[i].lastScanTime);
       // Serial.println(timeCheck);
        if (sensors[i].lastScanTime < timeCheck)
        {
            //Serial.println("Sensor offline");
            setDeviceMode(i, "OF", millis());
            sensors[i].displaySensor();

        }
    }
}
void XcisSensor::displaySensor(int scanNumber)
{
    sensors[scanNumber].displaySensor();
}
void XcisSensor::streamSensor(int scanNumber)
{
    sensors[scanNumber].outputSensor();
}
void XcisSensor::addSensor(int scanNumber, String loraID, String deviceType, String state)
{
    sensors[scanNumber].setLoraID(loraID);
    sensors[scanNumber].setdeviceType(deviceType);
    sensors[scanNumber].setdeviceMode("UNKNOWN");
    sensors[scanNumber].setsensorData("NODATA,");
    sensors[scanNumber].setInit(state);
}
void XcisSensor::addSensor(int scanNumber, String loraID, String deviceType, String deviceVersion, String state)
{
    sensors[scanNumber].setLoraID(loraID);
    sensors[scanNumber].setdeviceType(deviceType);
    sensors[scanNumber].setdeviceVersion(deviceVersion);
    sensors[scanNumber].setdeviceMode("UNKNOWN");
    sensors[scanNumber].setsensorData("NODATA,");
    sensors[scanNumber].setInit(state);
}
void XcisSensor::deleteSensor()
{
    //Serial.println("XcisSensor::deleteSensor");

}
void XcisSensor::setSensorData(int scanNumber, String data)
{
    //Serial.println("XcisSensor::setSensorData");
    sensors[scanNumber].setsensorData(data);
}
void XcisSensor::setDeviceMode(int scanNumber, String state, unsigned long timeStamp)
{
    //Serial.println("XcisSensor::setdeviceMode");
    sensors[scanNumber].setdeviceMode(state);
    sensors[scanNumber].setLastScanTime(timeStamp);
}
String XcisSensor::getDeviceMode(String loraID)
{
    //Serial.println("XcisSensor::getDeviceMode");
    return sensors[getSensorScanNumber(loraID)].deviceMode;
}
String XcisSensor::getDeviceInitState(String loraID)
{
    //Serial.println("XcisSensor::getDeviceInitState");
    return sensors[getSensorScanNumber(loraID)].initialised;
;
}
String XcisSensor::getValue(String message,String name)
{
     // Returns first token 
    char *tk = strtok((char*)message.c_str(), ",");
    String token;
    String value;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (tk != NULL)
    {
        //Serial.println(tk);
        token = tk;
        int found = token.indexOf(name);
       
        if (found!=-1)
        {
            int nameLength = name.length();
            // allow for '='sign
            nameLength++;
            value = token.substring(nameLength,token.length());
            //Serial.print("Value is :");
            //Serial.println(value);
            return value;
        }
        tk = strtok(NULL, ",");
    }
    return "NULL";
}
