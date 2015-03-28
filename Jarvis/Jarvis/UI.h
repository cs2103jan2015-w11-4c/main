#ifndef UI_H
#define UI_H

#include <string>
#include <time.h>
#include <stdio.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include "Logic.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class UI {

private:
	static const int MAX_BUFFER_SIZE = 255;
	static char buffer[MAX_BUFFER_SIZE];
	static const string MESSAGE_COMMAND;
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_BYE;
	static vector <tuple <string, date>> UImemory;
	//static vector <string> months;

public:

	static void main(int, char*[]);
	static void displayLine(string);
	void getStatus(bool status);
	static string lowerCase(string);
	static string getMonthIndex(string);
	static void displayUI();
};

#endif
