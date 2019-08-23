#ifndef DE0_H_
#define DE0_H_

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "soc_system.h"
#include "SPIbus.hpp"
#include "msg.hpp"

#define BURSTCYCLE_OFFSET 2500


//#define ALT_LWFPGASLVS_OFST 0xFF200000
#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#define PIEZO_ENABLE_BASE         (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_ENABLE_REG_OFST)
#define PIEZO_PERIOD_BASE         (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_PERIOD_REG_OFST)
#define PIEZO_PHASE_A_COUNT_BASE  (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_PHASE_A_COUNT_REG_OFST)
#define PIEZO_PHASE_B_COUNT_BASE  (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_PHASE_B_COUNT_REG_OFST)
#define PIEZO_PHASE_A_BASE        (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_PHASE_A_REG_OFST)
#define PIEZO_PHASE_B_BASE        (PIEZO_CONTROLLER_0_BASE + PIEZO_CONTROLLER_0_PHASE_B_REG_OFST)
#define PIEZO_COUNT               88
#define PIEZO_FREQ                40000
#define PIEZO_PERIOD_CLK          (PIEZO_CONTROLLER_0_FREQ / PIEZO_FREQ)

typedef enum {REGISTER_A, REGISTER_B} phase_register;

class addr_base{
  public:
    addr_base();
    uint32_t rtc_base_addr;
    uint32_t piezo_base_addr;
    uint32_t led_base_addr;
    uint32_t key_base;
    uint32_t ptp_base;
    uint32_t sw_base;

    //void virtual_base;

    int fd;
};


//------ AVALON BRIDGE ----
class hardware_interface{
  public:
    uint8_t device_id = 0;
    hardware_interface(SPI *spi_,msg_gen *transmit_);
    SPI *spi;
    msg_gen *transmit;

    addr_base *addr;// = nullptr;

    uint32_t US_start_time;

    void IOWR(uint32_t base,uint32_t reg, uint32_t data);
    uint32_t IORD(uint32_t base,uint32_t reg);

    //--SET---
    void master_reset();
    void start_time_sync(bool is_master_mode_);
    void start_US_out();
    void stop_US_out();
    void piezo_burst_out();
    void piezo_set_burst_cycles(uint32_t cycle_amont);
    void allow_input_trigger();
    void set_time(uint32_t time_data);

    //--GET--
    uint32_t getID();
    uint32_t time_sync_data();
    bool waitFlag_timeSync();
    bool rdy_to_read();
    uint32_t read_time(void);
    uint32_t read_trigger_time(void);
    uint32_t read_trigger_time2(void);


    //--BI--

  //private:



};

/*
hw::hw(){
  //addr_base addr_base;

  piezo_ctl piezo_ctl(addr_base.virtual_base);
  hw hw(addr_base.rtc_base_addr);
  fpga_mode modef(addr_base.sw_base, &hw);
  time_sync ptp(addr_base.ptp_base, modef.id);  //todo
}*/

#endif
