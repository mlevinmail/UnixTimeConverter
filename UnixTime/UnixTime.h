#pragma once
#include <stdint.h>

// Data structure for DateTime
struct DateTime {
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Second;

	uint8_t Day;
	uint8_t Month;
	uint16_t Year;
};

class UnixTime {

public:

	// Converts DateTime to a unix time
	uint32_t   ConvertToUnixTime(const DateTime *dateTime);


	// Converts Unix time to a DateTime
	DateTime  ConvertFromUnixTime(uint32_t unixTime);

private:



	uint16_t GetDayNumFromYearStart(uint8_t day, uint8_t month, bool isLeapYear);


	// Given the day number from when the year began the function will return the month number
	uint8_t GetMonthByDay(uint16_t day, bool isLeapYear);

	// The function will return the day number in a month given the day number from the begining
	// of the year
	uint8_t GetMonthDayByYearDay(uint16_t yearDay, bool isLeapYear);

	bool isLeapYear(uint16_t year);

	// Returns number of days in a month. 
	//  
	// month - takes value from 1 to 12
	// isLeapYear - true if it's leap year
	uint8_t daysInMonth(uint8_t month, bool isLeapYear);



	// Precalculated time 
	const uint32_t SecondsInNonLeapYear = 31536000;
	const uint32_t SecondsInLeapYear    = 31622400;
	const uint32_t HoursInYear          = 31436000;
	const uint32_t SecondsInDay         = 86400;	
	const uint16_t SecondsInHour        = 3600;
	const uint16_t MinutesInDay         = 1440;
	const uint8_t  SecondsInMinute      = 60;


};

