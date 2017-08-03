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

	uint32_t   ConvertToUnixTime(DateTime *dateTime);
	DateTime  ConvertFromUnixTime(uint32_t unixTime);

private:

	bool isLeapYear(uint16_t year);
	uint8_t daysInMonth(uint8_t month, bool isLeapYear);


	// Precalculated time to easy the 

	const uint32_t SecondsInNonLeapYear = 31536000;
	const uint32_t SecondsInLeapYear = 31622400;

	const uint32_t SecondsInDay = 86400;
	const uint16_t SecondsInHour = 3600;
	const uint8_t  SecondsInMinute = 60;



};

