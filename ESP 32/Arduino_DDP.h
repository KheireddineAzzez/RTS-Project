#ifndef tl
#define tl

#if (ARDUINO >=100)
  #include "Arduino.h"
  #include <ArduinoJson.h>
  #include <ArduinoWebsockets.h>
  #include <Uno_interface.h>

  using namespace websockets;

#else
  #include "WProgram.h"
#endif

class ArduinoDDP  {

  public:
    // Constructor 
    ArduinoDDP(String displayMsg);

    // Methods
    void hpom();
    long getRandomNumber();
    bool setup(String host, String path,int port);
    bool handshake();//Establish Handshake with the server
    void waitFor();
    bool connect(); // Connect to websocket server 
    void listen();// listen to the news
    /** Heartbeats : I am still exist*/
    void ping(String id = "");
    void pong(String id = "");
    /*Websocket: Cient to Server*/
    void sub(String SubName);
    void unsub();
    /*Websocket:server to client*/
    void nosub();
    void added();
    void changed();
    void removed();
    void ready();
//Methods: Client
  void method_sensor(String Method_name,Interface_Uno_Ultra_reader Uno_Reader);
  void method_sensor_tempurature(String Method_name,Interface_Uno_Temperature Uno_Reader);

  void result();
 /* Sub *******************************************************************/
    bool subsReady();
    WebsocketsClient client;
    String request;


  private:
    String _msg;
    String _host;
    String _path;
    int _port;
    String _session;
    bool _connected;
    int _pause = 1000;
    int _timer = 1;   
    
};
#endif