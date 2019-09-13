#include <wiring_private.h>
#include "jtag.h"
#include <SPI.h>

#define TDI                               12
#define TDO                               15
#define TCK                               13
#define TMS                               14
#define MB_INT                            28
#define MB_INT_PIN                        31
#define SIGNAL_IN 33 //B2 N2

#define no_data    0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, \
          0x00, 0x00, 0x00, 0x00  \

#define NO_BOOTLOADER   no_data
#define NO_APP        no_data
#define NO_USER_DATA    no_data

__attribute__ ((used, section(".fpga_bitstream_signature")))
const unsigned char signatures[4096] = {
  //#include "signature.ttf"
  NO_BOOTLOADER,

  0x00, 0x00, 0x08, 0x00,
  0xA9, 0x6F, 0x1F, 0x00,   // Don't care.
  0x20, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x65, 0x73, 0x2d, 0x65, 0x6d, 0x62, 0x61, 0x72, 0x71, 0x75, 0x65, 0x73, 0x2e, 0x66, 0x72, 0x20, 0x00, 0x00, 0xff, 0xf0, 0x0f,
  0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00,   // Force

  NO_USER_DATA,
};
__attribute__ ((used, section(".fpga_bitstream")))
const unsigned char bitstream[] = {
  #include "app.h"
};

const int transmissionPin = 6;
const int slaveSelectPin = 7;
const int servo_pin = 11;
const int dc_direction = 12;
const int dc_enable = 13;
const int thumb_lock = 14;

union COM_FRAME_READ{
  struct{
    int32_t pos[4];
    int16_t vel[4];
    int16_t dis[4];
    int16_t cur[4];
    int16_t pwmRef[4];
  }values;
  uint8_t data[48];
}com_frame_read;

union COM_FRAME_WRITE{
  struct{
    int16_t Kp[4];
    int16_t Ki[4];
    int16_t Kd[4];
    int32_t sp[4];
    int16_t outputPosMax[4];
    int16_t outputNegMax[4];
    int16_t IntegralPosMax[4];
    int16_t IntegralNegMax[4];
    int16_t deadBand[4];
    uint8_t conf;
    uint8_t control_mode;
    uint8_t outputDivider[4];
  }values = {.Kp = {1,1,1,1}, .Ki = {0,0,0,0}, .Kd = {0,0,0,0}, .sp = {0,0,0,0}, .outputPosMax = {500,500,500,500}, .outputNegMax = {-500,-500,-500,-500},
    .IntegralPosMax = {0,0,0,0}, .IntegralNegMax = {0,0,0,0}, .deadBand = {0,0,0,0}, .conf =  0x40,  .control_mode=0, .outputDivider  = {0,0,0,0}
  };
  uint8_t data[86];
}com_frame_write;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("ready");
  
  int ret;
  uint32_t ptr[1];

  pinPeripheral(30, PIO_AC_CLK);
  clockout(0, 1);
  delay(1000);  
  //Init Jtag Port
  ret = jtagInit();
  mbPinSet();

  // Load FPGA user configuration
  ptr[0] = 0 | 3;
  mbEveSend(ptr, 1);

  // Give it delay
  delay(1000);

  // Configure onboard LED Pin as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Disable all JTAG Pins (usefull for USB BLASTER connection)
  pinMode(TDO, INPUT);
  pinMode(TMS, INPUT);
  pinMode(TDI, INPUT);
  pinMode(TCK, INPUT);

  // Configure other share pins as input too
  pinMode(SIGNAL_IN, INPUT);
  pinMode(MB_INT, INPUT);

  // Configure onboard LED Pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  SPI.begin();
//  pinMode (slaveSelectPin, OUTPUT);
//  pinMode (transmissionPin, OUTPUT);  
//  pinMode (servo_pin, OUTPUT);
//  pinMode (dc_direction, OUTPUT);  
//  pinMode (dc_enable, OUTPUT);  
//  pinMode (thumb_lock, OUTPUT);  
}

bool toggle;

void loop() {
  Serial.println("hello");
  delay(500);
//  digitalWrite(transmissionPin, LOW);
//  for(int i=0;i<86;i++){
//    digitalWrite(slaveSelectPin, LOW);
//    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
//    if(i<48)
//      com_frame_read.data[i] = SPI.transfer(com_frame_write.data[i]);
//    SPI.endTransaction();
//    digitalWrite(slaveSelectPin, HIGH);
//  }
//  digitalWrite(transmissionPin, HIGH);
//
//  digitalWrite(servo_pin, toggle);
//  digitalWrite(dc_direction, toggle);
//  digitalWrite(dc_enable, toggle);
//  digitalWrite(thumb_lock, toggle);
//
//  toggle= !toggle;
}
