#ifndef __CAN_UTILS_INCLUDE__
#define __CAN_UTILS_INCLUDE__

#include "main.h"
#include <stdint.h>

typedef struct
{
	int32_t canErrCounter;
	uint32_t canTxMailbox;
	uint8_t canDataArray[0x5FF][8];
} Can_DataTypeDef;

typedef enum
{
	CAN_OK       = 0x00U,
	CAN_ERROR    = 0x01U,
	CAN_BUSY     = 0x02U,
	CAN_TIMEOUT  = 0x03U
} CAN_StatusTypeDef;

void copyArray(uint8_t source[], uint8_t destination[], uint8_t length);
void assignDefaultValues(Can_DataTypeDef *canData);

CAN_StatusTypeDef sendCanMessage(CAN_HandleTypeDef *hcan, Can_DataTypeDef *canData, uint8_t messageId);


#endif
