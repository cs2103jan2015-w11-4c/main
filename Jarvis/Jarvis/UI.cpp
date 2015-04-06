#include "UI.h"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_WELCOME = "\n**********************\n* Welcome to Jarvis. *\n**********************\nCommands available: \n( add, delete, display, update, clear, exit)\nData will be written into ";
const string UI::MESSAGE_BYE = "Goodbye!";
char UI::buffer[MAX_BUFFER_SIZE];
bool isRunning = true;
const string IDENTIFIERS = "/";
vector <tuple <int, string, ptime, ptime>> UI::UImemory;
vector <pair <int, int>> UI::indexPair;

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
	}
};

int main(void){
	UI::main();
	return 0;
}

void UI::main(){
	setColour(15);
	cout << "File name: ";
	string fileName;
	getline(cin, fileName);

	while (fileName.substr(fileName.size() - 4, fileName.size()) != ".txt") //to catch invalid txt file
	{
		setColour(12);
		cout << endl <<"Please specify a valid text file: ";
		setColour(15);
		getline(cin, fileName);
		char *cstr = new char[fileName.length() + 1];
		strcpy(cstr, fileName.c_str());

	}

	string welcome = MESSAGE_WELCOME + fileName;
	displayLine(welcome);
	
	stack <string> inputStack;
	std::cout << "*Copy address as text and paste below to specify file path." << endl << "Specify file path: ";
	string filePath;
	getline(cin, filePath);
	filePath += "\\";

	while (isRunning){
		std::cout << endl << MESSAGE_COMMAND;
		
		string userInput;
		getline(cin, userInput);
		inputStack.push(userInput);
		Logic temp;
		string userCommand;
		userCommand = temp.extractUserCommand(userInput);

		//displayTodaysTask(temp, userInput, inputStack, fileName, filePath);

			
		if (userCommand == "display" || userCommand == "search"){
			system("cls");
			UImemory.clear();
			indexPair.clear();
			string displaytemp;
			displaytemp = temp.executeCommand(userInput, inputStack, fileName, filePath);
			
			if (displaytemp.substr(0, 7) == "Error: ")
			{
				displayLine(displaytemp);
				continue;
			}

			ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
			std::cout << "Current Date: " << now.date() << endl;

			time_duration tod = now.time_of_day();
			std::cout << "Current Time: " << tod.hours() << ':' << tod.minutes() << ':' << tod.seconds() << endl << endl;

			istringstream in(displaytemp);
			string extractLine;
			string taskDes;
			int origIndex = 1;

			while (getline(in, extractLine)) {

				vector <string> tokens;
				boost::split(tokens, extractLine, boost::is_any_of(IDENTIFIERS));

				vector<string>::iterator it= tokens.begin();
				int count = 0;
				
				taskDes = *it;
				if (isFloating(tokens)){ //floating task

					ptime d(not_a_date_time);
					UImemory.push_back(make_tuple(origIndex, taskDes, d, d));
					sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

				} else if (isDeadline(tokens)){
											
					ptime d(from_iso_string(prepareTaskDay(tokens)+"T235959"));
					ptime d2(not_a_date_time);

					UImemory.push_back(make_tuple(origIndex, taskDes, d, d2));
					sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

				} else if (isTimeTask1(tokens)){ //only has end hour and min

					ptime d(from_iso_string(prepareTaskDay(tokens) + "T" + prepareByEndHourEndMin(tokens) + "01")); // HH:MM:01 indicates TimeTask1, i.e. only end hour and min
					ptime d2(not_a_date_time);
					UImemory.push_back(make_tuple(origIndex, taskDes, d, d2));
					sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());
				} else  {
					ptime d(from_iso_string(prepareTaskDay(tokens) + "T" + prepareStartHourStartMin(tokens) + "02")); // HH:MM:02 indicates TimeTask2, i.e. start hour start min
					ptime d2(from_iso_string(prepareTaskDay(tokens) + "T" + prepareEndHourEndMin(tokens) + "03")); // HH:MM:03 indicates TimeTask2, i.e. end hour end min
					UImemory.push_back(make_tuple(origIndex, taskDes, d, d2));
					sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());
				}

				
				origIndex++;
			}

			displayUI();
		} else if (userCommand == "exit"){
			
			isRunning = false;
			displayLine(MESSAGE_BYE);
			system("pause");
		} else { //add, update, delete, clear
			system("cls");
			//setindex
			int displayedIndex = 1;
			vector <tuple<int, string, ptime, ptime>>::iterator iter;
			for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
			{
				indexPair.push_back(make_pair(displayedIndex, get<0>(*iter)));
				displayedIndex++;

			}
			displayLine(temp.executeCommand(userInput, inputStack, fileName, filePath));
		}
		
	}
	return;
}

