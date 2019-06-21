/* =========================================================================
SPIbus library is placed under the MIT License
Copyright 2017 Natanael Josue Rabello. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
 ========================================================================= */

 #include "SPIbus.hpp"
 #include <stdio.h>
 #include <stdint.h>
 #include "driver/spi_common.h"
 #include "driver/spi_master.h"
 #include "esp_log.h"
 #include "esp_err.h"
 #include "sdkconfig.h"


#if defined   CONFIG_SPIBUS_LOG_RW_LEVEL_INFO
#define SPIBUS_LOG_RW(format, ... ) ESP_LOGI(TAG, format, ##__VA_ARGS__)
#elif defined CONFIG_SPIBUS_LOG_RW_LEVEL_DEBUG
#define SPIBUS_LOG_RW(format, ... ) ESP_LOGD(TAG, format, ##__VA_ARGS__)
#elif defined CONFIG_SPIBUS_LOG_RW_LEVEL_VERBOSE
#define SPIBUS_LOG_RW(format, ... ) ESP_LOGV(TAG, format, ##__VA_ARGS__)
#endif
#define SPIBUS_LOGE(format, ... )   ESP_LOGE(TAG, format, ##__VA_ARGS__)


static const char* TAG __attribute__((unused)) = "SPIbus";

/*******************************************************************************
 * OBJECTS
 ******************************************************************************/
SPI hspi = SPI(HSPI_HOST);
SPI vspi = SPI(VSPI_HOST);


/*******************************************************************************
 * SETUP
 ******************************************************************************/
SPI::SPI(spi_host_device_t host) : host(host) {
}

SPI::~SPI() {
    close();
}

uint32_t SPI::fpga_read(uint32_t base, uint32_t inc_addr){
  unsigned char read_data[BUFFER_LENGTH];
  uint32_t ret_buf = 0;
  bool trans_flag = 0;
  uint32_t cnt2 = 0;

  uint8_t ret_read = transaction_channel_read((inc_addr<<10)+base,4, &read_data[0],INCREMENT_ADDRESS);

  for(uint32_t cnt= 0; cnt < 40;cnt++){
    if (read_data[cnt] != SPI_IDLE ){
      if (read_data[cnt] == CHANNEL ) {
        cnt+=2;
        if(read_data[cnt] == SOP){
          trans_flag = 1;
          cnt++;
        }
      }
      if(trans_flag == 1){
        //read_data[cnt]
        if(read_data[cnt] == EOP){
          trans_flag = 0;
          cnt+=2;
          read_data[cnt2] = read_data[cnt-1];
          cnt2++;
        }
        read_data[cnt2] = read_data[cnt];
        cnt2++;
      }
    }
  }
  for(uint32_t cnt= 0; cnt < 4; cnt++){
    if(read_data[cnt] == BYTESESCCHAR){
      read_data[cnt] = xor_20(read_data[cnt+1]);
      read_data[cnt+1] = 0;
      cnt++;
    }else if(read_data[cnt] == BYTESIDLECHAR){
      read_data[cnt] = 0;
    }
  }
  //printf("count:%d...out_data: %d,%d,%d,%d\n",cnt2,read_data[0],read_data[1],read_data[2],read_data[3]);
  //printf("write length: %d --- readlength: %d\n",write_length,read_length);

  ret_buf = read_data[0] | (read_data[1]<<8)| (read_data[2]<<16)| (read_data[3]<<24);
  //read_data[cnt]
  //printf("%d,",ret_buf);
  //printf("\n");
  return ret_buf;
}
void SPI::fpga_write(uint32_t base, uint32_t inc_addr, uint32_t data){
  unsigned char data_buffer[BUFFER_LENGTH];
  data_buffer[0] = uint8_t(data & 0xff);
  data_buffer[1] = uint8_t((data>>8) & 0xff);
  data_buffer[2] = uint8_t((data>>16)  & 0xff);
  data_buffer[3] = uint8_t((data>>24)  & 0xff);

  transaction_channel_write(base+(inc_addr<<10),4, &data_buffer[0],INCREMENT_ADDRESS);

}

