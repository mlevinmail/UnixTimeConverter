#include "UnixTime.h"
#include <stdint.h>



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

DateTime UnixTime::ConvertFromUnixTime(uint32_t unixTime) {
	DateTime dateTime;

	// Calculating number of years
	uint16_t currentYear = 1970;
	uint32_t currentSecond = 0;


	// Finding the year
	while (currentSecond + SecondsInLeapYear <= unixTime)
	{
		if (isLeapYear(currentYear))
			currentSecond += SecondsInLeapYear;
		else
			currentSecond += SecondsInNonLeapYear;
		currentYear++;
	}

	dateTime.Year = currentYear;
	auto isCurrentLeapYear = isLeapYear(dateTime.Year);
	uint8_t currentMonth = 1;

	uint8_t daycount = 1;

	// Finding the month
	while (currentSecond + SecondsInDay * 31 <= unixTime) {
		auto days = daysInMonth(currentMonth, isCurrentLeapYear);
		auto secondsInMonth = SecondsInDay * days;

		if (currentSecond + secondsInMonth <= unixTime)
			currentSecond += secondsInMonth;


		currentMonth++;

	}


	dateTime.Month = currentMonth;

	auto days = daysInMonth(currentMonth, isCurrentLeapYear);
	uint8_t currentDay = 1;


	while (currentSecond + SecondsInDay <= unixTime) {
		currentSecond += SecondsInDay;
		currentDay++;

		daycount++;

		if (daycount == days)
			break;
	}

	dateTime.Day = currentDay;

	uint8_t currentHour = 0;

	while (currentSecond + SecondsInHour <= unixTime) {

		currentSecond += SecondsInHour;
		currentHour++;


	}

	dateTime.Hour = currentHour;
	uint8_t currentMinute = 0;

	while (currentSecond + SecondsInMinute <= unixTime) {
		currentSecond += SecondsInMinute;
		currentMinute++;
	}

	dateTime.Minute = currentMinute;

	uint8_t seconds = unixTime - currentSecond;


	dateTime.Second = seconds;



	return dateTime;
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
