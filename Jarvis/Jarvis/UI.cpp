#include "UI.h"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_WELCOME = "\n**********************\n* Welcome to Jarvis. *\n**********************\nCommands available: \n( add, delete, display, update, clear, exit)\nData will be written into %s.\n";
const string UI::MESSAGE_BYE = "Goodbye!";
char UI::buffer[MAX_BUFFER_SIZE];
bool isRunning = true;
const string IDENTIFIERS = "/";
vector <tuple <int, string, date>> UI::UImemory;
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

int main(int argc, char* argv[]){
	UI::main(argc, argv);
	return 0;
}

void UI::main(int argc, char* argv[]){
	setColour(15);
	string fileName = argv[1];
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[1]);
	displayLine(buffer);
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

		if (userCommand != "exit" && userCommand != "display"){ //add, update, delete, clear
			system("cls");
			//setindex
			int displayedIndex = 1;
			vector <tuple<int, string, date>>::iterator iter;
			for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
			{
				indexPair.push_back(make_pair(displayedIndex, get<0>(*iter)));
				displayedIndex++;

			}
			displayLine(temp.executeCommand(userInput, inputStack, fileName, filePath));			
		}
		else if (userCommand == "exit"){
			
			isRunning = false;
			displayLine(MESSAGE_BYE);
		}
		else if (userCommand == "display"){
			system("cls");
			UImemory.clear();
			indexPair.clear();
			string displaytemp;
			displaytemp = temp.executeCommand(userInput,inputStack, fileName, filePath);
			ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
			std::cout << "Current Date: " << now.date() << endl;

			time_duration tod = now.time_of_day();
			std::cout << "Current Time: " << tod.hours() << ':' << tod.minutes() << ':' << tod.seconds() << endl << endl;

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

			displayUI();
		}
	}
	return;
}

void UI::displayUI() {
	vector <tuple <int, string, date>>::iterator iter, iter2;
	int lineNo = 1;

	date nullDate(not_a_date_time);
	iter2 = UImemory.begin();

	setColour(13);
	cout << "   Deadline\t\tTask" << endl;

	setColour(3);
	std::cout << "=======================================================" << endl;
	setColour(15);
	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{

		if (get<2>(*iter) != get<2>(*iter2)) {
			setColour(3);
			std::cout << "=======================================================" << endl; //different date
			setColour(15);
		}

		if (get<2>(*iter) == nullDate ) {
					std::cout << lineNo << ". Do this anytime!\t\t";
				} else {
				std::cout << lineNo << ". " << get<2>(*iter) << "\t\t";
				}
		std::cout << get<1>(*iter) << endl;
			
		
		if (iter != UImemory.begin()) {
			iter2++;
		}
		lineNo++;
	}
	setColour(3);
	std::cout << "=======================================================" << endl << endl;
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

