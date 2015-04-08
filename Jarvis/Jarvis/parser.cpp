#include "Parser.h"
#include "RecurringTask.h"
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

//string CommandParser::userInput = "";
const string INDENTIFIERS = "./?! ";
const string CommandParser::startDateIndicator = " on ";
const string CommandParser::endTimeIndicator = " by ";
const string CommandParser::hourIndicator = ":";
const string CommandParser::startTimeIndicator = "from";
const string CommandParser::deadlineTimeIndicator = "to";

Task CommandParser::getTaskObject() {
	return taskDetails;
}

string CommandParser::getUserInput() {
	return userInput;
}

int CommandParser::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int CommandParser::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string CommandParser::changeToLowerCase(string input) {
	string lowerCase="";
	for(int i=0;i<input.size();i++) {
		if(input[i]>='A' && input[i]<='Z') {
			input[i] = tolower(input[i]);
			lowerCase = lowerCase + input[i];
		}
		else {
			lowerCase = lowerCase + input[i];
		}
	}
	return lowerCase;
}

string CommandParser::extractUserCommand(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	userInput =input.substr(end+1);

	return input.substr(start,end-start);
}

int CommandParser::findKeywordPosition(string searchString, string keyWord) {
	int lenString = searchString.size();
	int lenWord = keyWord.size();
	std::string::iterator it(searchString.begin()), end(searchString.end());
	std::string::iterator s_it(keyWord.begin()), s_end(keyWord.end());
	it = std::search(it, end, s_it, s_end);

	while(it!=(end-1))
{
	if(searchString.at(*(it-1)==' ') && searchString.at(*(it+lenWord)==' ')) {
		return distance(searchString.begin(),it);
	}
	else
		advance(it, distance(s_it, s_end));
		it = search(it, end, s_it, s_end);

}

		return 0;


}

