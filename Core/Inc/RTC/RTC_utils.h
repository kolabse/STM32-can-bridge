/**
  ******************************************************************************
  * @file    RTC_utils.h
  * @author  kolabse (mikefedd@gmail.com)
  * @brief   RTC utils to check RTC set time, set RTC time ant get some data
  *          from date and time
  ******************************************************************************
  */
#ifndef __STM_RTC_UTILS__
#define __STM_RTC_UTILS__

#include <stdbool.h>
#include <stdint.h>
#include "main.h"

/**
 * @brief Returns week day number
 * @param date day of date
 * @param month month of date
 * @param year year of date
*/
uint8_t calculateWeekday(uint8_t date, uint8_t month, uint16_t year);

/**
 * @brief Checks rtc values to compliance with date and time
 * @param hrtc HAL RTC interface
 * @param sDate struct with date
 * @param sTime struct with time
*/
bool checkRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

/**
 * @brief Sets rtc values to compliance with date and time
 * @param hrtc HAL RTC interface
 * @param sDate struct with date
 * @param sTime struct with time
*/
void setupRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

/**
 * @brief Checks rtc values to compliance with date and time and sets it if it's different
 * @param hrtc HAL RTC interface
 * @param sDate struct with date
 * @param sTime struct with time
*/
void checkAndSetRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

/**
 * @brief Returns rtc date struct from presented day, month and year
 * @param date day of date
 * @param month month of date
 * @param year year of date
*/
RTC_DateTypeDef getRTC_DateTypeDef(uint8_t date, uint8_t month, uint16_t year);

/**
 * @brief Returns rtc time struct from presented hours, minutes and seconds
 * @param hours hour of day
 * @param minutes minute of hour
 * @param seconds second of minute
*/
RTC_TimeTypeDef getRTC_TimeTypeDef(uint8_t hours, uint8_t minutes, uint8_t seconds);

/**
 * @brief Returns rtc month number from month number
 * @param monthNumber number of month
*/
uint8_t getRTCMonthFromInt(uint8_t monthNumber);


#endif /* __STM_RTC_UTILS__ */
