#include "UnixTime.h"
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;




UnixTime unixTime;

int main(void) {
	
	// Part 1 Converting to unix time
	DateTime today;

	// Set the dateTime you want to convert to unix time;
	today.Day = 3;
	today.Month = 8;
	today.Year = 2017;
	today.Hour = 13; // use 24 hour format
	today.Minute = 58;
	today.Second = 0;
	
	// pass a reference of DateTime to a function that converts to unix time
	auto result = unixTime.ConvertToUnixTime(&today);
	cout << "Today in unix time is " << result << endl;

	// Part 2 Converting from unix time

	// The function to convert from unix time will return a DateTime data structure
	DateTime bigevent;
	bigevent = unixTime.ConvertFromUnixTime(626634000);

	cout << "On the year " << bigevent.Year << " day " << to_string(bigevent.Day)<< " month " << to_string(bigevent.Month) << " at " << to_string(bigevent.Hour) << ":" << to_string(bigevent.Minute)<< ":" << to_string(bigevent.Second)<< " the big wall came down " << endl;





	getchar();
}