esp_err_t SPI::begin(int mosi_io_num, int miso_io_num, int sclk_io_num, int max_transfer_sz) {
    spi_bus_config_t config;
    config.mosi_io_num = mosi_io_num;
    config.miso_io_num = miso_io_num;
    config.sclk_io_num = sclk_io_num;
    config.quadwp_io_num = -1;  // -1 not used
    config.quadhd_io_num = -1;  // -1 not used
    config.max_transfer_sz = max_transfer_sz;
    return spi_bus_initialize(host, &config, 0);  // 0 DMA not used
}

esp_err_t SPI::close() {
    return spi_bus_free(host);
}

esp_err_t SPI::addDevice(uint8_t mode, uint32_t clock_speed_hz, int cs_io_num, spi_device_handle_t *handle) {
    spi_device_interface_config_t dev_config;
    dev_config.command_bits = 0;
    dev_config.address_bits = 0;
    dev_config.dummy_bits = 0;
    dev_config.mode = mode;
    dev_config.duty_cycle_pos = 128;  // default 128 = 50%/50% duty
    dev_config.cs_ena_pretrans = 6;  // 0 not used
    dev_config.cs_ena_posttrans = 0;  // 0 not used
    dev_config.clock_speed_hz = clock_speed_hz;
    dev_config.spics_io_num = cs_io_num;
    dev_config.flags = 0;  // 0 not used
    dev_config.queue_size = 1;
    dev_config.pre_cb = NULL;
    dev_config.post_cb = NULL;
    return spi_bus_add_device(host, &dev_config, handle);
}

esp_err_t SPI::addDevice(spi_device_interface_config_t *dev_config, spi_device_handle_t *handle) {
    dev_config->address_bits = 8;  // must be set, SPIbus uses this 8-bits to send the regAddr
    return spi_bus_add_device(host, dev_config, handle);
}

esp_err_t SPI::removeDevice(spi_device_handle_t handle) {
    return spi_bus_remove_device(handle);
}


/*******************************************************************************
 * WRITING
 ******************************************************************************/
esp_err_t SPI::writeBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t buffer;
    esp_err_t err = readByte(handle, regAddr, &buffer);
    if (err) return err;
    buffer = data ? (buffer | (1 << bitNum)) : (buffer & ~(1 << bitNum));
    return writeByte(handle, regAddr, buffer);
}

esp_err_t SPI::writeBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t buffer;
    esp_err_t err = readByte(handle, regAddr, &buffer);
    if (err) return err;
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1);
    data &= mask;
    buffer &= ~mask;
    buffer |= data;
    return writeByte(handle, regAddr, buffer);
}

esp_err_t SPI::writeByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t data) {
    return writeBytes(handle, regAddr, 1, &data);
}

esp_err_t SPI::writeBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, const uint8_t *data) {
    spi_transaction_t transaction;
    transaction.flags = 0;
    transaction.cmd = 0;
    transaction.addr = regAddr & SPIBUS_WRITE;
    transaction.length = length * 8;
    transaction.rxlength = 0;
    transaction.user = NULL;
    transaction.tx_buffer = data;
    transaction.rx_buffer = NULL;
    esp_err_t err = spi_device_transmit(handle, &transaction);
    #if defined CONFIG_SPIBUS_LOG_READWRITES
        if (!err) {
            char str[length*5+1];
            for(size_t i = 0; i < length; i++)
                sprintf(str+i*5, "0x%s%X ", (data[i] < 0x10 ? "0" : ""), data[i]);
            SPIBUS_LOG_RW("[%s, handle:0x%X] Write %d bytes to__ register 0x%X, data: %s", (host == 1 ? "HSPI" : "VSPI"), (uint32_t)handle, length, regAddr, str);
        }
    #endif
    return err;
}


/*******************************************************************************
 * READING
 ******************************************************************************/
esp_err_t SPI::readBit(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    return readBits(handle, regAddr, bitNum, 1, data);
}

