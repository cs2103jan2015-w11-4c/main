#include "UI.h"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_WELCOME = "\n**********************\n* Welcome to Jarvis. *\n**********************\nCommands available: \n( add, delete, display, update, clear, exit)\nData will be written into %s.\n";
const string UI::MESSAGE_BYE = "Goodbye! Press any key to terminate the program . . .";
char UI::buffer[MAX_BUFFER_SIZE];
bool isRunning = true;
const string IDENTIFIERS = "/";
vector <pair <string, date>> UI::UImemory;
//vector<string> UI::months = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
//int month_no = 2;

int main(int argc, char* argv[]){
	UI::main(argc, argv);
	return 0;
}

void UI::main(int argc, char* argv[]){
	string fileName = argv[1];
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[1]);
	displayLine(buffer);

	cout << "*Copy address as text and paste below to specify file path." << endl << "Specify file path: ";
	string filePath;
	getline(cin, filePath);
	filePath += "\\";

	while (isRunning){
		cout << MESSAGE_COMMAND;
		string userInput;
		getline(cin, userInput);
		//readLine(userInput);
		Logic temp;
		string userCommand;
		userCommand = temp.extractUserCommand(userInput);

		if (userCommand != "exit" && userCommand != "display"){
			displayLine(temp.executeCommand(userInput, fileName, filePath));
		}
		else if (userCommand == "exit"){
			isRunning = false;
			displayLine(MESSAGE_BYE);
		}
		else if (userCommand == "display"){
			string displaytemp;
			displaytemp = temp.executeCommand(userInput, fileName, filePath);
			
			ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
			cout << "Current Date: " << now.date() << endl;

			time_duration tod = now.time_of_day();
			cout << "Current Time: " << tod.hours() << ':' << tod.minutes() << ':' << tod.seconds() << endl << endl;

			istringstream in(displaytemp);
			string extractLine;
			string taskDes, taskDate, taskMonth, taskYear, taskDay, nextSubstring;

			while (getline(in, extractLine)) {

				taskDes = extractUserCommand(extractLine, nextSubstring);
				extractLine = nextSubstring;

				taskDate = extractUserCommand(extractLine, nextSubstring);
				extractLine = nextSubstring;

				taskMonth = extractUserCommand(extractLine, nextSubstring);
				extractLine = nextSubstring;
				taskMonth = lowerCase(taskMonth).substr(0, 3);
				taskMonth = getMonthIndex(taskMonth);

				taskYear = extractUserCommand(extractLine, nextSubstring);
				extractLine = nextSubstring;

				taskDay = taskYear + taskMonth + taskDate;
				date d(from_undelimited_string(taskDay));

				UImemory.push_back(make_pair(taskDes, d));
				sort(UImemory.begin(), UImemory.end(), boost::bind(&pair<string, date>::second, _1) < boost::bind(&pair<string, date>::second, _2));
			}

			displayUI();
			UImemory.clear();
		}
	}
	return;
}

void UI::displayUI() {

	vector <pair <string, date>>::iterator iter;
	cout << "=============================================" << endl;
	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{
		cout << "Task: " << iter->first << "\t\tDeadline: " << iter->second << endl;
		cout << "=============================================" << endl;

	}
}

string UI::getMonthIndex(string name) {

	map<string, string> months
	{
		{ "jan", "01" },
		{ "feb", "02" },
		{ "mar", "03" },
		{ "apr", "04" },
		{ "may", "05" },
		{ "jun", "06" },
		{ "jul", "07" },
		{ "aug", "08" },
		{ "sep", "09" },
		{ "oct", "10" },
		{ "nov", "11" },
		{ "dec", "12" }
	};

	const auto iter = months.find(name);

	if (iter != months.cend())
		return iter->second;
	return "";
}


string UI::lowerCase(string input) {

	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}

int UI::startIndex(string input) {

	return input.find_first_not_of(IDENTIFIERS);
}

int UI::endIndex(string input) {
	return input.find_first_of(IDENTIFIERS);
}

string UI::extractUserCommand(string input, string &substring) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	substring = input.substr(end + 1);
	return input.substr(start, end - start);
}

void UI::displayLine(string text){
	cout << text << endl;
}
