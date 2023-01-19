

#if (ARDUINO >=100)
  #include "Arduino.h"

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#else
  #include "WProgram.h"
#endif


class Interface_Uno_Ultra_Sender{
public:

long Duration;
int  Distance;
int dasdsa;
String Send_Data_Ultra();


};

class Interface_Uno_Ultra_reader{
public:
long Duration;
int  Distance;
void  Read_Data_Ultra(String input);

};

