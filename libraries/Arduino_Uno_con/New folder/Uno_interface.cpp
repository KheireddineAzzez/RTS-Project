#include "HardwareSerial.h"
#include "C:\Users\kheir\Documents\Arduino\sketch_nov5b\Uno_interface.h"



String Interface_Uno_Ultra_Sender::Send_Data_Ultra(){
      DynamicJsonDocument doc(1024);

  String data;
  doc["Duration"]=Duration;
  doc["Distance"]=Distance;
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

  doc.clear();

}