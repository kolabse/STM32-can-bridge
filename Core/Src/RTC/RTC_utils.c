#include "RTC/RTC_utils.h"

uint8_t calculateWeekday(uint8_t date, uint8_t month, uint16_t year)
{
	uint8_t weekday;
	if (month < 3)
	{
		year--;
		month += 12;
	}
	weekday = ((date + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7) + 1;

	return (uint8_t)weekday;

}


bool checkRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime)
{
	RTC_DateTypeDef RTC_Date;
	RTC_TimeTypeDef RTC_Time;

	  HAL_RTC_GetDate(hrtc, &RTC_Date, RTC_FORMAT_BIN);
	  HAL_RTC_GetTime(hrtc, &RTC_Time, RTC_FORMAT_BIN);

	return (
				(RTC_Date.Year == sDate->Year) &&
				(RTC_Date.Month == sDate->Month) &&
				(RTC_Date.Date == sDate->Date) &&
				(RTC_Time.Hours == sTime->Hours) &&
				(RTC_Time.Minutes == sTime->Minutes) &&
				(RTC_Time.Seconds == sTime->Seconds)
			);
}

void setupRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime)
{
	HAL_RTC_SetTime(hrtc, sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(hrtc, sDate, RTC_FORMAT_BIN);
	HAL_RTCEx_BKUPWrite(hrtc, RTC_BKP_DR9, '*');
}

void checkAndSetRTC(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, RTC_TimeTypeDef *sTime)
{
	if (!checkRTC(hrtc, sDate, sTime))
	{
		setupRTC(hrtc, sDate, sTime);
	}
}

RTC_DateTypeDef getRTC_DateTypeDef(uint8_t date, uint8_t month, uint16_t year)
{
	RTC_DateTypeDef RTC_Date;

	RTC_Date.Date = date;
	RTC_Date.Month = month;
	RTC_Date.WeekDay = calculateWeekday(date, month, year);
	RTC_Date.Year = year;

	return RTC_Date;
}

RTC_TimeTypeDef getRTC_TimeTypeDef(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	RTC_TimeTypeDef RTC_Time;

	RTC_Time.Hours = hours;
	RTC_Time.Minutes = minutes;
	RTC_Time.Seconds = seconds;

	return RTC_Time;
}

uint8_t getRTCMonthFromInt(uint8_t monthNumber)
{
	return (monthNumber < 10 ? monthNumber : monthNumber + 6);
}
