#include "CAN_utils.h"


CanMessage createCanMessage(uint32_t id, uint32_t dlc, uint8_t data[8])
{
	CanMessage message;

	message.msgHeader.StdId = id;
	message.msgHeader.ExtId = 0;
	message.msgHeader.RTR = CAN_RTR_DATA;
	message.msgHeader.IDE = CAN_ID_STD;
	message.msgHeader.DLC = dlc;
	message.msgHeader.TransmitGlobalTime = DISABLE;

	//uint8_t size = sizeof(data)/sizeof(data[0]);

	for (int i = 0; i < 8; ++i)
	{
		message.msgData[i] = data[i];
	}

	return message;
}

void canMessageSend(CAN_HandleTypeDef *hcan, CanMessage *canMessage, uint32_t *TxMailbox)
{
	while(HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0);
	HAL_CAN_AddTxMessage(hcan, &canMessage->msgHeader, canMessage->msgData, &TxMailbox);
}