void UI::displayUI() {
	vector <tuple <int, string, ptime, ptime>>::iterator iter, iter2;
	int lineNo = 1;

	ptime nullDate(not_a_date_time);
	iter2 = UImemory.begin();

	setColour(13);
	cout << "No." << setw(1) << " " << setw(8) << "Deadline" << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << "Task" << endl;
	setColour(3);
	std::cout << "=======================================================================================================" << endl;
	setColour(15);
	
	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{

		if (to_simple_string(get<2>(*iter)).substr(0,11) != to_simple_string(get<2>(*iter2)).substr(0,11)) {
			setColour(3);
			std::cout << "=======================================================================================================" << endl; //different date
			setColour(15);
		}

		if (get<2>(*iter) == nullDate ) { 
				std::cout << lineNo << "." << setw(1) << " " << setw(8) << "Anytime!";//print Deadline
				std::cout << setw(8) << " " << setw(8) << "        --    ";//print time duration
				} else { //not floating task
				std::cout << lineNo << ".";
					if (iter == UImemory.begin() || to_simple_string(get<2>(*iter)).substr(0, 11) != to_simple_string(get<2>(*iter2)).substr(0, 11)) {
					std::cout<< setw(1) << " " << setw(8) << to_simple_string(get<2>(*iter)).substr(0, 11); //print deadline if different date
					}
					else
					{
					std::cout << setw(1) << "            " << setw(8);
					}

					if (to_simple_string(get<2>(*iter)).substr(12,8) == "23:59:59") { //this is a deadline task
						std::cout << setw(8) << "  " << setw(8) << "     --    ";//deadline tasks don't have time duration
					} else if (to_simple_string(get<2>(*iter)).substr(18, 2) == "01"){ // TimeTask1
						std::cout << setw(8) << "  " << setw(8) << "  by " + to_simple_string(get<2>(*iter)).substr(12, 5) + " ";
					} else { //TimeTask2
						std::cout << setw(8) << " " << setw(8) << to_simple_string(get<2>(*iter)).substr(12, 5) + "-" + to_simple_string(get<3>(*iter)).substr(12, 5);
					}

			}

		
		std::cout << setw(10) << " " << setw(10) << left <<get<1>(*iter) << endl; //print out Task

		if (iter != UImemory.begin()) {
			iter2++;
		}
		lineNo++;
	}
	
	setColour(3);
	std::cout << "=======================================================================================================" << endl << endl;
	setColour(15);
}

string UI::getMonthIndex(string name) {

	map<string, string> months;
	map<string,string>::iterator iter;

		months["jan"]="01";
		months["feb"]="02";
		months["mar"]="03";
		months["apr"]="04";
		months["may"]="05";
		months["jun"]="06";
		months["jul"]="07";
		months["aug"]="08";
		months["sep"]="09";
		months["oct"]="10";
		months["nov"]="11";
		months["dec"]="12";

	 iter = months.find(name);

	if (iter != months.end())
		return iter->second;
	return "";
}


string UI::lowerCase(string input) {

	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}

void UI::displayLine(string text){
	std::cout << text << endl;
}

