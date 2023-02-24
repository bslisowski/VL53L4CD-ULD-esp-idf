/*
 Copyright (c) 2021, STMicroelectronics - All Rights Reserved

 This file : part of VL53L4CD Ultra Lite Driver and : dual licensed, either
 'STMicroelectronics Proprietary license'
 or 'BSD 3-clause "New" or "Revised" License' , at your option.

*******************************************************************************

 'STMicroelectronics Proprietary license'

*******************************************************************************

 License terms: STMicroelectronics Proprietary in accordance with licensing
 terms at www.st.com/sla0081

 STMicroelectronics confidential
 Reproduction and Communication of this document : strictly prohibited unless
 specifically authorized in writing by STMicroelectronics.


*******************************************************************************

 Alternatively, VL53L4CD Ultra Lite Driver may be distributed under the terms of
 'BSD 3-clause "New" or "Revised" License', in which case the following
 provisions apply instead of the ones mentioned above :

*******************************************************************************

 License terms: BSD 3-clause "New" or "Revised" License.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
*/

#include "platform.h"


uint8_t VL53L4CD_RdDWord(Dev_t dev, uint16_t RegisterAdress, uint32_t *value) { 
	
	uint8_t status = 255;  
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff) }; 
	uint8_t read_buf[4] = {0};
 	
	esp_err_t err = i2c_master_write_read_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), read_buf, sizeof(read_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 

	*value = ((uint32_t)read_buf[0] << 24) | ((uint32_t)read_buf[1] << 16) | ((uint32_t)read_buf[2] << 8) | (uint32_t)read_buf[3]; 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t VL53L4CD_RdWord(Dev_t dev, uint16_t RegisterAdress, uint16_t *value) { 
	
	uint8_t status = 255;
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff) }; 
	uint8_t read_buf[2] = {0}; 
	
	esp_err_t err = i2c_master_write_read_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), read_buf, sizeof(read_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 
	
	*value = ((uint16_t)read_buf[0] << 8) | (uint16_t)read_buf[1]; 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t VL53L4CD_RdByte(Dev_t dev, uint16_t RegisterAdress, uint8_t *value) { 
	
	uint8_t status = 255; 
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff) }; 
	uint8_t read_buf[1] = {0}; 
	
	esp_err_t err = i2c_master_write_read_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), read_buf, sizeof(read_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 
	
	*value = read_buf[0]; 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t VL53L4CD_WrByte(Dev_t dev, uint16_t RegisterAdress, uint8_t value) { 
	
	uint8_t status = 255; 
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff), value }; 
	
	esp_err_t err = i2c_master_write_to_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t VL53L4CD_WrWord(Dev_t dev, uint16_t RegisterAdress, uint16_t value) { 
	
	uint8_t status = 255; 
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff), (uint8_t)(value >> 8), (uint8_t)(value & 0xff) }; 
	
	esp_err_t err = i2c_master_write_to_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t VL53L4CD_WrDWord(Dev_t dev, uint16_t RegisterAdress, uint32_t value) { 
	
	uint8_t status = 255; 
	uint8_t d = (uint8_t)((dev >> 1) & 0x7f); 
	uint8_t write_buf[] = { (uint8_t)(RegisterAdress >> 8), (uint8_t)(RegisterAdress & 0xff), (uint8_t)(value >> 24), (uint8_t)(value >> 8), (uint8_t)(value & 0xff) }; 
	
	esp_err_t err = i2c_master_write_to_device(I2C_NUM_0, d, write_buf, sizeof(write_buf), I2C_TIMEOUT_MS / portTICK_PERIOD_MS); 
	
	status = esp_err_to_VL53L4CD_status(err); 
	
	return status;
}

uint8_t WaitMs(Dev_t dev, uint32_t TimeMs) { 

	vTaskDelay(TimeMs / portTICK_PERIOD_MS); 
	
	return VL53L4CD_ERROR_NONE;
}

uint8_t esp_err_to_VL53L4CD_status(esp_err_t err) { 

	switch(err) { 
		case ESP_ERR_INVALID_STATE: 
			ESP_LOGW(TAG, "ESP_ERR_INVALID_STATE"); 
		case ESP_ERR_INVALID_ARG: 
			return VL53L4CD_ERROR_INVALID_ARGUMENT; 
		case ESP_FAIL: 
			ESP_LOGW(TAG, "ESP_FAIL"); 
		case ESP_ERR_TIMEOUT: 
			return VL53L4CD_ERROR_TIMEOUT; 
		default: 
			return VL53L4CD_ERROR_NONE; 
	}
}
