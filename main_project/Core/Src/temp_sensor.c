#include "temp_sensor.h"
#include "i2c.h"
#include <string.h>
#include <usart.h>
#include <stdio.h>





HAL_StatusTypeDef getTemp(int32_t *float_data){

	uint8_t data = 0x2E;																//start to measure

	HAL_I2C_Mem_Write(&hi2c1, SENSORAddr << 1, 0xF4, 1, &data, 1, HAL_MAX_DELAY);

	HAL_Delay(100);																			//need at least 4.5ms to measure

	uint8_t data2[2] = {0};																//read data, from 2 registers

	HAL_I2C_Mem_Read(&hi2c1, SENSORAddr << 1, 0xF6, 1, data2, 2, HAL_MAX_DELAY);

	uint16_t UT = ((uint16_t)data2[0] << 8) | data2[1];									//merge data


	uint8_t AC5[2];																	//get paraments, do calculations, and get final results
	uint8_t AC6[2];
	uint8_t MC[2];
	uint8_t MD[2];

	HAL_I2C_Mem_Read(&hi2c1, SENSORAddr << 1, 0xB2, 1, AC5, 2, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, SENSORAddr << 1, 0xB4, 1, AC6, 2, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, SENSORAddr << 1, 0xBC, 1, MC, 2, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, SENSORAddr << 1, 0xBE, 1, MD, 2, HAL_MAX_DELAY);

	uint16_t AC5A = ((uint16_t)AC5[0] << 8) | AC5[1];
	uint16_t AC6A = ((uint16_t)AC6[0] << 8) | AC6[1];
	int16_t MCA = ((uint16_t)MC[0] << 8) | MC[1];
	int16_t MDA = ((uint16_t)MD[0] << 8) | MD[1];

	int32_t X1, X2, B5, T;

	X1 = ((int32_t)UT - AC6A) * AC5A / 32768;

	X2 = ((int32_t)MCA * 2048) / (X1 + MDA);

	B5 = X1 + X2;

	T = (B5 + 8) / 16;

	float temperature = T / 10.0f;

	*float_data = T;

	//transmit data


	// 转换为十分之一摄氏度的整数
//	int32_t temp10 = (int32_t)(temperature * 10.0f);
//	int32_t integer = temp10 / 10;
//	int32_t decimal = temp10 % 10;
//
//	if (decimal < 0)
//	{
//	    decimal = -decimal;
//	}
//
//	char sendData[50];
//
//	sprintf(sendData, "%ld.%01ld\r\n",
//	        (long)integer, (long)decimal);
//
//	HAL_UART_Transmit(&huart2, (uint8_t *)sendData, strlen(sendData), HAL_MAX_DELAY);


}