void UI::setColour(int value) {
	/*
	1: Blue
	2: Green
	3: Cyan
	4: Red
	5: Purple
	6: Yellow (Dark)
	7: Default white
	8: Gray/Grey
	9: Bright blue
	10: Brigth green
	11: Bright cyan
	12: Bright red
	13: Pink/Magenta
	14: Yellow
	15: Bright white
*/

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

bool UI::isFloating(vector <string> tokens) {
	
	bool floating = false;
	vector <string>::iterator iter = tokens.begin();
	iter++;
	if (*iter == "" && *(++iter) == "") {
		floating = true;
	}
	return floating;
}

bool UI::isDeadline(vector <string> tokens) {

	bool deadline = false;
	vector <string>::iterator iter = tokens.begin();
	iter++;
	iter++;
	iter++;
	iter++;
	if (*iter == "" && *(iter + 5) == "") {
		deadline = true;
	}
	return deadline;
}

bool UI::isTimeTask1(vector <string> tokens) {
	bool timeTask1 = false;
	vector <string>::iterator iter = tokens.begin();
	iter++;
	iter++;
	iter++;
	iter++;
	if (*iter != "" && *(++iter) != "") {
		timeTask1 = true;
	}
	return timeTask1;
}

bool UI::isTimeTask2(vector <string> tokens) {
	bool timeTask2 = false;
	vector <string>::iterator iter = tokens.begin();
	iter++;
	iter++;
	iter++;
	iter++;
	iter++;
	iter++;
	if (*iter != "" && *(++iter) != "") {
		timeTask2 = true;
	}
	return timeTask2;
}

string UI::prepareTaskDay(vector<string> tokens) {
	string taskDate, taskMonth, taskYear, taskDay;
	vector<string>::iterator it = tokens.begin();
	it++;

	taskDate = *it;

	it++;

	taskMonth = *it;
	taskMonth = UI::lowerCase(taskMonth).substr(0, 3);
	taskMonth = UI::getMonthIndex(taskMonth);
	it++;


	taskYear = *it;

	taskDay = taskYear + taskMonth + taskDate;
	return taskDay;
}

string UI::prepareByEndHourEndMin(vector<string> tokens) {
	string byEndHour, byEndMin, byEndTime;
	vector<string>::iterator it = tokens.begin();
	it++;
	it++;
	it++;
	it++;
	byEndHour = *it;
	it++;
	byEndMin = *it;

	byEndTime = byEndHour + byEndMin;
	return byEndTime;
}

string UI::prepareStartHourStartMin(vector<string> tokens) {
	string startHour, startMin, startTime;
	vector<string>::iterator it = tokens.begin();
	it = it + 6;
	startHour = *it;
	it++;
	startMin = *it;

	startTime = startHour + startMin;
	return startTime;
}

string UI::prepareEndHourEndMin(vector<string> tokens) {
	string endHour, endMin, endTime;
	vector<string>::iterator it = tokens.begin();
	it = it + 8;
	endHour = *it;
	it++;
	endMin = *it;

	endTime = endHour + endMin;
	return endTime;
}

/*

void UI::displayTodaysTask(Logic temp, string userInput, stack<string> inputStack, string fileName, string filePath) {

		UImemory.clear();
		string displaytemp;
		displaytemp = temp.executeCommand(userInput, inputStack, fileName, filePath);
		
		istringstream in(displaytemp);
		string extractLine;
		string taskDes, taskDate, taskMonth, taskYear, taskDay, nextSubstring;
		int origIndex = 1;

		while (getline(in, extractLine)) {

			vector <string> tokens;
			boost::split(tokens, extractLine, boost::is_any_of(IDENTIFIERS));

			vector<string>::iterator it = tokens.begin();
			taskDes = *it;

			it++;
			if (*it == ""){ //floating task
				date d(not_a_date_time);
				UImemory.push_back(make_tuple(origIndex, taskDes, d));
				sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

			}
			else {
				taskDate = *it;
				it++;

				taskMonth = *it;
				taskMonth = lowerCase(taskMonth).substr(0, 3);
				taskMonth = getMonthIndex(taskMonth);
				it++;


				taskYear = *it;

				taskDay = taskYear + taskMonth + taskDate;

				date d(from_undelimited_string(taskDay));

				UImemory.push_back(make_tuple(origIndex, taskDes, d));
				sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

			}
			origIndex++;
		}

		vector <tuple <int, string, date>>::iterator iter;
		ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
		date nullDate(not_a_date_time);
		for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
		{
			if (get<2>(*iter) == now.date()) {
				
					std::cout << "Finish this by today: "<< get<1>(*iter) << endl;
			}
		}
		return;
}
*/

