#include "UnixTime.h"
#include <stdint.h>


using namespace std;


uint32_t UnixTime::ConvertToUnixTime(DateTime *dateTime) {
	// Calculating the number of seconds to the begining of the same year

	uint32_t secondsFromYearStart = 0;
	secondsFromYearStart += dateTime->Minute * SecondsInMinute;
	secondsFromYearStart += dateTime->Second;
	secondsFromYearStart += dateTime->Hour * SecondsInHour;
	// Subtracting one to account for the fact that there is no day 0
	secondsFromYearStart += (dateTime->Day - 1) * SecondsInDay;

	// checking if the current year is a leap year
	bool isCurrentLeapYear = isLeapYear(dateTime->Year);

	for (uint8_t i = 1; i < dateTime->Month; i++)
	{
		secondsFromYearStart += daysInMonth(i, isCurrentLeapYear) * SecondsInDay;
	}

	uint32_t secondsFromOrigin = 0;
	// Calculating the number of seconds from 1970/1/1 till the current year
	for (uint16_t i = 1970; i < dateTime->Year; i++)
	{
		secondsFromOrigin += isLeapYear(i) == true ? SecondsInLeapYear : SecondsInNonLeapYear;
	}
	secondsFromOrigin += secondsFromYearStart;
	return secondsFromOrigin;
}

// The function doing some heavy lifting to convert unix time to DateTime

DateTime UnixTime::ConvertFromUnixTime(uint32_t uTimestamp) {
	DateTime dateTime;
	// Unix timespamp / hours. Ignoring the decimal part will give the year 
	uint16_t yearSinceEpoch = uTimestamp / HoursInYear;

	uint16_t numberOfLeapYears = (yearSinceEpoch + 1970 - 1969) / 4;

	// Converting this year begining to the unix time, so it could be subtructed from the 
	// epoch time to find out how many seconds passed since the begining of the year
	DateTime dtime;
	dtime.Year = 1970 + yearSinceEpoch;
	dtime.Month = 1;
	dtime.Day = 1;
	dtime.Hour = 0;
	dtime.Minute = 0;
	dtime.Second = 0;


	uint32_t secondsSinceBeginingOfTheYear = uTimestamp - ConvertToUnixTime(&dtime);
	// Finding out how many seconds has passed since the year started
	uint32_t daysSinceBeginingOfTheYear = (secondsSinceBeginingOfTheYear) / SecondsInDay;


	bool isCurrentLeapYear = isLeapYear(dtime.Year);
	
	// Since the daysSinceBeginingOfTheYear is rounded to the nearest integer one day must be added
	// as the daysSinceBeginingOfTheYear = how many full days passed since the begining of the year, not 
	// including the hours, minutes, and seconds.

	dateTime.Month = GetMonthByDay(daysSinceBeginingOfTheYear + 1, isCurrentLeapYear);
	dateTime.Day = GetMonthDayByYearDay(daysSinceBeginingOfTheYear + 1, isCurrentLeapYear);
	dateTime.Year = yearSinceEpoch + 1970;


	// Find out how many seconds passed since the beginng of the day

	
	// Calculated diffirence is how much seconds passed since the day began
	uint32_t secondsSinceTheDayStarted = secondsSinceBeginingOfTheYear - daysSinceBeginingOfTheYear * SecondsInDay;
	
	dateTime.Hour = secondsSinceTheDayStarted / SecondsInHour;
	uint16_t secondsSinceTheHourStarted = secondsSinceTheDayStarted - dateTime.Hour* SecondsInHour;
	dateTime.Minute = secondsSinceTheHourStarted / SecondsInMinute;
	uint8_t secondsSinceMinuteStarted = secondsSinceTheHourStarted - dateTime.Minute * SecondsInMinute;
	dateTime.Second = secondsSinceMinuteStarted;



	return dateTime;
}


uint8_t UnixTime::GetMonthByDay(uint16_t daynum, bool isLeapYear) {	
	uint16_t currentDay = 0;
	for (int month = 1; month <= 12; month++) {
		currentDay += daysInMonth(month, isLeapYear);

		if (currentDay >= daynum)
			return month;
	}
	return -1;
};

uint8_t UnixTime::GetMonthDayByYearDay(uint16_t yearDay, bool isLeapYear) {
	// Determain the number of days right before the begining of the month
	int16_t currentDay = 0;
	for (int month = 1; month < GetMonthByDay(yearDay, isLeapYear); month++) {
		currentDay += daysInMonth(month, isLeapYear);
	} // the diffirence will be the day number in a month
	return yearDay - (currentDay);
};

uint16_t UnixTime::GetDayNumFromYearStart(uint8_t day, uint8_t month, bool isLeapYear) {
	uint8_t currentDayCount = 0;
	// itterating through months to add all the days before the last month
	for (int i = 1; i < month; i++) {
		currentDayCount += daysInMonth(i, isLeapYear);
	}
	// Adding the days to all the previous months
	return currentDayCount + day;
}



bool UnixTime::isLeapYear(uint16_t year) {
	bool case1 = year % 4 == 0;
	bool case2 = year % 100 == 0;
	bool case3 = year % 400 == 0;
	return (case1 && !case2) || (case1 && case2 && case3);
}

uint8_t UnixTime::daysInMonth(uint8_t month, bool isLeapYear) {
	if (month < 1 || month > 12)
		return -1;
	if (month == 2 && isLeapYear)
		return 29;
	if (month == 2 && !isLeapYear)
		return 28;
	if (month < 8)
		return month % 2 == 0 ? 30 : 31;
	else
		return month % 2 == 0 ? 31 : 30;
}
