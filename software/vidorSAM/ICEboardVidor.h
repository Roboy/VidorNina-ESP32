#ifndef ICEboardVidor_h
#define ICEboardVidor_h

#include "AvalonMM.h"
#include "ardprintf.h"

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
  void printStatus(int base, int motor){
    writeRegister(base,0,motor);
    int32_t val[12];
    for(int i=0;i<12;i++){
      val[i] = readRegister(base, i);
    }
    ardprintf("motor %d Kp: %d Ki: %d Kd: %d pos %d vel %d dis %d cur %d pwmlim %d intlim %d deadband %d control_mode %d setpoint\n",
      val[REG::motor],val[REG::Kp],val[REG::Ki],val[REG::Kd],val[REG::pos],val[REG::vel],val[REG::dis],val[REG::cur],
      val[REG::pwmlim],val[REG::intlim],val[REG::deadband],val[REG::control_mode],val[REG::setpoint]);
  };
  int32_t writeRegister(uint32_t base, uint8_t reg, int32_t data){
    for(int i=0;i<4;i++){
      AvalonMM.write(base,(reg*4)+i, ((data>>(8*i))&0xFF));
    }
  };
  int32_t readRegister(uint32_t base, uint8_t reg){
    uint8_t val[4];
    for(int i=0;i<4;i++){
      val[i] = AvalonMM.read(base,(reg*4)+i);
    }
    return (int32_t)(val[3]<<24|val[2]<<16|val[1]<<8|val[0]);
  };
  enum REG{
    motor = 0,
    Kp,
    Ki,
    Kd,
    pos,
    vel,
    dis,
    cur,
    pwmlim,
    intlim,
    deadband,
    control_mode,
    setpoint
  };
};

#endif
