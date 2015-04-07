#include "Add.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

Add::Add(Task TaskAttributes,RecurringTask recurringObject) {
	T1=TaskAttributes;
	R1=recurringObject;
}

Add::~Add() {

}

int Add::getMonthNumber(string name) {

	map<string, int> months;
	map<string,int>::iterator iter;

		months["january"]=1;
		months["february"]=2;
		months["march"]=3;
		months["april"]=4;
		months["may"]=5;
		months["june"]=6;
		months["july"]=7;
		months["august"]=8;
		months["september"]=9;
		months["october"]=10;
		months["november"]=11;
		months["december"]=12;

	 iter = months.find(name);

	if (iter != months.end())
		return iter->second;
	return 0;
}

string Add::getMonthFromNumber(int no) {

	map<int, string> months;
	map<int,string>::iterator iter;

		months[1]="january";
		months[2]="february";
		months[3]="march";
		months[4]="april";
		months[5]="may";
		months[6]="june";
		months[7]="july";
		months[8]="august";
		months[9]="september";
		months[10]="october";
		months[11]="november";
		months[12]="december";

	 iter = months.find(no);

	if (iter != months.end())
		return iter->second;
	return "";
}

int Add::getDayNumber(string name) {

	map<string,int>dayName;
	map<string,int>::iterator iter;

		dayName["monday"]=1;
		dayName["tuesday"]=2;
		dayName["wednesday"]=3;
		dayName["thursday"]=4;
		dayName["friday"]=5;
		dayName["saturday"]=6;
		dayName["sunday"]=0;

	 iter = dayName.find(name);

	if (iter != dayName.end())
		return iter->second;
	return 7;
} 


string Add::execute(string fileName,string filePath) {
	
	string status;
	bool statusOfAdd;
	if(R1.getRecurring()) {
		if(R1.getRecurringError())
			return "Error: Invalid form of recurring task.";
		else if(R1.getWord()=="until") {
			if(R1.getTaskDay()=="day") {
				ptime now = microsec_clock::local_time();
				date today = now.date();
				int gregYear = 2015;
				int gregMonth = getMonthNumber(R1.getEndMonth());
				int gregDate = stoi(R1.getEndDate());
				date end(gregYear, gregMonth, gregDate);
				date_duration dd(1);
				while(today<=end) {
					T1.setDate(to_string(today.day()));
					T1.setMonth(getMonthFromNumber(today.month()));
					T1.setYear(to_string(today.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					today = today + dd;
				}

			}

			else {
				ptime now = microsec_clock::local_time();
				string dayName = T1.getKeywords();
				date today = now.date();
				greg_weekday gregDay = getDayNumber(R1.getTaskDay());
				first_day_of_the_week_after fdaf(gregDay);
				date day = fdaf.get_date(date(today));
				int gregYear = 2015;
				int gregMonth = getMonthNumber(R1.getEndMonth());
				int gregDate = stoi(R1.getEndDate());
				date end(gregYear, gregMonth, gregDate);
				first_day_of_the_week_before fdbf(gregDay);
				date lastDay = fdbf.get_date(date(end));
				date_duration dd(7);
				while(day<=lastDay) {
					T1.setDate(to_string(day.day()));
					T1.setMonth(getMonthFromNumber(day.month()));
					T1.setYear(to_string(day.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					day = day + dd;
				}
			}
			if(statusOfAdd) {
				status = "Added recurring task successfully\n";
			}
			else { 
				status= "Error: Could not add recurring task\n";
			}
		}

		else {
			char number =(R1.getWord()).at(1);
			int recurringNumber =number - '0';
			//cout << recurringNumber << endl;
			//cout << R1.getTaskDay() << endl;
			int countOfDays=0;
			if(recurringNumber>0) {
				if(R1.getTaskDay()=="day") {
				ptime now = microsec_clock::local_time();
				date today = now.date();
				date_duration dd(1);
				while(countOfDays<=recurringNumber) {
					
					T1.setDate(to_string(today.day()));
					T1.setMonth(getMonthFromNumber(today.month()));
					T1.setYear(to_string(today.year()));
					cout << T1.getDate() << endl;
					cout << T1.getMonth() << endl;
					cout << T1.getYear() << endl;
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					countOfDays++;
					today = today + dd;
				}
				}

			else {
				ptime now = microsec_clock::local_time();
				string dayName = T1.getKeywords();
				date today = now.date();
				greg_weekday gregDay = getDayNumber(R1.getTaskDay());
				first_day_of_the_week_after fdaf(gregDay);
				date day = fdaf.get_date(date(today));
				date_duration dd(7);
				while(countOfDays<recurringNumber) {
					T1.setDate(to_string(day.day()));
					T1.setMonth(getMonthFromNumber(day.month()));
					T1.setYear(to_string(day.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					countOfDays++;
					day = day + dd;
				}
			}

			}
			else {
				return "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";

			}
			if(statusOfAdd) {
				status = "Added recurring task successfully\n";
			}
			else { 
				status= "Error: Could not add recurring task\n";
			}

		}
	}

	else if(!R1.getRecurring()) {
	if(R1.getRecurringError()) 
		return "Error: Invalid date entered for task. Please enter a valid date\n";
	if(T1.getErrorDate())
		return "Error: Invalid date entered for task. Please enter a valid date\n";
	if(T1.getCommandError()) 
		return "Error: Invalid format of task. Please enter a valid format\n";
	if(T1.getTimeError())
		return "Error: Invalid time entered for task. Please enter a valid time in the 24 hour clock\n";
 	bool statusOfAdd = S1.writeFile(T1,fileName,filePath);
	if(statusOfAdd) {
		status = "Added successfully\n";
	}
	else { 
		status= "Error: Could not add task\n";
	}
	
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
		return "Error: Error occured when doing undo. Please try again";
}


