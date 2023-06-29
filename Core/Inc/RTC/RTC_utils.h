#ifndef __RTC_UTILS_INCLUDE__
#define __RTC_UTILS_INCLUDE__

#include <stdbool.h>
#include <stdint.h>
#include "main.h"


uint8_t calculateWeekday(uint8_t date, uint8_t month, uint16_t year);

bool checkRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

void setupRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

void checkAndSetRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime);

RTC_DateTypeDef getRTC_DateTypeDef(uint8_t date, uint8_t month, uint16_t year);

RTC_TimeTypeDef getRTC_TimeTypeDef(uint8_t hours, uint8_t minutes, uint8_t seconds);

uint8_t getRTCMonthFromInt(uint8_t monthNumber);


#endif
