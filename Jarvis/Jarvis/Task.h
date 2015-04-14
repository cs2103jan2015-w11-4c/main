//@author A0118904E
#ifndef TASK_H
#define TASK_H


#include <string>
#include <stack>
#include <vector>
using namespace std;

class Task {

private:
	string description;
	string taskNumber;
	string updatedDescription;
	string taskDate;
	string taskMonth;
	string taskYear;
	string taskHour;
	string taskMinute;
	string taskStartHour;
	string taskStartMinute;
	string taskEndHour;
	string taskEndMinute;
	string taskStatus;
	bool isErrorDate;
	bool isCommandError;
	bool isTimeError;
	vector <string> updateTokens;
	string taskKeywords;
	stack <string> inputStack;
	string undoString;
	bool isBlankString;

public:
	Task();
	~Task();
	void setDescription(string);
	string getDescription();
	void setNumber(string);
	string getNumber();
	void setUpdated(string);
	string getUpdated();
	void setDate(string);
	string getDate();
	void setMonth(string);
	string getMonth();
	void setYear(string);
	string getYear();
	void setHour(string);
	string getHour();
	void setMinute(string);
	string getMinute();
	void setStartHour(string);
	string getStartHour();
	void setStartMinute(string);
	string getStartMinute();
	void setEndHour(string);
	string getEndHour();
	void setEndMinute(string);
	string getEndMinute();
	void setStatus(string);
	string getStatus();
	void setErrorDate(bool);
	bool getErrorDate();
	void setCommandError(bool);
	bool getCommandError();
	bool getTimeError();
	void setTimeError(bool);
	void setKeywords(string);
	string getKeywords();
	stack <string> getStack();
	void setStack(stack <string>);
	string getUndoString();
	void setUndoString(string);
	vector <string> getUpdateTokens();
	void setUpdateTokens(vector <string>);
	void setBlankString(bool);
	bool getBlankString();
};
#endif
