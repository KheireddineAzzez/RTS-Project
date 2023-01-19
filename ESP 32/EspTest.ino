
#include <esp32cam.h>

#include <WebServer.h>


#define RXD2 33
#define TXD2 4

#include <WiFi.h>
#include "Arduino_DDP.h"

 Interface_Uno_Ultra_reader Uno_Reader;
 Interface_Uno_Temperature Uno_temp_reader;
WebServer server(80);

const char* ssid = "Azzez";
const char* password = "123456789";



ArduinoDDP testlib("dsd");



void setup() {


  // WIFI COnfig
    Serial.begin(9600);
    Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);
    //Serial2.setTimeout(500);
    WiFi.begin(ssid, password);
     for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
     Serial.println("try connecting");
      delay(1000);
      }
      testlib.setup("ws://localhost:3005/websocket", "dasdsad",  222);
      testlib.connect();
      testlib.sub("Welcome");
      testlib.ping("15996");
    // End wifi config
    // 
}
int read_Type(String input ){
        DynamicJsonDocument doc(1024);
DeserializationError err= deserializeJson(doc,input);
  if (err){

    Serial.println("Error In Dis");
        Serial.println(err.c_str());

    return 0;
  }
  int type= doc["Type"];
  doc.clear();
   return  type ;

}
void loop() { 
  
  String Data_From_ARduino_Uno =  Serial2.readStringUntil('\r');
  if(!Data_From_ARduino_Uno.isEmpty() &&  Data_From_ARduino_Uno!=NULL){
    Serial.println("Traing");
   if(read_Type(Data_From_ARduino_Uno)==1){
    Uno_Reader.Read_Data_Ultra(Data_From_ARduino_Uno);
    
   Serial.println(Data_From_ARduino_Uno);
   testlib.method_sensor("Distance_Ultra_sound", Uno_Reader);
   
   }

   if(read_Type(Data_From_ARduino_Uno)==2){
   Uno_temp_reader.Read_data_tempurature(Data_From_ARduino_Uno);
   testlib.method_sensor_tempurature("Tempurature", Uno_temp_reader);
   }

   
   }

  testlib.ping("kk15996");
  testlib.client.ping();
  delay(100);
  testlib.client.poll();

}