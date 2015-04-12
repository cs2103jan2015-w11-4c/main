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
#include <Windows.h>
#include <iomanip>
//#include <mmsystem.h>
#include <stdlib.h>
#include <fstream>
#include "Logic.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class UI {

private:
	static const int MAX_BUFFER_SIZE = 255;
	static char buffer[MAX_BUFFER_SIZE];
	static const string MESSAGE_COMMAND;
	static const string MESSAGE_WELCOME1;
	static const string MESSAGE_WELCOME2;
	static const string MESSAGE_WELCOME3;
	static const string MESSAGE_WELCOME4;
	static const string MESSAGE_WELCOME5;
	static const string MESSAGE_WELCOME6;
	static const string MESSAGE_COMMANDS_AVAIL;
	static const string MESSAGE_BYE;
	static vector <tuple <int,string, ptime, ptime, string>> UImemory;
	


public:

	static void main();
	static void defaultView(string, stack <string>, string, string);
	static void displayLine( string);
	void getStatus(bool status);
	static string lowerCase(string);
	static string getMonthIndex(string);
	static void displayUI(string);
	static vector <pair <int, int>> indexPair;
	static void setColour(int);
	static string prepareTaskDay(vector<string>);
	static string prepareByEndHourEndMin(vector<string>);
	static string prepareStartHourStartMin(vector<string>);
	static string prepareEndHourEndMin(vector<string>);
	static bool isFloating(vector <string>);
	static bool isDeadline(vector <string>);
	static bool isTimeTask1(vector <string>); //only has end hour and min
	static bool isTimeTask2(vector <string>); // start hour, start min, end hour, end min
	static void prepareUImemory(string);
	static bool noTasksToday(date, string);
	static void printJarvis();
	static bool emptyFileFirstRun(string);
	static bool noDateTasks(string);
	static void displayDone();
};

#endif