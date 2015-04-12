#ifndef UPDATE_H
#define UPDATE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Parser.h"
#include "Logic.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

class Update:public Command {

private:
	Storage S1;
	Task T1;
	static string originalTask;
	static string updatedTask;
	string userNumber;
	string category;
	bool isWrongTaskFormat;
	bool isWrongDateFormat;
	bool isWrongTimeFormat;
	bool isDatePassed;
	bool isInvalidTimePeriod;


public:
	Update(Task);
	~Update();
	string execute(string,string);
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
	void setOriginalTask(string);
	string getOriginalTask();
	void setUpdatedTask(string);
	string getUpdatedTask();
	string lowerCase(string);
	bool isValidCommand(string);
	int getLineNumber(vector <string>);
	string getCategory(vector <string>);
	bool updateTask(string,int,string,vector<string>,string&,string&);
	bool updateDate(string,int,string,vector<string>,string&,string&);
	bool updateTime(string,int,string,vector<string>,string&,string&);
	void performUpdate(string, string, string, string);
	int convertStringToInt(string);
	int getMonthNumber(string);
	bool checkDateMonth(string, string);
	bool checkDateMonthYear(string, string,string);
	bool checkByTime(string,string&,string&);
	bool checkTime(string,string,string,string&,string&,string&,string&);
	bool isHourValid(string);
	bool isMinuteValid(string);
};

#endif
