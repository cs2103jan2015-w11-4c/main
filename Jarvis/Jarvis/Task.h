#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task {

private:
	string description;
	string taskNumber;
	string updatedDescription;

public:
	void setDescription(string);
	string getDescription();
	void setNumber(string);
	string getNumber();
	void setUpdated(string);
	string getUpdated();
};

#endif