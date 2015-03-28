#include "Add.h"

using namespace std;

Add::Add(Task TaskAttributes) {
	T1=TaskAttributes;
}

Add::~Add() {

}

string Add::execute(string fileName,string filePath) {
	
	string status;
	bool statusOfAdd = S1.writeFile(T1,fileName,filePath);
	if(statusOfAdd) {
		status = "Added successfully\n";
	}
	else { 
		status= "Error in adding\n";
	}
	return status;

}

string Add::executeUndo(string fileName,string filePath) {
	Delete D1(T1);
	string data = D1.getDeleteTask();
	bool status = S1.writeBackToFile(data,fileName,filePath);
	if(status)
		return "The task *" + D1.getDeleteTask() + "* has been added back";
	else
		return "Error occured when doing undo. Please try again";
}


