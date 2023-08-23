#include "CAN/CAN_utils.h"


void copyArray(uint8_t source[], uint8_t dest[], uint8_t len) {
    for (int i = 0; i < len; i++) {
        dest[i] = source[i];
    }
}

void assignDefaultValues(Can_DataTypeDef *canData)
{
	uint8_t msgData036[8] = {0x0E, 0x00, 0x03, 0x0F, 0X91, 0x00, 0x01, 0xAC};

	copyArray(msgData036, canData->canDataArray[0x036], 8);

}

CAN_StatusTypeDef sendCanMessage(CAN_HandleTypeDef *hcan, Can_DataTypeDef *canData, uint8_t messageId)
{
	CAN_TxHeaderTypeDef msgHeader;

	uint32_t dlc = sizeof(canData->canDataArray[messageId])/sizeof(canData->canDataArray[messageId][0]);

	msgHeader.StdId = messageId;
	msgHeader.ExtId = 0;
	msgHeader.RTR = CAN_RTR_DATA;
	msgHeader.IDE = CAN_ID_STD;
	msgHeader.DLC = dlc;
	msgHeader.TransmitGlobalTime = DISABLE;

	while(HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0);

	HAL_StatusTypeDef status;

	status = HAL_CAN_AddTxMessage(hcan, &msgHeader, canData->canDataArray[messageId], &canData->canTxMailbox);

	if(status != HAL_OK)
	{
		return CAN_OK;
	}
	else
	{
		return CAN_ERROR;
	}
}
void decodeCan04Message(uint8_t messageId, uint8_t messageData[8], Can_DataTypeDef *canData)
{
}
