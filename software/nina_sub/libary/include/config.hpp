#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#define ARRAY_SIZE 3

#define FPGA_CLK_FRQ      50000000
#define FPGA_CLK_T        (double)( 1. / FPGA_CLK_FRQ)

#define SOUND_SPEED       340. //m/s
#define DISTANCE_FACTOR   FPGA_CLK_T

  #define MASTER 0

#endif
