#include <DHT.h>

#include<SoftwareSerial.h>
#include "Uno_interface.h"
//Temp DEFINE
#define DHTPIN 22
#define DHTTYPE DHT11  

// END Temp DEFINE

Interface_Uno_Ultra_Sender Sender_Interface;
Interface_Uno_Ultra_reader Reader_Interface;

Interface_Uno_Temperature Reader_interface_Temperature;

const int trigPin=13;
const int echoPin=12;
long duration;
int distance;
int dasdsd;


SoftwareSerial myserail(0,1); // create local Serial: Arduino Uno use the port 1 as Tx and 0 as  Rx 
SoftwareSerial myserial2(15,14);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  myserail.begin(9600);
  myserial2.begin(9600);
  Serial.begin(9600);
  dht.begin();


}
void Read_Data_Temp(){
  float temperature, humidity;

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  delay(2000); 


 char tempF[6]; 
 char humF[6];
 dtostrf(temperature, 5, 1, tempF);
 dtostrf(humidity, 2, 0, humF);

 Serial.println("T:"); 
 Serial.println(tempF);
 Serial.println((char)223);
 Serial.println("C ");
 Serial.println("H: ");
 Serial.println(humF);
 Serial.println("%");


String sent_Tempurature= Reader_interface_Temperature.Send_data_tempurature(tempF, humF);
myserail.println(sent_Tempurature);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);
  distance= duration * 0.034/2;

    
    Sender_Interface.Distance=distance;
    Sender_Interface.Duration=duration;
    
    myserail.println(Sender_Interface.Send_Data_Ultra());
     
    Reader_Interface.Read_Data_Ultra(Sender_Interface.Send_Data_Ultra());
    

    Read_Data_Temp();
    delay(100); // Stop 1 s
}