//@author A0118904E
#include "Add.h"
#include "Assert.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string ERROR_BLANK_STRING = "Error: Task to be added cannot be empty. Please enter *ADD* followed by a task\n";
const string ERROR_END_LESSTHAN_START = "Error: Please enter a start date for the task that comes after today's date\n";
const string ERROR_DAY_LESSTHAN_START1 = "Error: Recurring task could not be added since no ";
const string ERROR_DAY_LESSTHAN_START2 = " comes before ";
const string MONTH_1 = "january";
const string MONTH_2 = "february";
const string MONTH_3 = "march";
const string MONTH_4 = "april";
const string MONTH_5 = "may";
const string MONTH_6 = "june";
const string MONTH_7 = "july";
const string MONTH_8 = "august";
const string MONTH_9 = "september";
const string MONTH_10 = "october";
const string MONTH_11 = "november";
const string MONTH_12 = "december";
const string DAY_1 = "monday";
const string DAY_2 = "tuesday";
const string DAY_3 = "wednesday";
const string DAY_4 = "thursday";
const string DAY_5 = "friday";
const string DAY_6 = "saturday";
const string DAY_0 = "sunday";
const string SUCCESS_RECURRING = "Added recurring task successfully\n";
const string ERROR_RECURRING = "Error: Could not add recurring task\n";
const string ERROR_INVALID_OCCURENCES = "Error: Recurring Task could not be added.\nPlease specify a valid number of occurences\n";
const string ERROR_PAST_DATE = "Error: Recurring Task could not be added.\n Please make sure the start date of recurrence comes before the end date of recurrence.\n";
const string ERROR_INVALID_DATE ="Error: Invalid date entered for task. Please enter a valid date\n"; 
const string ERROR_INVALID_RECURRING = "Error: Invalid form of recurring task\n";
const string ERROR_COMMAND = "Error: Invalid format of task. Please enter a valid format\n";
const string ERROR_TIME = "Error: Invalid time entered for task. Please enter a valid time in the 24 hour clock\n";
const string ERROR_ADD = "Error: Could not add the task.\n";
const string SUCCESS_ADD = "Added task successfully to the tasklist!\n";
const string UNDO_ERROR = "Error: Error occured when doing undo. Please try again";

Add::Add(Task TaskAttributes,RecurringTask recurringObject) {
	T1=TaskAttributes;
	R1=recurringObject;
}

Add::~Add() {

}

//Returns the integer conversion of the month
//Used to check if the date entered is valid
int Add::getMonthNumber(string name) {

	map<string, int> months;
	map<string,int>::iterator iter;

		months[MONTH_1]=1;
		months[MONTH_2]=2;
		months[MONTH_3]=3;
		months[MONTH_4]=4;
		months[MONTH_5]=5;
		months[MONTH_6]=6;
		months[MONTH_7]=7;
		months[MONTH_8]=8;
		months[MONTH_9]=9;
		months[MONTH_10]=10;
		months[MONTH_11]=11;
		months[MONTH_12]=12;

	 iter = months.find(name);

	if (iter != months.end())
		return iter->second;
	return 0;
}

//Returns the month name corresponding to the number of the month
//Used to store the data into the file
string Add::getMonthFromNumber(int no) {

	map<int, string> months;
	map<int,string>::iterator iter;

		months[1]=MONTH_1;
		months[2]=MONTH_2;
		months[3]=MONTH_3;
		months[4]=MONTH_4;
		months[5]=MONTH_5;
		months[6]=MONTH_6;
		months[7]=MONTH_7;
		months[8]=MONTH_8;
		months[9]=MONTH_9;
		months[10]=MONTH_10;
		months[11]=MONTH_11;
		months[12]=MONTH_12;

	 iter = months.find(no);

	if (iter != months.end())
		return iter->second;
	return "";
}

//Returns the integer conversion of the day of the week eg. monday is day1, sunday is day0
//Used to check if the date entered is valid
int Add::getDayNumber(string name) {

	map<string,int>dayName;
	map<string,int>::iterator iter;

		dayName[DAY_1]=1;
		dayName[DAY_2]=2;
		dayName[DAY_3]=3;
		dayName[DAY_4]=4;
		dayName[DAY_5]=5;
		dayName[DAY_6]=6;
		dayName[DAY_0]=0;

	 iter = dayName.find(name);

	if (iter != dayName.end())
		return iter->second;
	return 7;
} 