esp_err_t SPI::readBits(spi_device_handle_t handle, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
    uint8_t buffer;
    esp_err_t err = readByte(handle, regAddr, &buffer);
    if(!err) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        buffer &= mask;
        buffer >>= (bitStart - length + 1);
        *data = buffer;
    }
    return err;
}

esp_err_t SPI::readByte(spi_device_handle_t handle, uint8_t regAddr, uint8_t *data) {
    return readBytes(handle, regAddr, 1, data);
}

esp_err_t SPI::readBytes(spi_device_handle_t handle, uint8_t regAddr, size_t length, uint8_t *data) {
    if(length == 0) return ESP_ERR_INVALID_SIZE;
    spi_transaction_t transaction;
    transaction.flags = 0;
    transaction.cmd = 0;
    transaction.addr = regAddr | SPIBUS_READ;
    transaction.length = length * 8;
    transaction.rxlength = length * 8;
    transaction.user = NULL;
    transaction.tx_buffer = NULL;
    transaction.rx_buffer = data;
    esp_err_t err = spi_device_transmit(handle, &transaction);
    #if defined CONFIG_SPIBUS_LOG_READWRITES
        if (!err) {
            char str[length*5+1];
            for(size_t i = 0; i < length; i++)
            sprintf(str+i*5, "0x%s%X ", (data[i] < 0x10 ? "0" : ""), data[i]);
            SPIBUS_LOG_RW("[%s, handle:0x%X] Read_ %d bytes from register 0x%X, data: %s", (host == 1 ? "HSPI" : "VSPI"), (uint32_t)handle, length, regAddr, str);
        }
    #endif
    return err;
}


/*
// Receive routines
uint8_t SPI::readData_() {
  uint8_t d = readByte_();
  return (d == ESCAPE) ? readByte_() ^ 0x20 : d;
}

uint8_t SPI::readByte_() {
  uint8_t d = readSPI_();
  return (d == SPI_ESC) ? readSPI_() ^ 0x20 : d;
}

uint8_t SPI::readSPI_() {
  uint8_t d;
  uint16_t timeout = 50;

  // data in the FIFO
  if (FIFO_BYTES != 0) {
    d = fifo[tail++];
    tail %= FIFO_LEN;
    return d;
  }

  // FIFO is empty
  d = SPI_IDLE;
  while (timeout--);
  while (d == SPI_IDLE && timeout--) {
    //USBBlaster.loop();

    digitalWrite(chipSelectPin, LOW);
    d = SPI.transfer(SPI_IDLE);
    digitalWrite(chipSelectPin, HIGH);
  }
  return d;
}

uint16_t AvalonMMClass::readPacket_() {
  while (1) {
    uint8_t r = readData_();
    if (r == SPI_IDLE) {
      // timeout
      return 0xffff;
    }

    if (rstat == waitSop) {
      if (r == SOP) {
        rstat = afterSop;
      }
    } else { // in packet
      if (r == EOP) {
        rstat = waitSop;
        return readData_();
      }
      return r;
    }
  }
  return 0;
}

*/


