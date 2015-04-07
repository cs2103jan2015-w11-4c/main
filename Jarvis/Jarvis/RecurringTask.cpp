#include "RecurringTask.h"

RecurringTask::RecurringTask() {
	isRecurring=false;
	isRecurringError=false;
	taskDay="";
	endDate="";
	endMonth="";
	endYear="2015";

}
RecurringTask::~RecurringTask() {


}


bool RecurringTask::getRecurringError() {
	return isRecurringError;

}

bool RecurringTask::getRecurring() {
	return isRecurring;
}

void RecurringTask::setRecurringError(bool value){
	isRecurringError=value;
}

void RecurringTask::setRecurring(bool value) {
	isRecurring=value;
}

void RecurringTask::setEndDate(string date) {
	endDate = date;
}

string RecurringTask::getEndDate() {
	return endDate;
}

void RecurringTask::setEndMonth(string month) {
	endMonth = month;
}

string RecurringTask::getEndMonth() {
	return endMonth;
}

void RecurringTask::setTaskDay(string day) {
	taskDay = day;
}

string RecurringTask::getTaskDay() {
	return taskDay;
}

string RecurringTask::getEndYear() {
	return endYear;
}

void RecurringTask::setEndYear(string year) {
	endYear = year;
}

void RecurringTask::setWord(string word) {
	keyword=word;
}

string RecurringTask::getWord() {
	return keyword;
}