int CommandParser::getMonthNumber(string name) {

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


bool CommandParser::isHourValid(string hour) {
	try{
		int number = stoi(hour);
		if(number>=0 && number<=23){
			return true;
		}
		else
			return false;
	}
	catch(const std::invalid_argument) {

		return false; 

	}
}

bool CommandParser::isMinuteValid(string minute) {
	try{
		int number = stoi(minute);
		if(number>=0 && number<=59){
			return true;
		}
		else
			return false;
	}
	catch(const std::invalid_argument) {

		return false; 

	}
}

bool CommandParser::isDayValid(string taskDay) {
	if(taskDay=="day" || taskDay=="monday" || taskDay=="tuesday" || taskDay=="wednesday" || taskDay=="thursday" || taskDay=="friday" || taskDay=="saturday" || taskDay=="sunday")
		return true;
	else 
		return false;

}

bool CommandParser::isTimeValid(time_duration t){
	ptime now = microsec_clock::local_time();
	time_duration tod = now.time_of_day();
	if(t>tod)
		return true;
	else
		return false;

}




Task CommandParser::parseString(string userInput, RecurringTask &R1) {
	string desc;
	string date;
	string month;
	string hour;
	string minute;
	string StartHour;
	string StartMinute;
	string EndHour;
	string EndMinute;
	string str = "on";
	ptime now = microsec_clock::local_time();
	time_duration tod = now.time_of_day();
	cout << tod << endl;
	int gregDate,gregMonth,gregYear=2015;
	bool deadline,floating,timedBy,timedFrom,recurring=false;
	boost::trim(userInput);
	vector <string> tokens;
	vector <string> tokensBeforeTrim;
	vector <string> originalTokens;
	Task T1;
	int i;
	boost::split(tokensBeforeTrim,userInput,boost::is_any_of(" "));                 //split by occurences of " "
	for(i=0;i<tokensBeforeTrim.size();i++) {
		if(tokensBeforeTrim[i].find_first_not_of(' ') != string::npos) {
			originalTokens.push_back(tokensBeforeTrim[i]);
			tokens.push_back(changeToLowerCase(tokensBeforeTrim[i]));
		}
	}
	


	//Search for "on" keyword
	for(i=0;i<tokens.size();i++) {
		if(tokens[i]=="on") {                              //checking deadline tasks
			if((i+3)<=tokens.size()) {                         //only date task on 21 march
				try {
					gregDate = stoi(tokens[i+1]);
				}
				catch (const std::invalid_argument) {                  //catches if not deadline task
					deadline = false;
					continue;
				}
	
				gregMonth = getMonthNumber(tokens[i+2]);                            //2 tokens after on, is month
				
				try {                                                            //check if date and numebrs are correct, gregorian converts into numbers
					boost::gregorian::date d(gregYear, gregMonth, gregDate);
					ptime now = microsec_clock::local_time();
					boost::gregorian::date today = now.date();
					if(d<today) {                                          //dont take in dates earlier than current date
						T1.setErrorDate(true);
						deadline=false;
					}
					else {
						deadline=true;
						break;
					}
					}
				catch (std::out_of_range) {
					bool value=true;
					T1.setErrorDate(value);
					deadline=false;
				}
			}
	}

	}
	if(i==tokens.size())                     //if on keyword doesnt exist, then not a deadline task
		deadline=false;                      //end of scanning through tokens, if on keyword doesnt exist, then not a deadline task

	if(deadline) {
		for(int j=0;j<i;j++) {
			desc = desc + originalTokens[j] + " ";                   //description = add buy veggies on 21 march
		}
		T1.setDescription(desc);
		T1.setDate(tokens[i+1]);
		T1.setMonth(tokens[i+2]);
		if((i+3)==tokens.size())
			return T1;                                             //no timed tasks, only date month year



		//in pm/am add buy apples on 1 november by 10:45 pm, or 08:00 am.   1 pm(not yet)
		else if((i+6) == tokens.size()) {                   //TASK : on 21[i+1] march[i+2] by[i+3] 1[i+4] pm[i+5]
			if(tokens[i+3]=="by") {                        //TASK : on 21[i+1] march[i+2] by[i+3] 01:45[i+4] pm[i+5]
				vector <string> byTime;
		/*		size_t found = tokens[i+4].find_first_of(":");
			
				if (found = string::npos) {                   //1pm case
					if (tokens[i+5] == "pm") {
						
						int hourinteger = stoi(byTime[0]);
					hourinteger = hourinteger + 12;
					cout << hourinteger << endl;       

					ostringstream convert;   // stream used for the conversion
					convert << hourinteger;      // insert the textual representation of 'Number' in the characters in the stream
					byTime[0] = convert.str();
					}

				if (isHourValid(byTime[0])) {         //never do byTime.size() == 2 cause if 1 pm is not 2 already
					T1.setHour(byTime[0]);
				}
				else {
					bool value=true;
					T1.setTimeError(value);
				}

				}
			
			else {
				bool value=true;
				T1.setCommandError(value);
			}
				}	

					 //1 pm case ends
*/
				boost::split(byTime,tokens[i+4],boost::is_any_of(":"));       // "1 45"
				if (tokens[i+5] == "pm") {
					int hourinteger = stoi(byTime[0]);
					hourinteger = hourinteger + 12;
					cout << hourinteger << endl;       

					ostringstream convert;   // stream used for the conversion
					convert << hourinteger;      // insert the textual representation of 'Number' in the characters in the stream
					byTime[0] = convert.str();
					
				}
				
				if (isHourValid(byTime[0]) && isMinuteValid(byTime[1])) {         //never do byTime.size() == 2 cause if 1 pm is not 2 already
					T1.setHour(byTime[0]);
					T1.setMinute(byTime[1]);
				}
				else {
					bool value=true;
					T1.setTimeError(value);
				}

			}
			else {
				bool value=true;
				T1.setCommandError(value);
			}
		
			
		}
	
		
	
		//MY TEST END HEHE




		else if((i+5)==tokens.size()) {//by timed task                 //TASK : on 21[i+1] march[i+2] by[i+3] 13:00[i+4]
			if(tokens[i+3]=="by") {
				vector <string> byTime;
				boost::split(byTime,tokens[i+4],boost::is_any_of(":"));            //"13 00" stored in byTime vector
				if(isHourValid(byTime[0]) && isMinuteValid(byTime[1]) && byTime.size()==2) {
					string userTime = byTime[0]+":"+byTime[1]+":00";
					time_duration td(duration_from_string(userTime));
					if(isTimeValid(td)) {
						T1.setHour(byTime[0]);                      //put into task, 13 is hour, time is byTime[1]
						T1.setMinute(byTime[1]);
					}
					else 
						T1.setTimeError(true);
				}
				else {
					bool value=true;
					T1.setTimeError(value);
				}


			}
			else {
				bool value=true;
				T1.setCommandError(value);
			}
	
		}




		//test from from to time start (:

		else if((i+9) == tokens.size()) {                   //add TASK on 21[i+1] march[i+2] from[i+3] 12:00[i+4] pm[i+5] to[i+6] 13:00[i+7] pm[i+8]

			if(tokens[i+3]=="from" && tokens[i+6]=="to") {                        
				vector <string> fromTime;
					boost::split(fromTime,tokens[i+4],boost::is_any_of(":"));       // "1 45"
				if (tokens[i+5] == "pm") {
					int hourinteger = stoi(fromTime[0]);
					hourinteger = hourinteger + 12;
					cout << hourinteger << endl;       

					ostringstream convert;   // stream used for the conversion
					convert << hourinteger;      // insert the textual representation of 'Number' in the characters in the stream
					fromTime[0] = convert.str();
					
				}
                       
				vector <string> toTime;
					boost::split(toTime,tokens[i+7],boost::is_any_of(":"));       // "1 45"
				if (tokens[i+8] == "pm") {
					int hourinteger = stoi(toTime[0]);
					hourinteger = hourinteger + 12;
					cout << hourinteger << endl;       

					ostringstream convert;   // stream used for the conversion
					convert << hourinteger;      // insert the textual representation of 'Number' in the characters in the stream
					toTime[0] = convert.str();
					
				}
			
				
				if(isHourValid(toTime[0]) && isHourValid(fromTime[0]) && isMinuteValid(toTime[1]) && isMinuteValid(fromTime[1])) {
					T1.setEndHour(toTime[0]);
					T1.setEndMinute(toTime[1]);
					T1.setStartHour(fromTime[0]);
					T1.setStartMinute(fromTime[1]);
				}
				else {
					bool value=true;
					T1.setTimeError(value);
				}

			}
			else {
				bool value=true;
				T1.setCommandError(value);
			}
		
			
		}
	
		//test for from to time end







		else if((i+7)==tokens.size()) { // from to timed task
			if(tokens[i+3]=="from" && tokens[i+5]=="to") {                //on 21[i+1] march[i+2] from[i+3] 12:00[i+4] to[i+4] 13:00[i+5]
				vector <string> fromTime;
				boost::split(fromTime,tokens[i+4],boost::is_any_of(":"));
				
				vector <string> toTime;
				boost::split(toTime,tokens[i+6],boost::is_any_of(":"));
				if(isHourValid(toTime[0]) && isHourValid(fromTime[0]) && isMinuteValid(toTime[1]) && isMinuteValid(fromTime[1]) && fromTime.size()==2 && toTime.size()==2) {
					string userStartTime = fromTime[0]+":"+fromTime[1]+":00";
					time_duration tdStart(duration_from_string(userStartTime));
					string userEndTime = toTime[0]+":"+toTime[1]+":00";
					time_duration tdEnd(duration_from_string(userEndTime));
					if(isTimeValid(tdStart)&&isTimeValid(tdEnd)) {
					T1.setEndHour(toTime[0]);
					T1.setEndMinute(toTime[1]);
					T1.setStartHour(fromTime[0]);
					T1.setStartMinute(fromTime[1]);
					}
					else
						T1.setTimeError(true);

				}

				else {
					bool value=true;
					T1.setTimeError(value);
				}


			}

			else {
				bool value=true;
				T1.setCommandError(value);
			}

			 //function ends
		}
		else {                          //error in format of input 
			bool value=true;
			T1.setCommandError(value);
			return T1;
		}
	
	
	
	
	}               //closing deadline tasks

	else if(!deadline && !T1.getErrorDate()) {
		int a;
		for(a=0;a<tokens.size();a++) {                        //recurring task add buy apples every friday by
			 if(tokens[a]=="every") { 
				 if((a+2)<=tokens.size() && isDayValid(tokens[a+1])) {
					 if((a+5)==tokens.size() && tokens[a+2]=="until"){
							 R1.setWord(tokens[a+2]);
						try {
							gregDate = stoi(tokens[a+3]);
						}
						catch (const std::invalid_argument) {
							recurring = false;
							break;
						}
	
						gregMonth = getMonthNumber(tokens[a+4]);
				
						try {
							boost::gregorian::date d(gregYear, gregMonth, gregDate);
							ptime now = microsec_clock::local_time();
							boost::gregorian::date today = now.date();
							if(d<today) {
								R1.setRecurringError(true);
								R1.setRecurring(false);
							}
							else {
								recurring=true;
								R1.setRecurring(recurring);
							}
							for(int b=0;b<a;b++) {
								desc = desc + originalTokens[b] + " ";
							}
							T1.setDescription(desc);
							R1.setTaskDay(tokens[a+1]);
							R1.setEndDate(tokens[a+3]);
							R1.setEndMonth(tokens[a+4]);
							break;
						}
						catch (std::out_of_range) {
							bool value=true;
							T1.setErrorDate(value);
							recurring=false;
						}

					}
						 
					 else if((a+3)==tokens.size() && (tokens[a+2]).at(0)=='x' && isdigit(tokens[a+2].at(1))) {
							 R1.setWord(tokens[a+2]);
							 for(int b=0;b<a;b++) {
								 desc = desc + originalTokens[b] + " ";
							}
							 T1.setDescription(desc);
							 R1.setTaskDay(tokens[a+1]);
							 R1.setRecurring(true);
							 break;
						}
						
					 else if((a+7)==tokens.size() && tokens[a+2]=="by") {
						vector <string> byRecTime;
						boost::split(byRecTime,tokens[a+3],boost::is_any_of(":"));
						if(byRecTime.size()==2 && isHourValid(byRecTime[0]) && isMinuteValid(byRecTime[1])) {
							string userTime = byRecTime[0]+":"+byRecTime[1]+":00";
							time_duration td(duration_from_string(userTime));
							if(isTimeValid(td)) {
								T1.setHour(byRecTime[0]);
								T1.setMinute(byRecTime[1]);
							}
						else 
							T1.setTimeError(true);
						}

						else {
							bool value=true;
							T1.setTimeError(value);
							return T1;
						}
						if(tokens[a+4]=="until") {
							R1.setWord(tokens[a+4]);
						try {
							gregDate = stoi(tokens[a+5]);
						}
						catch (const std::invalid_argument) {
							R1.setRecurringError(true);
							break;
						}
	
						gregMonth = getMonthNumber(tokens[a+6]);
				
						try {
							boost::gregorian::date d(gregYear, gregMonth, gregDate);
							ptime now = microsec_clock::local_time();
							boost::gregorian::date today = now.date();
							if(d<today) {
								R1.setRecurringError(true);
								R1.setRecurring(false);
							}
							else {
								recurring=true;
								R1.setRecurring(recurring);
							}
							for(int b=0;b<a;b++) {
								desc = desc + originalTokens[b] + " ";
							}
							T1.setDescription(desc);
							R1.setTaskDay(tokens[a+1]);
							R1.setEndDate(tokens[a+5]);
							R1.setEndMonth(tokens[a+6]);
							break;
						}
						catch (std::out_of_range) {
							bool value=true;
							T1.setErrorDate(value);
							recurring=false;
						}



					 }
						
					 }
					
					 else if((a+5)==tokens.size() && (tokens[a+4]).at(0)=='x' && isdigit(tokens[a+4].at(1))) {
							vector <string> byRecTime;
						boost::split(byRecTime,tokens[a+3],boost::is_any_of(":"));
						if(byRecTime.size()==2 && isHourValid(byRecTime[0]) && isMinuteValid(byRecTime[1])) {
							string userTime = byRecTime[0]+":"+byRecTime[1]+":00";
							time_duration td(duration_from_string(userTime));
							if(isTimeValid(td)) {
								T1.setHour(byRecTime[0]);
								T1.setMinute(byRecTime[1]);
							}
							else 
								T1.setTimeError(true);
						}

						else {
							bool value=true;
							T1.setTimeError(value);
							return T1;
						}
							R1.setWord(tokens[a+4]);
							for(int b=0;b<a;b++) {
								desc = desc + originalTokens[b] + " ";
							}
							T1.setDescription(desc);
							R1.setTaskDay(tokens[a+1]);
							R1.setRecurring(true);
							 break;
						}
					 else if((a+9)==tokens.size() && tokens[a+2]=="from" && tokens[a+4]=="to") {
						vector <string> fromRecTime;
				boost::split(fromRecTime,tokens[a+3],boost::is_any_of(":"));
				
				vector <string> toRecTime;
				boost::split(toRecTime,tokens[a+5],boost::is_any_of(":"));
				if(fromRecTime.size()==2 && toRecTime.size()==2 && isHourValid(toRecTime[0]) && isHourValid(fromRecTime[0]) && isMinuteValid(toRecTime[1]) && isMinuteValid(fromRecTime[1])) {
					string userStartTime = fromRecTime[0]+":"+fromRecTime[1]+":00";
					time_duration tdStart(duration_from_string(userStartTime));
					string userEndTime = toRecTime[0]+":"+toRecTime[1]+":00";
					time_duration tdEnd(duration_from_string(userEndTime));
					if(isTimeValid(tdStart)&&isTimeValid(tdEnd)) {
					T1.setEndHour(toRecTime[0]);
					T1.setEndMinute(toRecTime[1]);
					T1.setStartHour(fromRecTime[0]);
					T1.setStartMinute(fromRecTime[1]);
					}
					else
						T1.setTimeError(true);
				}
						else {
							bool value=true;
							T1.setTimeError(value);
							return T1;
						}
						if(tokens[a+6]=="until") {
							R1.setWord(tokens[a+6]);
						try {
							gregDate = stoi(tokens[a+7]);
						}
						catch (const std::invalid_argument) {
							R1.setRecurringError(true);
							break;
						}
	
						gregMonth = getMonthNumber(tokens[a+8]);
				
						try {
							boost::gregorian::date d(gregYear, gregMonth, gregDate);
							ptime now = microsec_clock::local_time();
							boost::gregorian::date today = now.date();
							if(d<today) {
								R1.setRecurringError(true);
								R1.setRecurring(false);
							}
							else {
								recurring=true;
								R1.setRecurring(recurring);
							}
							for(int b=0;b<a;b++) {
								desc = desc + originalTokens[b] + " ";
							}
							T1.setDescription(desc);
							R1.setTaskDay(tokens[a+1]);
							R1.setEndDate(tokens[a+7]);
							R1.setEndMonth(tokens[a+8]);
							break;
						}
						catch (std::out_of_range) {
							bool value=true;
							T1.setErrorDate(value);
							recurring=false;
						}
					 }
						
	
					 }
					 
					 else if((a+7)==tokens.size() && (tokens[a+6]).at(0)=='x' && isdigit(tokens[a+6].at(1))) {
								vector <string> fromRecTime;
							boost::split(fromRecTime,tokens[a+3],boost::is_any_of(":"));
				
				vector <string> toRecTime;
				boost::split(toRecTime,tokens[a+5],boost::is_any_of(":"));
				if(fromRecTime.size()==2 && toRecTime.size()==2 && isHourValid(toRecTime[0]) && isHourValid(fromRecTime[0]) && isMinuteValid(toRecTime[1]) && isMinuteValid(fromRecTime[1])) {
					string userStartTime = fromRecTime[0]+":"+fromRecTime[1]+":00";
					time_duration tdStart(duration_from_string(userStartTime));
					string userEndTime = toRecTime[0]+":"+toRecTime[1]+":00";
					time_duration tdEnd(duration_from_string(userEndTime));
					if(isTimeValid(tdStart)&&isTimeValid(tdEnd)) {
					T1.setEndHour(toRecTime[0]);
					T1.setEndMinute(toRecTime[1]);
					T1.setStartHour(fromRecTime[0]);
					T1.setStartMinute(fromRecTime[1]);
					}
					else
						T1.setTimeError(true);
				}
						else {
							bool value=true;
							T1.setTimeError(value);
							return T1;
						}	 
						 R1.setWord(tokens[a+6]);
							 for(int b=0;b<a;b++) {
								 desc = desc + originalTokens[b] + " ";
							}
							T1.setDescription(desc);
							R1.setTaskDay(tokens[a+1]);
							 R1.setRecurring(true);
							 break;
					}
					 else {
						 bool value=true;
						 R1.setRecurringError(value);

					}
				 }

			}

		}
		if(a==tokens.size()) {
			bool value=false;
			R1.setRecurring(false);
		}
	}

	if(!deadline && !R1.getRecurring()) {
		for(int j=0;j<originalTokens.size();j++) {
			desc = desc + originalTokens[j] + " ";
		}
		T1.setDescription(desc);
	}
	else if(T1.getErrorDate()) {
		return T1;
	}


return T1;
}

Task CommandParser::parserUpdate(string userInput){
	int startLine = userInput.find_first_not_of(" ");
	userInput = userInput.substr(startLine);
	int endLine = userInput.find_first_of(" ");
	string number = userInput.substr(0,endLine);
	userInput = userInput.substr(endLine+1);
	int startString = userInput.find_first_not_of(" ");
	userInput = userInput.substr(startString);
	RecurringTask R1;
	Task T1 = parseString(userInput,R1);
	Logic L1;
	T1.setNumber(L1.correctNumber(number));
	return T1;

}
CommandType CommandParser::getParserInput(string input,stack <string> inputStack){
	string command;
	RecurringTask R1;
	boost::trim(input);
	command = extractUserCommand(input);
	command = changeToLowerCase(command);
	boost::trim(command);
	boost::trim(userInput);
	taskDetails.setStack(inputStack);

	if(command=="add") {
		taskDetails = parseString(userInput,R1);
		Add *A1;
		A1=new Add(taskDetails,R1);
		CommandType C1(A1);
		return C1;
	}
	else if(command=="display") {
		Display *D1;
		Logic L1;
		if(userInput=="display")
			taskDetails.setKeywords("");
		else if(changeToLowerCase(userInput)=="done") {
			L1.setDisplayDone(true);
			taskDetails.setKeywords(userInput);
		}
		else 
			taskDetails.setKeywords(userInput);
		D1 = new Display(taskDetails);
		CommandType C1(D1);
		return C1;
	}
	else if(command=="delete") {
		Logic L1;
		taskDetails.setNumber(L1.correctNumber(userInput));
		Delete *Del;
		Del = new Delete(taskDetails);
		CommandType C1(Del);
		return C1;
	
	}	
	else if(command=="update") {
		taskDetails = parserUpdate(userInput);
		taskDetails.setStack(inputStack);
		Update *U1;
		U1 = new Update(taskDetails);
		CommandType C1(U1);
		return C1;
}
	else if(command=="clear") {
		Clear *C2;
		C2 = new Clear();
		CommandType C1(C2);
		return C1;
	}
	else if(command=="exit") {
		WrongFormat *W1;
		W1 = new WrongFormat();
		CommandType C1(W1);
		return C1;
	}
	else if(command=="search") {
		taskDetails.setKeywords(userInput);
		Search *S1;
		S1 = new Search(taskDetails);
		CommandType C1(S1);
		return C1;
	}
	else if(command=="undo") {
		taskDetails.setKeywords(userInput);
		Undo *U1;
		U1 = new Undo(taskDetails);
		CommandType C1(U1);
		return C1;
	}
	else if(command=="done") {
		Logic L1;
		taskDetails.setNumber(L1.correctNumber(userInput));
		Done *DoneTask;
		DoneTask = new Done(taskDetails);
		CommandType C1(DoneTask);
		return C1;

	}
	else {
		WrongFormat *W1;
		W1 = new WrongFormat();
		CommandType C1(W1);
		return C1;
	}
}