esp_err_t SPI::transductBytes_fpga(uint32_t base, uint32_t slave, uint32_t write_length, const uint8_t * write_data,
                 uint32_t read_length, uint8_t * read_data, uint32_t flags){

      esp_err_t err;
      spi_transaction_t transaction;

     //for(uint32_t cnt= 0; cnt < write_length;cnt++)  //
    //    SPIBUS_LOG_RW("write data: %d",write_data[cnt]);



        transaction.flags = 0;
        transaction.cmd = 0;
        transaction.length = write_length*8*2;
        transaction.rxlength = 0;//read_length;
        transaction.user = NULL;
        transaction.tx_buffer = write_data;
        transaction.rx_buffer = read_data;

      err = spi_device_transmit(device_fpga, &transaction);


      //uint16_t ret_val = readPacket_();




    // SPIBUS_LOG_RW("retVal %d",ret_val);
    //(spi_device_handle_t handle,uint8_t write_data, uint8_t regAddr, size_t read_length, uint8_t *read_data)
  /*  if(read_length == 0) return ESP_ERR_INVALID_SIZE;

    spi_transaction_t transaction;

    transaction.flags = 0;
    transaction.cmd = 0;

    //SPIBUS_LOG_RW("data %d", write_data);
    //for(uint32_t cnt= 0; cnt < ((write_length < 40)?write_length:40);cnt++)  //
    //  SPIBUS_LOG_RW("write data: %d",write_data[cnt]);
    //SPIBUS_LOG_RW("data: [%.3d][%.3d][%.3d][%.3d][%.3d][%.3d]",write_data[0],write_data[1],write_data[2],write_data[3],write_data[4],write_data[5]);

    SPIBUS_LOG_RW("length send %d", write_length);
    SPIBUS_LOG_RW("length %d", read_length);


    if(read_length <= write_length){
      if(read_length == write_length){
        for(uint32_t cnt= 0; cnt < write_length;cnt++)
          SPIBUS_LOG_RW("write data: [%d]",write_data[cnt]);
          transaction.length = read_length+8;
          transaction.rxlength = 0;
      }
      else{
        transaction.length = write_length;
        transaction.rxlength = read_length;
      }

    //  transaction.addr = regAddr | SPIBUS_READ;

      transaction.user = NULL;
      transaction.tx_buffer = write_data;
      transaction.rx_buffer = read_data;


      //esp_err_t err = spi_device_transmit(device_fpga, &transaction);
    }else{
    //  transaction.addr = regAddr | SPIBUS_READ;
      //uint8_t *tmp_write_data = write_data;
      //for(uint32_t cnt= 0; cnt < write_length;cnt++)
      //write_length
      transaction.length = read_length;
      transaction.rxlength = 0;
      transaction.user = NULL;
      transaction.tx_buffer = write_data;
      transaction.rx_buffer = read_data;



    }
    esp_err_t err = spi_device_transmit(device_fpga, &transaction);

    for(uint32_t cnt= 0; cnt < ((read_length < 100)?read_length:100);cnt++)
    //for(uint32_t cnt= 0; cnt < read_length;cnt++)
      SPIBUS_LOG_RW("data: %d",read_data[cnt]);
    //SPIBUS_LOG_RW("data: [%.3d][%.3d][%.3d][%.3d][%.3d][%.3d]",read_data[0],read_data[1],read_data[2],read_data[3],read_data[4],read_data[5]);

    #if defined CONFIG_SPIBUS_LOG_READWRITES
        if (!err) {
            char str[read_length*5+1];
            for(size_t i = 0; i < read_length; i++)
            sprintf(str+i*5, "0x%s%X ", (read_data[i] < 0x10 ? "0" : ""), read_data[i]);
            SPIBUS_LOG_RW("[%s, device_fpga:0x%X] Read_ %d bytes from register 0x%X, data: %s", (host == 1 ? "HSPI" : "VSPI"), (uint32_t)device_fpga, read_length, base, str);
        }
    #endif
    return err;


    ///esp_err_t err;
    */
    return err;
}





/******************************************************************************
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
******************************************************************************/
/*

int SPI::spi_command(unsigned int base, unsigned int slave, unsigned int write_length, const unsigned char * write_data,
                 unsigned int read_length, unsigned char * read_data, unsigned int flags)
{

	//----------------------------------------------------------------------------------------
  // alt_avalon_spi_command() is Altera's SPI Driver function. If you are using another SPI
	// driver, replace this with your own SPI Driver functions.
  //----------------------------------------------------------------------------------------
  esp_err_t ret_;
  spi_transaction_t t;

  memset(&t, 0, sizeof(t));       //Zero out the transaction

  t.length=write_length;                 //Len is in bytes, transaction length is in bits.
  t.rxlength=read_length;
  t.tx_buffer=write_data;               //Data
  t.rx_buffer=read_data;
  t.user=(void*)1;                //D/C needs to be set to 1


  ret_=spi_device_polling_transmit(spi, &t);  //Transmit!
  assert(ret_==ESP_OK);

	return 0;
}*/

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/


/******************************************************************************
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
******************************************************************************/



