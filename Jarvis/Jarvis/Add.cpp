#include "Add.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string ERROR_BLANK_STRING = "Error: Task to be added cannot be empty. Please enter *ADD* followed by a task\n";
const string ERROR_END_LESSTHAN_START = "Error: Please enter a start date for the task that comes after today's date";
const string ERROR_DAY_LESSTHAN_START1 = "Error: Recurring task could not be added since no ";
const string ERROR_DAY_LESSTHAN_START2 = " comes before ";

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
	int countOfDays=0;
	if(T1.getBlankString()) {
		return ERROR_BLANK_STRING;
	}
	string status;
	bool statusOfAdd;
	if(R1.getRecurring()) {
		if(R1.getRecurringError())
			return "Error: Invalid form of recurring task.";
		else if(R1.getRecWord()=="every") {
			if(R1.getWord()=="until") {
				if(R1.getTaskDay()=="day") {
					ptime now = microsec_clock::local_time();
					date today = now.date();
					int gregYear = stoi(T1.getYear());
					int gregMonth = getMonthNumber(R1.getEndMonth());
					int gregDate = stoi(R1.getEndDate());
					date end(gregYear, gregMonth, gregDate);
					if(end<today) {
						return ERROR_END_LESSTHAN_START;
					}
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
					cout << R1.getTaskDay() << endl;
					ptime now = microsec_clock::local_time();
					string dayName = T1.getKeywords();
					date today = now.date();
					greg_weekday gregDay = getDayNumber(R1.getTaskDay());
					first_day_of_the_week_after fdaf(gregDay);
					date day = fdaf.get_date(date(today));
					int gregYear = stoi(T1.getYear());
					int gregMonth = getMonthNumber(R1.getEndMonth());
					int gregDate = stoi(R1.getEndDate());
					date end(gregYear, gregMonth, gregDate);
					first_day_of_the_week_before fdbf(gregDay);
					date lastDay = fdbf.get_date(date(end));
					date_duration dd(7);
					if(lastDay<day) {
						return ERROR_DAY_LESSTHAN_START1 + R1.getTaskDay() + ERROR_DAY_LESSTHAN_START2 + to_string(gregDay) + " " + getMonthFromNumber(gregMonth) + " " + to_string(gregYear) + "\n";
					}
					while(day<=lastDay) {
						T1.setDate(to_string(day.day()));
						T1.setMonth(getMonthFromNumber(day.month()));
						T1.setYear(to_string(day.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						cout << "yes" << endl;
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
			cout << "yep" << endl;
			if(recurringNumber>0) {
				
				if(R1.getTaskDay()=="day") {
				ptime now = microsec_clock::local_time();
				date today = now.date();
				date_duration dd(1);
				while(countOfDays<=recurringNumber) {
					
					T1.setDate(to_string(today.day()));
					T1.setMonth(getMonthFromNumber(today.month()));
					T1.setYear(to_string(today.year()));
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
			return status;

		}
	}
	else if(R1.getRecWord()=="from") {
		cout << "YES" << endl;
		int startDate = stoi(R1.getStartDate());
		int startMonth = getMonthNumber(R1.getStartMonth());
		int startYear = stoi(R1.getStartYear());
		
		string recPeriod = R1.getPeriod();
		string word = R1.getWord();
		date start(startYear, startMonth, startDate);
		if(recPeriod=="daily") {
			if(word=="until") {
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end)
					return "Error: Recurring Task could not be added.\n Please make sure the start date of recurrence comes before the end date of recurrence.\n";
				date_duration dd(1);
				while(start<=end) {
				T1.setDate(to_string(start.day()));
				T1.setMonth(getMonthFromNumber(start.month()));
				T1.setYear(to_string(start.year()));
				statusOfAdd = S1.writeFile(T1,fileName,filePath);
				start = start + dd;
				}

			}
			else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
				cout << "rec1" << endl;
				date_duration dd(1);
				if(recurringNumber>0) {
					while(countOfDays<=recurringNumber) {
						cout << "rec2" << endl;
						T1.setDate(to_string(start.day()));
						T1.setMonth(getMonthFromNumber(start.month()));
						T1.setYear(to_string(start.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						start = start + dd;
				}
				}
				else {
					return "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";
				}
			}

		}
		else if(recPeriod=="weekly") {
			if(word=="until") {
				date_duration dd(7);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end)
					return "Error: Recurring Task could not be added.\n Please make sure the start date of recurrence comes before the end date of recurrence.\n";
				while(start<=end) {
				T1.setDate(to_string(start.day()));
				T1.setMonth(getMonthFromNumber(start.month()));
				T1.setYear(to_string(start.year()));
				statusOfAdd = S1.writeFile(T1,fileName,filePath);
				start = start + dd;
				}

		}
			else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
				date_duration dd(7);
				if(recurringNumber>0) {
					while(countOfDays<=recurringNumber) {
					
						T1.setDate(to_string(start.day()));
						T1.setMonth(getMonthFromNumber(start.month()));
						T1.setYear(to_string(start.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						start = start + dd;
					}
				}
				else {
					return "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";
				}
			}


		}
		else if(recPeriod=="monthly") {
			if(word=="until") {
				months single(1);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end)
					return "Error: Recurring Task could not be added.\n Please make sure the start date of recurrence comes before the end date of recurrence.\n";
				while(start<=end) {
				T1.setDate(to_string(start.day()));
				T1.setMonth(getMonthFromNumber(start.month()));
				T1.setYear(to_string(start.year()));
				statusOfAdd = S1.writeFile(T1,fileName,filePath);
				start = start + single;
				}

		}
			else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
				months single(1);
				if(recurringNumber>0) {
					while(countOfDays<=recurringNumber) {
					
						T1.setDate(to_string(start.day()));
						T1.setMonth(getMonthFromNumber(start.month()));
						T1.setYear(to_string(start.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						start = start + single;
					}
				}
				else {
					return "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";
				}
			}


		}
		else { //yearly
			if(word=="until") {
				years single(1);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end)
					return "Error: Recurring Task could not be added.\n Please make sure the start date of recurrence comes before the end date of recurrence.\n";
				while(start<=end) {
				T1.setDate(to_string(start.day()));
				T1.setMonth(getMonthFromNumber(start.month()));
				T1.setYear(to_string(start.year()));
				statusOfAdd = S1.writeFile(T1,fileName,filePath);
				start = start + single;
				}

		}
			else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
				int countOfDays;
				years single(1);
				if(recurringNumber>0) {
					while(countOfDays<=recurringNumber) {
					
						T1.setDate(to_string(start.day()));
						T1.setMonth(getMonthFromNumber(start.month()));
						T1.setYear(to_string(start.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						start = start + single;
					}
				}
				else {
					return "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";
				}
			}

		}

	if(statusOfAdd) {
				status = "Added recurring task successfully\n";
			}
			else { 
				status= "Error: Could not add recurring task\n";
			}
			/*cout << R1.getRecurring() << endl;
			cout << R1.getRecurringError() << endl;
			cout << R1.getTaskDay() << endl;
			cout << R1.getEndDate() << endl;
			cout << R1.getEndMonth() << endl;
			cout << R1.getEndYear() << endl;
			cout << T1.getYear() << endl;
			cout << R1.getStartDate() << endl;
			cout << R1.getStartMonth() << endl;
			cout << R1.getStartYear() << endl;
			cout << R1.getWord() << endl;
			cout << T1.getDescription() << endl;
			cout << R1.getRecWord() << endl;
			cout << R1.getPeriod() << endl;
			cout << T1.getStartHour() << endl;
			cout << T1.getStartMinute() << endl;
			cout << T1.getEndHour() << endl;
			cout << T1.getEndMinute() << endl;
			cout << T1.getHour() << endl;
			cout << T1.getMinute() << endl;*/
	return status;

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