string Add::execute(string fileName,string filePath) {
	int countOfDays=0;
	if(T1.getBlankString()) {                  //The user cannot enter a blank string after "add" command
		return ERROR_BLANK_STRING;
	}
	string status;
	bool statusOfAdd;
	
	//If the task added is a recurring task, it first checks if there is an error in the format of the recurring task added
	//If the task format is valid it checks for the two keywords: every or from
	if(R1.getRecurring()) {
		if(R1.getRecurringError()) {
			return ERROR_INVALID_RECURRING;
		} else if(R1.getRecWord()=="every") {   // The format for this task is add <task> every <day/dayName> (until <deadline>)
			if(R1.getWord()=="until") {                                                                       //no of occurences
				if(R1.getTaskDay()=="day") {
					ptime now = microsec_clock::local_time();
					date today = now.date();
					int gregYear = stoi(T1.getYear());
					int gregMonth = getMonthNumber(R1.getEndMonth());
					int gregDate = stoi(R1.getEndDate());
					date end(gregYear, gregMonth, gregDate);
					assert(end > today);
					if(end<today) {                       //If the date entered is in the past, it is invalid.
						return ERROR_END_LESSTHAN_START;
					}
					date_duration dd(1);
					while(today<=end) {                    //Depending on the end date added, the task is added daily to the tasklist.
						T1.setDate(to_string(today.day()));
						T1.setMonth(getMonthFromNumber(today.month()));
						T1.setYear(to_string(today.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						today = today + dd;
					}

				} else {
					ptime now = microsec_clock::local_time();
					string dayName = T1.getKeywords();
					date today = now.date();
				
					//Gets the date corresponding to the first occurence of the day name. 
					//Example it gets the nearest friday, if the keyword is friday
					greg_weekday gregDay = getDayNumber(R1.getTaskDay());
					first_day_of_the_week_after fdaf(gregDay);
					date day = fdaf.get_date(date(today));
				
					//Gets the end date specified by the user. It checks for the last occurence of the day name before the end date.
					int gregYear = stoi(T1.getYear());
					int gregMonth = getMonthNumber(R1.getEndMonth());
					int gregDate = stoi(R1.getEndDate());
					date end(gregYear, gregMonth, gregDate);
					first_day_of_the_week_before fdbf(gregDay);
					date lastDay = fdbf.get_date(date(end));
					date_duration dd(7);
					if(lastDay<day) {              //If the end date added is in the past, its invalid.
						return ERROR_DAY_LESSTHAN_START1 + R1.getTaskDay() + ERROR_DAY_LESSTHAN_START2 + to_string(gregDay) + " " + getMonthFromNumber(gregMonth) + " " + to_string(gregYear) + "\n";
					}
					while(day<=lastDay) {          //Adds the task every 7 days
						T1.setDate(to_string(day.day()));
						T1.setMonth(getMonthFromNumber(day.month()));
						T1.setYear(to_string(day.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						day = day + dd;
					}
				}
			if(statusOfAdd) {
				status = SUCCESS_RECURRING;
			} else { 
				status= ERROR_RECURRING;
			}

		} else {                                  //If the number of occurences are specified eg. "x2"
			char number =(R1.getWord()).at(1);
			int recurringNumber =number - '0';
			int countOfDays=0;
			if(recurringNumber>0) {              //Negative number of recurrences are invalid
				if(R1.getTaskDay()=="day") {
					ptime now = microsec_clock::local_time();
					date today = now.date();
					date_duration dd(1);
					while(countOfDays<=recurringNumber) {    //Depending on the number of occurences, the task is added daily to the tasklist.
						T1.setDate(to_string(today.day()));
						T1.setMonth(getMonthFromNumber(today.month()));
						T1.setYear(to_string(today.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						today = today + dd;
					}
				} else {
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

			} else {
				return ERROR_INVALID_OCCURENCES;
			}
			if(statusOfAdd) {
				status = SUCCESS_RECURRING;
			} else { 
				status= ERROR_RECURRING;
			}
			return status;
		}
	} else if(R1.getRecWord()=="from") {              // The format for this task is add <task> from <deadline> (until <deadline>) OR (no of occurences)
		
		string recPeriod = R1.getPeriod();
		string word = R1.getWord();
		int startDate = stoi(R1.getStartDate());
		int startMonth = getMonthNumber(R1.getStartMonth());
		int startYear = stoi(R1.getStartYear());
		date start(startYear, startMonth, startDate);  //This is the date from which task should start recurring
		if(recPeriod=="daily") {
			if(word=="until") {
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end) {
					return ERROR_PAST_DATE;
				}
				date_duration dd(1);
				while(start<=end) {            //Adds the task daily until end date is reached 
				T1.setDate(to_string(start.day()));
				T1.setMonth(getMonthFromNumber(start.month()));
				T1.setYear(to_string(start.year()));
				statusOfAdd = S1.writeFile(T1,fileName,filePath);
				start = start + dd;
				}

			} else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
				date_duration dd(1);
				if(recurringNumber>0) {
					while(countOfDays<=recurringNumber) {
						T1.setDate(to_string(start.day()));
						T1.setMonth(getMonthFromNumber(start.month()));
						T1.setYear(to_string(start.year()));
						statusOfAdd = S1.writeFile(T1,fileName,filePath);
						countOfDays++;
						start = start + dd;
					}
				} else {
					return ERROR_INVALID_OCCURENCES;
				}
			}

		} else if(recPeriod=="weekly") {                    //Task is added weekly until end date is reached
			if(word=="until") {
				date_duration dd(7);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end) {
					return ERROR_PAST_DATE;
				}
				while(start<=end) {
					T1.setDate(to_string(start.day()));
					T1.setMonth(getMonthFromNumber(start.month()));
					T1.setYear(to_string(start.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					start = start + dd;
				}

			} else {
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
					return ERROR_INVALID_OCCURENCES;
				}
			}
		} else if(recPeriod=="monthly") {     //Task is added monthly until end date is reached
			if(word=="until") {
				months single(1);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end) {
					return ERROR_PAST_DATE;
				}
				while(start<=end) {
					T1.setDate(to_string(start.day()));
					T1.setMonth(getMonthFromNumber(start.month()));
					T1.setYear(to_string(start.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					start = start + single;
				}

			} else {
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
				} else {
					return ERROR_INVALID_OCCURENCES;
				}
			}
		} else {                                            //Task is added yearly until end date is reached
			if(word=="until") {
				years single(1);
				int endDate = stoi(R1.getEndDate());
				int endMonth = getMonthNumber(R1.getEndMonth());
				int endYear = stoi(T1.getYear());
				date end(endYear, endMonth, endDate);
				if(start>end) {
					return ERROR_PAST_DATE;
				}
				while(start<=end) {
					T1.setDate(to_string(start.day()));
					T1.setMonth(getMonthFromNumber(start.month()));
					T1.setYear(to_string(start.year()));
					statusOfAdd = S1.writeFile(T1,fileName,filePath);
					start = start + single;
				}

			} else {
				char number =(R1.getWord()).at(1);
				int recurringNumber =number - '0';
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
				} else {
					return ERROR_INVALID_OCCURENCES;
				}
			}
		}

		if(statusOfAdd) {
			status = SUCCESS_RECURRING;
		} else { 
			status= ERROR_RECURRING;
		}
		return status;
		}
	} else if(!R1.getRecurring()) { //If the task is not recurring, it checks for all possible errors before adding to storage
		if(R1.getRecurringError()) {
			return ERROR_INVALID_RECURRING;
		} else if(T1.getErrorDate()) {
			return ERROR_INVALID_DATE;
		} else if(T1.getCommandError()) {
			return ERROR_COMMAND;
		} else if(T1.getTimeError()) {
			return ERROR_TIME;
		}
 		bool statusOfAdd = S1.writeFile(T1,fileName,filePath);
		if(statusOfAdd) {
			status = SUCCESS_ADD;
		} else { 
			status= ERROR_ADD;
		}
	}
	return status;
}

//This is used to add the last deleted task. Function is called in undo

string Add::executeUndo(string fileName,string filePath) {
	Delete D1(T1);
	string data = D1.getDeleteTask();    //the last task deleted is retrieved
	bool status = S1.writeBackToFile(data,fileName,filePath);
	if(status) {
		return "The task *" + D1.getDeleteTask() + "* has been added back";
	} else {
		return UNDO_ERROR;
	}
}