unsigned char SPI::byte_to_core_convert (unsigned int send_length, unsigned char* send_data,
								unsigned int response_length, unsigned char* response_data)
{
    unsigned int i;
    unsigned int packet_length = 0;
    unsigned char *send_packet;
    unsigned char *response_packet;
    unsigned char *p;
    unsigned char current_byte;

    //---------------------------------------------------------------------
    // The maximum length of the packet is going to be so we can allocate
    // a chunk of memory for it. Assuming worst case scenario is that each
    // data byte is escaped, so we double the memory allocation.
    //---------------------------------------------------------------------

#ifdef DYNAMIC_MEMORY_ALLOC
    unsigned int send_max_len = 2 * send_length;
    unsigned int response_max_len = 2 * response_length;

	send_packet = (unsigned char*) malloc (send_max_len * sizeof(unsigned char));
    if(send_packet == NULL)	ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");

    response_packet = (unsigned char*) malloc (response_max_len * sizeof(unsigned char));
    if(response_packet == NULL)	ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");
#endif
#ifdef STATIC_MEMORY_ALLOC
	unsigned int response_max_len = 2 * response_length;

	send_packet = &send_byte_buffer[0];

	response_packet = &response_byte_buffer[0];
#endif
    p = send_packet;

    for (i = 0; i < send_length; i++)
    {
        current_byte = send_data[i];
        //-----------------------------------------------
        // Check for Escape and Idle special characters.
        // If exists, insert Escape and XOR the next byte
        //-----------------------------------------------
        switch(current_byte)
        {
            case BYTESIDLECHAR:
                        *p++ = BYTESESCCHAR;
                        *p++ = xor_20(current_byte);
                        break;
            case BYTESESCCHAR:
                        *p++ = BYTESESCCHAR;
                        *p++ = xor_20(current_byte);
                        break;
            default:
                        *p++ = current_byte;
                        break;
        }

    }
    packet_length=p-send_packet;

    //---------------------------------------------------------
    // Use the SPI core access routine to transmit and receive
    //---------------------------------------------------------
    //spi_command(SPI_BASE,0,packet_length,send_packet,response_max_len,response_packet,0);
    //spi_command(0,0,packet_length,send_packet,response_max_len,response_packet,0);

     ESP_ERROR_CHECK(transductBytes_fpga(0,0,packet_length,send_packet,response_max_len,response_packet,0));


    //-----------------------------------------------------------------
    //Analyze response packet , reset pointer to start of response data
    //-----------------------------------------------------------------
	i=0;
	p = response_data;
	while(i < response_max_len*8)
	{
		current_byte = response_packet[i];
		//-----------------------------------------------
		// Check for Escape and Idle special characters.
		// If exists, ignore and XOR the next byte
		//-----------------------------------------------
		switch(current_byte)
		{
			case BYTESIDLECHAR:
				i++;
				break;

			case BYTESESCCHAR:
				i++;
				current_byte = response_packet[i];
				*p++ = xor_20(current_byte);
				i++;
				break;

			default:
				*p++ = current_byte;
				i++;
				break;
		}
	}

#ifdef DYNAMIC_MEMORY_ALLOC
	free(send_packet);
    free(response_packet);
#endif
    return 0;
}

unsigned char SPI::xor_20(unsigned char val)
{
    return val^0x20;
}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/



/******************************************************************************
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
******************************************************************************/

//------------------------------------
// Function prototypes
//------------------------------------

