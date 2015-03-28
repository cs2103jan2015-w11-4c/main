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
	void setKeywords(string);
	string getKeywords();
	stack <string> getStack();
	void setStack(stack <string>);
	string getUndoString();
	void setUndoString(string);
};
#endif