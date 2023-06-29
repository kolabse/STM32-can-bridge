#ifndef __CAN_UTILS_INCLUDE__
#define __CAN_UTILS_INCLUDE__

#include <stdint.h>
#include "main.h"


typedef struct
{
	CAN_TxHeaderTypeDef msgHeader;
	uint8_t msgData[8];
} CanMessage;


CanMessage createCanMessage(uint32_t id, uint32_t dlc, uint8_t data[8]);
void canMessageSend(CAN_HandleTypeDef *hcan, CanMessage *canMessage, uint32_t *TxMailbox);

#endif
