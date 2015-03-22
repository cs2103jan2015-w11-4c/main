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


