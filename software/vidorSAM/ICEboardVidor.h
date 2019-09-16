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
    int32_t val[0x14];
    for(int i=0;i<0x14;i++){
      val[i] = readRegister(base, i);
    }
    ardprintf("motor %d enc0_pos %d enc1_pos %d enc0_vel %d enc1_vel %d suf %d cm %d Kp: %d Ki: %d Kd: %d pwmlim %d intlim %d deadband %d setpoint %d error_code %d\n",
      val[REG::motor],
      val[REG::enc0_pos],val[REG::enc1_pos],
      val[REG::enc0_vel],val[REG::enc1_vel],
      //val[REG::cur_ph1],val[REG::cur_ph2],val[REG::cur_ph3],
      val[REG::status_update_frequency],
      val[REG::control_mode],
      val[REG::Kp],val[REG::Ki],val[REG::Kd],
      val[REG::pwmlim],val[REG::intlim],val[REG::deadband],val[REG::setpoint],val[REG::error_code]); //cur_ph1 %d cur_ph2 %d cur_ph3 
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
    motor = 0x0,
    Kp = 0x1,
    Ki = 0x2,
    Kd = 0x3,
    enc0_pos = 0x4,
    enc1_pos = 0x5,
    enc0_vel = 0x6,
    enc1_vel = 0x7,
    pwmlim = 0x8,
    intlim = 0x9,
    deadband = 0xA,
    control_mode = 0xB,
    setpoint = 0xC,
    error_code = 0xD,
    status_update_frequency = 0x11,
    cur_ph1 = 0x12,
    cur_ph2 = 0x13,
    cur_ph3 = 0x14
  };
};

#endif