unsigned char SPI::packet_to_byte_convert (unsigned int send_length, unsigned char* send_data,
								unsigned int response_length, unsigned char* response_data)
{
    unsigned int i;
    unsigned int packet_length = 0;
    unsigned char *send_packet;
    unsigned char *response_packet;
    unsigned char *p;
    unsigned char current_byte;

    //--------------------------------------------------------------
    //To figure out what the maximum length of the packet is going
    // to be so we can allocate a chunk of memory for it.
    //
    // All packets start with an SOP byte, followed by a channel
    // id (2 bytes) and end with an EOP. That's 4 bytes.
    //
    // However, we have to escape characters that are the same
    // as any of the SOP/EOP/channel bytes. Worst case scenario
    // is that each data byte is escaped, which leads us to the
    // algorithm below.
    //---------------------------------------------------------------

#ifdef DYNAMIC_MEMORY_ALLOC
    unsigned int send_max_len = 2 * send_length + 4;
    unsigned int response_max_len = 2 * response_length + 4;

	send_packet = (unsigned char *) malloc (send_max_len * sizeof(unsigned char));
    if(send_packet == NULL)	ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");

    response_packet = (unsigned char *) malloc (response_max_len * sizeof(unsigned char));
    if(response_packet == NULL)	ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");
#endif
#ifdef STATIC_MEMORY_ALLOC
	unsigned int response_max_len = 2 * response_length + 4;

	send_packet = &send_packet_buffer[0];

	response_packet = &response_packet_buffer[0];
#endif
    p = send_packet;

    //------------------------------------
    // SOP
    //------------------------------------
    *p++ = SOP;

    //------------------------------------
    // Channel information. Only channel 0 is defined.
     //------------------------------------
    *p++ = CHANNEL;
    *p++ = 0x0;

    //------------------------------------
    // Append the data to the packet
    //------------------------------------
    for (i = 0; i < send_length; i++)
    {
        current_byte = send_data[i];
        //------------------------------------
        // EOP must be added before the last byte
        //------------------------------------
        if (i == send_length-1)
        {
            *p++ = EOP;
        }

        //------------------------------------
        // Escape data bytes which collide with our
        // special characters.
        //------------------------------------
        switch(current_byte)
        {
            case SOP:
                        *p++ = ESC;
                        *p++ = xor_20(current_byte);
                        break;
            case EOP:
                        *p++ = ESC;
                        *p++ = xor_20(current_byte);
                        break;
            case CHANNEL:
                        *p++ = ESC;
                        *p++ = xor_20(current_byte);
                        break;
            case ESC:
                        *p++ = ESC;
                        *p++ = xor_20(current_byte);
                        break;

            default:
                        *p++ = current_byte;
                        break;
        }

    }
    packet_length=p-send_packet;

	byte_to_core_convert(packet_length,send_packet,response_max_len,response_packet);
	//-----------------------------------------------------------------
	//Analyze response packet , reset pointer to start of response data
	//-----------------------------------------------------------------
	p = response_data;
	//-------------
	//Look for SOP
	//-------------
	for(i=0;i<response_max_len;i++){
		if(response_packet[i] == SOP) {
			i++;
			break;
		}
	}

	//-------------------------------
	//Continue parsing data after SOP
	//-------------------------------
	while(i < response_max_len)
	{
		current_byte = response_packet[i];

		switch(current_byte)
		{
			case ESC:
			case CHANNEL:
			case SOP:
				i++;
				current_byte = response_packet[i];
				*p++ = xor_20(current_byte);
				i++;
				break;

			//------------------------------------
			// Get a EOP, get the next last byte
			// and exit while loop
			//------------------------------------
			case EOP:
				i++;
				current_byte = response_packet[i];

				if((current_byte == ESC)||(current_byte == CHANNEL)||(current_byte == SOP)){
					i++;
					current_byte = response_packet[i];
					*p++ = xor_20(current_byte);
				}

				else *p++ = current_byte;

				i = response_max_len;
				break;

			default:
				*p++ = current_byte;
				i++;
				break;
		}
	}
#ifdef DYNAMIC_MEMORY_ALLOC
	free(send_packet);
    free(response_packet);
#endif
    return 0;
}


/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/


/******************************************************************************
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved. All use of this software and documentation is          *
* subject to the License Agreement located at the end of this file below.     *
******************************************************************************/


unsigned char SPI::transaction_channel_write (unsigned int address,
									unsigned int burst_length,
									unsigned char* data_buffer,
									unsigned char sequential)
{
    return sequential?do_transaction(SEQUENTIAL_WRITE, burst_length, address, data_buffer):do_transaction(NON_SEQUENTIAL_WRITE, burst_length, address, data_buffer);
    //return do_transaction(SEQUENTIAL_WRITE, burst_length, address, data_buffer);
}

