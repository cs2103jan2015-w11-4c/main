#ifndef UI_H
#define UI_H

#include <string>
using namespace std;

class Task {

private:
	string _read;
	string _display;
	const string added, deleted, edited;

public:
	void readLine(string);
	void getStatus(bool status);
	void display();
}

#endif