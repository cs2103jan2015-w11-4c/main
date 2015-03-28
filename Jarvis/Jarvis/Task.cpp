#include "Task.h"

using namespace std;

Task::Task() {
	description="";
	taskNumber="";
	updatedDescription="";
	taskDate="";
	taskMonth="";
	taskYear="2015";
	taskKeywords="";
	undoString="";
}

Task::~Task() {

}

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

void Task::setDate(string date) {
	taskDate = date; 
}

string Task::getDate() {
	return taskDate;
}

void Task::setMonth(string month) {
	taskMonth = month; 
}

string Task::getMonth() {
	return taskMonth;
}

void Task::setYear(string year) {
	taskYear = year;
}

string Task::getYear() {
	return taskYear;
}

string Task::getKeywords() {
	return taskKeywords;
}

void Task::setKeywords(string keywords) {
	taskKeywords = keywords;
}

stack <string> Task::getStack() {
	return inputStack;
}

void Task::setStack(stack <string> input) {
	inputStack=input;
}

void Task::setUndoString(string undo) {
	undoString = undo;
}

string Task::getUndoString() {
	return undoString;
}
/*
void Task::setIndex(int userIndex) {
	index = userIndex;
}

int Task::getIndex() {
	return index;
}
*/