unsigned char SPI::transaction_channel_read  (unsigned int address,
									unsigned int burst_length,
									unsigned char* data_buffer,
									unsigned char sequential)
{
    return sequential?do_transaction(SEQUENTIAL_READ, burst_length, address, data_buffer):do_transaction(NON_SEQUENTIAL_READ, burst_length, address, data_buffer);
    //return do_transaction(SEQUENTIAL_READ, burst_length, address, data_buffer);
}

unsigned char SPI::do_transaction(unsigned char trans_type,
								unsigned int size,
								unsigned int address,
								unsigned char* data)
{
    unsigned int i = 0;
    unsigned char result = 0;
    unsigned char header[8];
    unsigned char* transaction;
    unsigned char* response;
    unsigned char* p;


    //-------------------------
    // Make transaction header
    //-------------------------
    header[0] = trans_type;
    header[1] = 0;
    header[2] = (size >> 8) & 0xff;
    header[3] = (size & 0xff);
    header[4] = (address >> 24) & 0xff;
    header[5] = (address >> 16) & 0xff;
    header[6] = (address >> 8)  & 0xff;
    header[7] = (address & 0xff);

    //ESP_LOGI(TAG_SPI,"do_transaction");


    switch(trans_type)
    {
        case NON_SEQUENTIAL_WRITE:
        case SEQUENTIAL_WRITE:
			//--------------------------------
			// Build up the write transaction
			//--------------------------------
#ifdef DYNAMIC_MEMORY_ALLOC
			transaction = (unsigned char *) malloc ((size + HEADER_LEN) * sizeof(unsigned char));
			if(transaction == NULL)		ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");

			response = (unsigned char *) malloc (RESPONSE_LEN * sizeof(unsigned char));
			if(response == NULL)	ESP_LOGI(TAG_SPI,"Allocating heap memory failed\n");
#endif
#ifdef STATIC_MEMORY_ALLOC
			transaction = &transaction_buffer[0];

			response = &response_buffer_[0];
#endif
			p = transaction;

			for (i = 0; i < HEADER_LEN; i++)
				*p++ = header[i];

			for (i = 0; i < size; i++)
				*p++ = *data++;

			//-----------------------------------------------
			// Send the header and data, get 4 byte response
			//-----------------------------------------------
			packet_to_byte_convert (size + HEADER_LEN, transaction, RESPONSE_LEN, response);

			//------------------------------------------------------------------
			// Check return number of bytes in the 3rd and 4th byte of response
			//------------------------------------------------------------------
			if (size == (((unsigned int)(response[2]& 0xff)<<8)|((unsigned int)(response[3]&0xff))))
				result = 1;
#ifdef DYNAMIC_MEMORY_ALLOC
			free(transaction);
			free(response);
#endif

			break;

        case NON_SEQUENTIAL_READ:
        case SEQUENTIAL_READ:
#ifdef DYNAMIC_MEMORY_ALLOC
        	response = (unsigned char *) malloc (size * sizeof(unsigned char));
        	if(response == NULL)
        		ESP_LOGI(TAG_SPI,"Allocating heap memory failed");
#endif
#ifdef STATIC_MEMORY_ALLOC
			response = &response_buffer_[0];
#endif
        	//--------------------------------------------
        	// Send the header, get n size byte response
        	//--------------------------------------------
        	packet_to_byte_convert (HEADER_LEN, header, size, response);

			for (i = 0; i < size; i++)
				*data++ = *response++;

			//-------------------------------------------------------------------
			// Read do not return number of bytes , assume result always set to 1
			//-------------------------------------------------------------------
			result = 1;
#ifdef DYNAMIC_MEMORY_ALLOC
			free(response);
#endif
			break;

        default:
			break;
    }

    if(result)return 1;
    else return 0;
}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2010 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/


void SPI::create_test_data(unsigned char* buffer, int length)
{
    int i=0;

    for (i = 0; i < BUFFER_LENGTH; i++)
      buffer[i] = (0xFF & rand()) % 256;  // random values between 0 and 255

}
