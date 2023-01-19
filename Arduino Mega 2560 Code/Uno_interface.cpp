#include "HardwareSerial.h"
#include "C:\Users\kheir\Documents\Arduino\sketch_nov5b\Uno_interface.h"
  #include "Arduino.h"



String Interface_Uno_Ultra_Sender::Send_Data_Ultra(){
      DynamicJsonDocument doc(1024);

  String data;
  doc["Duration"]=Duration;
  doc["Distance"]=Distance;
  doc["Type"]=1;

  serializeJson(doc,data);
  Serial.println(data);
  doc.clear();
  return data;


}

void Interface_Uno_Ultra_reader::Read_Data_Ultra(String input){
    DynamicJsonDocument doc(1024);

  DeserializationError err= deserializeJson(doc,input);
  if (err){

    Serial.println("Error In Dis");
        Serial.println(err.c_str());

    return ;
  }
  Duration=doc["Duration"];
  Distance=doc["Distance"];
  type=  doc["Type"];

  doc.clear();

}

////////////TEMP
String  Interface_Uno_Temperature::Send_data_tempurature(String temp, String hum){
  DynamicJsonDocument doc(1024);
  String data;
  doc["Temperature"]=temp;
  doc["Humidity"]=hum;
  doc["Type"]=2;
  serializeJson(doc,data);
  Serial.println(data);
  doc.clear();
  return data;
}

void Interface_Uno_Temperature::Read_data_tempurature(String Input){
      DynamicJsonDocument doc(1024);
   DeserializationError err= deserializeJson(doc,Input);
  if (err){

    Serial.println("Error In Dis");
        Serial.println(err.c_str());

    return ;
  }

  tempurature= doc["Temperature"].as<String>()  ;
  humidity = doc["Humidity"].as<String>();
  type=  doc["Type"];


  doc.clear();
}