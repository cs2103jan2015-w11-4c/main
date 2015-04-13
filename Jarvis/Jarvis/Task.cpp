#include "Task.h"

using namespace std;

Task::Task() {
	description = "";
	taskNumber = "";
	updatedDescription = "";
	taskDate = "";
	taskMonth = "";
	taskYear = "2015";
	taskKeywords = "";
	undoString = "";
	taskHour="";
	taskMinute="";
	taskStartHour="";
	taskStartMinute="";
	taskEndHour="";
	taskEndMinute="";
	taskStatus = "incomplete"; //default incomplete priorty, change be changed to High or Done (check off the list)
	isErrorDate=false;
	isCommandError=false;
	isTimeError=false;
	isBlankString=false;
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

void Task::setHour(string hour){
	taskHour = hour;
}

string Task::getHour()
{
	return taskHour;
}

void Task::setMinute(string minute){
	taskMinute = minute;
}

string Task::getMinute()
{
	return taskMinute;
}

void Task::setStartHour(string StartHour){
	taskStartHour = StartHour;
}

string Task::getStartHour()
{
	return taskStartHour;
}

void Task::setStartMinute(string StartMinute){
	taskStartMinute = StartMinute;
}

string Task::getStartMinute()
{
	return taskStartMinute;
}

void Task::setEndMinute(string minute) {
	taskEndMinute = minute;

}

string Task::getEndMinute() {
	return taskEndMinute;
}

void Task::setEndHour(string EndHour){
	taskEndHour = EndHour;
}


string Task::getEndHour()
{
	return taskEndHour;
}

void Task::setStatus(string Status){
	taskStatus = Status;
}

string Task::getStatus()
{
	return taskStatus;
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
	inputStack = input;
}

void Task::setUndoString(string undo) {
	undoString = undo;
}

string Task::getUndoString() {
	return undoString;
}

void Task::setErrorDate(bool value) {
	isErrorDate = value;
}

bool Task::getErrorDate() {
	return isErrorDate;
}

bool Task::getCommandError() {

	return isCommandError;
}

void Task::setCommandError(bool value) {
	isCommandError=value;

}

bool Task::getTimeError() {

	return isTimeError;
}

void Task::setTimeError(bool value) {
	isTimeError=value;

}

vector <string> Task::getUpdateTokens() {
	return updateTokens;
}

void Task::setUpdateTokens(vector <string> input) {
	updateTokens=input;
}

bool Task::getBlankString() {
	return isBlankString;
}

void Task::setBlankString(bool value) {
	isBlankString=value;
}
