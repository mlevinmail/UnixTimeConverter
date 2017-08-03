#include "UnixTime.h"
#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;




UnixTime unixTime;

int main(void) {

	//1501681604

	
	

	//for (uint32_t currentSecond = 0; currentSecond < 1501681604; currentSecond += 4000) {
	//	DateTime dtime = unixTime.ConvertFromUnixTime(currentSecond);
	//	string myOutput = to_string(currentSecond) + "," + to_string(dtime.Year) + ',' + to_string(dtime.Month) + ',' + to_string(dtime.Day) + ',' + to_string(dtime.Hour) + ',' + to_string(dtime.Minute) + ',' + to_string(dtime.Second);

	//	cout << myOutput << endl;
	//}

	DateTime dtime = unixTime.ConvertFromUnixTime(1501786865);

	string myOutput = to_string(1501786865) + "  " + to_string(dtime.Year) + ',' + to_string(dtime.Month) + ',' + to_string(dtime.Day) + ',' + to_string(dtime.Hour) + ',' + to_string(dtime.Minute) + ',' + to_string(dtime.Second);
	cout << myOutput << endl;




	getchar();
}

