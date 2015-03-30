#ifndef TASK_H
#define TASK_H

#include <string>
#include <stack>
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

	string taskKeywords;
	stack <string> inputStack;
	string undoString;

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

	void setKeywords(string);
	string getKeywords();
	stack <string> getStack();
	void setStack(stack <string>);
	string getUndoString();
	void setUndoString(string);
};
#endif