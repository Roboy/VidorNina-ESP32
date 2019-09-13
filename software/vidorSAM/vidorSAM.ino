#include <wiring_private.h>
#include "jtag.h"

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

#include "ICEboardVidor.h"

#define PIO_BASE (0x00800000)
#define PIO_IO (0x00800000 + 0)
#define PIO_DIR (0x00800000 + 4)
#define PIO_DIR_IN 0
#define PIO_DIR_OUT 1

bool toggle;
ICEboardVidor *ice;

// the setup function runs once when you press reset or power the board
void setup() {
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

  // Configure other share pins as input too
  pinMode(SIGNAL_IN, INPUT);
  pinMode(MB_INT, INPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  
  while (!Serial) {
    digitalWrite(LED_BUILTIN,toggle);
    toggle=!toggle;
    delay(100);
    ; // wait for serial port to connect. Needed for native USB port only
  }

  ice = new ICEboardVidor();
}

int base = 0;

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN,toggle);
  toggle=!toggle;
  delay(1000);
  for(int motor=0;motor<6;motor++){
    ice->printStatus(base,motor);
  }
}
