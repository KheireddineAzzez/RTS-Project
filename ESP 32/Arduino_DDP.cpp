

#include "Arduino_DDP.h"




void onMessageCallback(WebsocketsMessage message) {
 

}


void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}
ArduinoDDP::ArduinoDDP(String displayMsg) {
  _msg = displayMsg;
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);
}


void ArduinoDDP::hpom() {
  Serial.begin(9600);
  
    Serial.println("TestLib constructor instantiated (created) successfully.");
 
}
long ArduinoDDP::getRandomNumber() {
  return 55;
}

bool ArduinoDDP::setup(String host, String path,int port){
_host=host;
 bool connected = false;

if(client.connect("ws://192.168.142.238:3005/websocket")){
    Serial.println("Connected to server");

    connected = true;

} else{

  Serial.println("connection to server failed");
  connected=false;

};
return connected;

}

bool ArduinoDDP::handshake(){

return false;
}

// Arduino Connection
bool ArduinoDDP::connect(){
DynamicJsonDocument doc(1024);
String request;
doc["msg"]="connect";
doc["version"]="1";
JsonArray support = doc.createNestedArray("support");
support.add("1");
serializeJson(doc,request);
Serial.println(request);
client.send(request); 
doc.clear();
return true;

}

void ArduinoDDP::sub(String SubName){
  String request;
  DynamicJsonDocument doc(1024);
  doc["msg"] = "sub";
  doc["id"] = "1";
  doc["name"] = SubName;
  serializeJson(doc,request);

  client.send(request); 
  doc.clear();


}
void ArduinoDDP::ping(String id ){
  String request;
  DynamicJsonDocument doc(1024);
    doc["msg"] = "ping";
    doc["id"] = id;

  serializeJson(doc,request);

  client.send(request);
  doc.clear();
}

void ArduinoDDP::method_sensor(String Method_name, Interface_Uno_Ultra_reader Uno_Reader){
    String request;
  DynamicJsonDocument doc(1024);
  doc["msg"] = "method";
  doc["method"] = Method_name;
  doc["id"] = "1";
  
  JsonArray  params = doc.createNestedArray("params");
  params.add(Uno_Reader.Distance);
    params.add(Uno_Reader.Duration);

  serializeJson(doc,request);
  

  client.send(request);
}

void ArduinoDDP::method_sensor_tempurature(String Method_name, Interface_Uno_Temperature Uno_Reader){
    String request;
  DynamicJsonDocument doc(1024);
  doc["msg"] = "method";
  doc["method"] = Method_name;
  doc["id"] = "1";
  
  JsonArray  params = doc.createNestedArray("params");
  params.add(Uno_Reader.tempurature);
  params.add(Uno_Reader.humidity);
  params.add(Uno_Reader.type);

  serializeJson(doc,request);
  

  client.send(request);
}




