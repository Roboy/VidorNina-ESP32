#ifndef ICEboardVidor_h
#define ICEboardVidor_h

#include "AvalonMM.h"

class ICEboardVidor{
public:
  ICEboardVidor(){
    pinMode(7, OUTPUT); // SS   P12[5]
    pinMode(8, OUTPUT); // MOSI P12[2]
    pinMode(9, OUTPUT); // SCK  P12[4]
    pinMode(10, INPUT); // MISO P12[3]
    bool toggle;
    AvalonMM.begin();
    // wait until fpga comes up
    do{
      digitalWrite(LED_BUILTIN,toggle);
      toggle=!toggle;
      delay(200);
      Serial.println("waiting for fpga avalon bridge");
    }while (AvalonMM.read(0, 0x00000000) == 0xffff);
  };

  int32_t readRegister(uint32_t base, uint8_t reg, uint8_t motor){
    uint8_t val[4];
    for(int i=0;i<4;i++){
      val[i] = AvalonMM.read(base,(motor<<8|(reg*4)+i));
    }
    return (int32_t)(val[3]<<24|val[2]<<16|val[1]<<8|val[0]);
  };
};

#endif
