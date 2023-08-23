/**
  ******************************************************************************
  * @file    CAN_utils.h
  * @author  kolabse (mikefedd@gmail.com)
  * @brief   Can utils to decode prepare and resend can messagges
  ******************************************************************************
  */
#ifndef __STM_CAN_UTILS__
#define __STM_CAN_UTILS__

#include "main.h"
#include <stdint.h>


/**
 * @brief Structure of main bridge data
 */
typedef struct
{
	/** Counter for can errors */
	int32_t canErrCounter;
	/** Outgoing messages mailbox ID */
	uint32_t canTxMailbox;
	/** Array of Data fields for outgoing messages */
	uint8_t canDataArray[0x5FF][8];
} Can_DataTypeDef;

/**
 * @brief Can bus status enum
*/
typedef enum
{
	CAN_OK       = 0x00U,
	CAN_ERROR    = 0x01U,
	CAN_BUSY     = 0x02U,
	CAN_TIMEOUT  = 0x03U
} CAN_StatusTypeDef;

/**
 * @brief Copies array values
 * @param source[] source array
 * @param dest[] destination array
 * @param len length of arrays
 */
void copyArray(uint8_t source[], uint8_t dest[], uint8_t len);

/**
 * @brief Fills array of Data fields with default values
 * @param canData Struct with CanData 
*/
void assignDefaultValues(Can_DataTypeDef *canData);

/**
 * @brief Sends message to can bus
 * @param messageId id of can message
 * @param messageData array of can message data
 * @param hcan HAL CAN-BUS interface which message will be send
 * @param canData Struct with CanData
 * @param messageId id of can message
*/
CAN_StatusTypeDef sendCanMessage(CAN_HandleTypeDef *hcan, Can_DataTypeDef *canData, uint8_t messageId);

/**
 * @brief Decode can messages and puts data to struct with CanData
 * @param messageId id of can message
 * @param messageData array of can message data
 * @param canData Struct with CanData
*/
void decodeCan04Message(uint8_t messageId, uint8_t messageData[8], Can_DataTypeDef *canData);

#endif /* __STM_CAN_UTILS__ */
