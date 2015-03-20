#include "Task.h"


void Task::setDescription(string input) {
	description = input;
}
	

string Task::getDescription() {
	return description;
}

void Task::setNumber(string input) {
	taskNumber = input;
}

string Task::getNumber() {
	return taskNumber;
}

void Task::setUpdated(string newString) {
	updatedDescription = newString; 
}

string Task::getUpdated() {
	return updatedDescription;
}