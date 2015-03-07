#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task {

private:
	string description;


public:
	void setDescription(string);
	void getDescription();

}

#endif