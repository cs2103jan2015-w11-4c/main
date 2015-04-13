#include "Display.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

Display::Display() {

}

Display::Display(Task taskObject) {
	T1 = taskObject;
}

Display::~Display() {

}

string Display::getFullMonth(string name) {

	map<string, string> months;
	map<string,string>::iterator iter;

		months["Jan"]="january";
		months["Feb"]="february";
		months["Mar"]="march";
		months["Apr"]="april";
		months["May"]="may";
		months["Jun"]="june";
		months["Jul"]="july";
		months["Aug"]="august";
		months["Sep"]="september";
		months["Oct"]="october";
		months["Nov"]="november";
		months["Dec"]="december";

	 iter = months.find(name);

	if (iter != months.end())
		return iter->second;
	return "";
}

int Display::getMonthNumber(string name) {

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

int Display::getDayNumber(string name) {

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

void Display::searchForMonth(vector <string>& input) {
	int i;
	for(i=0;i<input.size();i++) {
		if(getMonthNumber(input[i])!=0) {
			input[i]=(input[i]).substr(0,3);
		}
	}
}



string Display::execute(string fileName,string filePath) {
	vector <string> dateVector;
	vector <string> keywordVector;
	string word;
	if(!T1.getBlankString()) {
	boost::trim(T1.getKeywords());
	vector <string> tokensBeforeTrim;
	int i;
	boost::split(tokensBeforeTrim,T1.getKeywords(),boost::is_any_of(" "));
	for(i=0;i<tokensBeforeTrim.size();i++) {
		if(tokensBeforeTrim[i].find_first_not_of(' ') != string::npos) {
			keywordVector.push_back(changeToLowerCase(tokensBeforeTrim[i]));
		}
	}
	T1.setKeywords("");
	for(i=0;i<keywordVector.size()-1;i++) 
		word = word + keywordVector[i] + " ";
	if(i==keywordVector.size()-1)
		word = word + keywordVector[i];
	T1.setKeywords(word);
	//remove spaces and put to lower case

	if(T1.getKeywords()=="all") {
		return S1.readFile(fileName,filePath);
	}

	else if(T1.getKeywords()=="today") {
		ptime now = microsec_clock::local_time();
		date today = now.date();
		boost::split(dateVector,to_simple_string(today),boost::is_any_of("-"));
		if(dateVector[2].at(0)=='0')
			dateVector[2] = dateVector[2].at(1);
		string keywords = dateVector[2] +" " + dateVector[1] + " " + dateVector[0];
		T1.setKeywords(keywords);
		Search S2(T1);
		if(S2.executeSearch(fileName,filePath)=="") {
			return "Error: There are no tasks scheduled for today - " + keywords +"\n";
		}
		else {
			return S2.executeSearch(fileName,filePath);
		}
	}

	else if(T1.getKeywords()=="tomorrow") {
		ptime now = microsec_clock::local_time();
		date_duration dd(1);
		date tomorrow = now.date() + dd;
		boost::split(dateVector,to_simple_string(tomorrow),boost::is_any_of("-"));
		if(dateVector[2].at(0)=='0')
			dateVector[2] = dateVector[2].at(1);
		string keywords = dateVector[2] +" " + dateVector[1] + " " + dateVector[0];
		T1.setKeywords(keywords);
		Search S2(T1);
		if(S2.executeSearch(fileName,filePath)=="") {
			return "Error: There are no tasks scheduled for tomorrow - " + keywords +"\n";
		}
		else {
			return S2.executeSearch(fileName,filePath);
		}

	}
	else if(T1.getKeywords()=="monday" || T1.getKeywords()=="tuesday" || T1.getKeywords()=="wednesday" || T1.getKeywords()=="thursday" || T1.getKeywords()=="friday" || T1.getKeywords()=="saturday" || T1.getKeywords()=="sunday") {
		ptime now = microsec_clock::local_time();
		string dayName = T1.getKeywords();
		date today = now.date();
		greg_weekday gregDay = getDayNumber(T1.getKeywords());
		first_day_of_the_week_after fdaf(gregDay);
		date day = fdaf.get_date(date(today));
		boost::split(dateVector,to_simple_string(day),boost::is_any_of("-"));
		string dateNumber = dateVector[2];
		if(dateVector[2].at(0)=='0')
			dateVector[2] = dateVector[2].at(1);
		string keywords = dateVector[2] +" " +dateVector[1] + " " + dateVector[0];
		T1.setKeywords(keywords);
		Search S2(T1);
		if(S2.executeSearch(fileName,filePath)=="") {
			return "Error: There are no tasks scheduled for "+ dayName + " - " + keywords +"\n";
		}
		else {
			return S2.executeSearch(fileName,filePath);
		}

	}
	else if(T1.getKeywords()=="done") {
		Search S2(T1);
		if(S2.execute(fileName,filePath)=="") {
			return "Error: No tasks have been completed yet!\n";
		}
		else {
			return S2.execute(fileName,filePath);
		}
	}
	else {
		searchForMonth(keywordVector);
		word="";
		for(i=0;i<keywordVector.size()-1;i++) 
			word = word + keywordVector[i] + " ";
		if(i==keywordVector.size()-1)
			word = word + keywordVector[i];
		T1.setKeywords(word);
		Search S2(T1);
		if(S2.executeSearch(fileName,filePath)=="") {
			return "Error: There are no tasks scheduled with the keywords - "+T1.getKeywords()+" in the deadline. Please enter a valid date. \n";
		}
		else {
			return S2.executeSearch(fileName,filePath);
		}

	}
}

	else {

		return "Error: Please enter a valid keyword after   *DISPLAY*   to view your tasks";
	}
}

string Display::changeToLowerCase(string input) {
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
