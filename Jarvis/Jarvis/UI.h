#ifndef UI_H
#define UI_H

#include <string>
using namespace std;

class UI {

private:
	string _read;
	string _display;
	const string ADDED = "Task has been added\n";
	const string DELETED = "Task has been deleted\n";
	const string EDITED = "Task has been edited\n";
	const string WELCOME = "Welcome!";


public:
	void readLine(string);
	void getStatus(bool status);
	void display();
}

#endif