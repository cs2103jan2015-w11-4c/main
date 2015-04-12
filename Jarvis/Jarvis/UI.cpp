#include "UI.h"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

const string UI::MESSAGE_COMMAND = "command: ";
/*
const string UI::MESSAGE_WELCOME1 = "\n*******************************************************************************************************";
const string UI::MESSAGE_WELCOME2 = "*****************************************";
const string UI::MESSAGE_WELCOME3 = " Welcome to Jarvis. ";
const string UI::MESSAGE_WELCOME4 = "******************************************";
const string UI::MESSAGE_WELCOME5 = "*******************************************************************************************************\n\n";
*/
const string UI::MESSAGE_COMMANDS_AVAIL = "\t\t\tCommands available : \n\t\t\t(add, delete, display, update, clear, search, undo, done, exit)\n\t\t\t===============================================================\n\t\t\tType in help to view all commands supported.\n\n";
const string UI::MESSAGE_WELCOME6 = "Data will be written into ";
const string UI::MESSAGE_BYE = "Goodbye!";
char UI::buffer[MAX_BUFFER_SIZE];
bool isRunning = true;
const string IDENTIFIERS = "/";
vector <tuple <int, string, ptime, ptime, string>> UI::UImemory;
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
	//PlaySound("C:\\Users\\Gabriel\\Documents\\GitHub\\main\\Jarvis\\Jarvis\\audioFile.wav", NULL, SND_ASYNC);
	UI::main();
	return 0;
}

void UI::main(){
	setColour(13);
	printJarvis();
	cout << "\n\n";
	setColour(15);
	cout << "Hey there! Your schedule is saved in a text file. What do you want your file to be named as? (*.txt): ";
	string fileName="";
	int iterations = 0;
	while (fileName.empty() || fileName.size() <= 4) {
		if (iterations != 0) {
			setColour(12);
			cout << "\nPlease specify a text file: ";
			setColour(15);
		}
		
		getline(cin, fileName);

		iterations++;

	}

	system("cls");

	while (fileName.substr(fileName.size() - 4, fileName.size()) != ".txt" || fileName.size() <= 4) //to catch invalid txt file
	{
		setColour(12);
		cout << endl <<"Please specify a valid text file: ";
		setColour(15);
		getline(cin, fileName);

	}
	setColour(13);
	printJarvis();
	cout << "\n\n";
	setColour(15);

	string welcomeTextFile = MESSAGE_WELCOME6 + fileName;
	displayLine(welcomeTextFile);
	
	stack <string> inputStack;
	std::cout << "\n*Copy address as text and paste below to specify file path." << endl << "Specify file path (Folder where you would like your textfile to be saved in): ";
	string filePath;
	getline(cin, filePath);
	size_t found = filePath.find_first_of("\\");
	while(found == string::npos){ //if = npos, filePath does not contain "\"
		setColour(12);
		cout << "\nPlease specify a valid file path: ";
		setColour(15);
		getline(cin, filePath);
		found = filePath.find_first_of("\\");
	}
	
	filePath += "\\";
	
	bool firstRun = true;
	bool defaultViewPrinted;
	
	while (isRunning){
		
		string userInput="";
		
		iterations = 0;
		
		if (firstRun && emptyFileFirstRun(filePath + fileName)) { //default view printed on the first run -->check if file is empty
			int displayedIndex = 1;
			vector <tuple<int, string, ptime, ptime, string>>::iterator iter;

			for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
			{
				if (get<4>(*iter) != "done"){
					indexPair.push_back(make_pair(displayedIndex, get<0>(*iter)));
					displayedIndex++;
				}

			}

			std::cout << endl;
			defaultView("display all", inputStack, fileName, filePath);
	
		}

		if (!emptyFileFirstRun(filePath + fileName) && firstRun) {
			cout << "\n\n";
			displayLine(MESSAGE_COMMANDS_AVAIL); //print commands available if new file is created, and no tasks to display for today
		}
		
		while (userInput.empty()) {
			if (iterations != 0) {
				setColour(12);
				system("cls");
				cout << "\nPlease specify a valid command, Type in help to view all commands supported." << endl;
				setColour(15);
			}
			std::cout << endl << MESSAGE_COMMAND; 
			getline(cin, userInput);
			
			iterations++;

		}

		firstRun = false;

		//trim
		size_t start = userInput.find_first_not_of(" ");
		if (start != string::npos)
		{
			userInput = userInput.substr(start);
		}
		userInput = lowerCase(userInput);
		inputStack.push(userInput);
		Logic temp;
		string userCommand;
		userCommand = temp.extractUserCommand(userInput);
	
		if (userCommand == "display" || userCommand == "search"){
			system("cls");
			UImemory.clear();
			indexPair.clear();
			string displaytemp;
			displaytemp = temp.executeCommand(userInput, inputStack, fileName, filePath);
			
			if (displaytemp.substr(0, 7) == "Error: ")
			{
				setColour(12);
				displayLine(displaytemp.substr(7));
				setColour(15);
				continue;
			}

			ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
			setColour(13);
			std::cout << "Current  Day &  Date";
			setColour(3);
			std::cout <<": ";
			setColour(15);
			std::cout << now.date().day_of_week().as_long_string() << " " << now.date().year_month_day().month.as_long_string() << " " << now.date().year_month_day().day << ", " << now.date().year_month_day().year << endl;

			setColour(13);
			std::cout << "Current Time (HH:MM)";
			setColour(3);
			std::cout << ": ";
			setColour(15);
			std::cout << to_simple_string(now).substr(12, 5) << endl << endl;

			prepareUImemory(displaytemp);
			
			//determine if it is a display done
			string userInputDisplayDone = userInput.substr(7);
			size_t foundDisplayDone = userInputDisplayDone.find_first_not_of(" ");
			if (foundDisplayDone != string::npos) {
				userInputDisplayDone = userInputDisplayDone.substr(foundDisplayDone,4);
			}

			if (userInputDisplayDone == "done")
			{
				displayUI("done"); //status is done if want to print tasks that are done
			} else {
				displayUI("low"); //status is low if want to print tasks that are not done
			}

			
		} else if (userCommand == "exit"){
			
			isRunning = false;
			displayLine(MESSAGE_BYE);
			system("pause");
		}
		else if (userCommand == "help") {
			system("cls");
			setColour(13);
			printJarvis();
			setColour(15);
			cout << "\n\n\n";
			/*
			cout << "test:" << userInput.substr(4) << endl; //see where to cut 
			string helpType = userInput.substr(7);
			size_t foundHelpType = helpType.find_first_not_of(" ");
			size_t foundHelpTypeEnd = 
			if (foundHelpType != string::npos) {
				helpType = helpType.substr(foundHelpType, 4);
			}
			*/

			displayLine(MESSAGE_COMMANDS_AVAIL);
		}
		else { //add, update, delete, clear
			system("cls");
			//setindex
			int displayedIndex = 1;
			vector <tuple<int, string, ptime, ptime, string>>::iterator iter;
			
			for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
			{
				if (get<4>(*iter) != "done"){
					indexPair.push_back(make_pair(displayedIndex, get<0>(*iter)));
					displayedIndex++;
				}

			}
			
			string statusMessage = temp.executeCommand(userInput, inputStack, fileName, filePath);
			defaultView("display all", inputStack, fileName, filePath);
			std::cout << "Status message: ";

			if (statusMessage.substr(0, 7) == "Error: ")
			{
				setColour(12);
				displayLine(statusMessage.substr(7));
				setColour(15);
			} else {
				setColour(10);
				displayLine(statusMessage);
				setColour(15);
			}


		}
		
	}
	return;
}

void UI::prepareUImemory(string displaytemp){
	istringstream in(displaytemp);
	string extractLine;
	string taskDes;
	string status;
	int origIndex = 1;

	while (getline(in, extractLine)) {

		vector <string> tokens;
		boost::split(tokens, extractLine, boost::is_any_of(IDENTIFIERS));

		vector<string>::iterator it = tokens.begin();
		vector<string>::iterator itEnd = tokens.end();
		--itEnd;
		int count = 0;

		taskDes = *it;
		status = *itEnd;
		if (isFloating(tokens)){ //floating task

			ptime d(not_a_date_time);
			UImemory.push_back(make_tuple(origIndex, taskDes, d, d, status));
			sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

		}
		else if (isDeadline(tokens)){

			ptime d(from_iso_string(prepareTaskDay(tokens) + "T235959"));
			ptime d2(not_a_date_time);

			UImemory.push_back(make_tuple(origIndex, taskDes, d, d2, status));
			sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());

		}
		else if (isTimeTask1(tokens)){ //only has end hour and min

			ptime d(from_iso_string(prepareTaskDay(tokens) + "T" + prepareByEndHourEndMin(tokens) + "01")); // HH:MM:01 indicates TimeTask1, i.e. only end hour and min
			ptime d2(not_a_date_time);
			UImemory.push_back(make_tuple(origIndex, taskDes, d, d2, status));
			sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());
		}
		else  {
			ptime d(from_iso_string(prepareTaskDay(tokens) + "T" + prepareStartHourStartMin(tokens) + "02")); // HH:MM:02 indicates TimeTask2, i.e. start hour start min
			ptime d2(from_iso_string(prepareTaskDay(tokens) + "T" + prepareEndHourEndMin(tokens) + "03")); // HH:MM:03 indicates TimeTask2, i.e. end hour end min
			UImemory.push_back(make_tuple(origIndex, taskDes, d, d2, status));
			sort(UImemory.begin(), UImemory.end(), TupleCompare<2>());
		}


		origIndex++;
	}
	return;
}

void UI::defaultView(string userInput, stack <string> inputStack, string fileName, string filePath){
	UImemory.clear();
	string displaytemp;
	Logic temp;
	displaytemp = temp.executeCommand(userInput, inputStack, fileName, filePath);

	prepareUImemory(displaytemp);
	
	//current date & time
	ptime now = microsec_clock::local_time(); // current *LOCAL TIMEZONE* time/date 
	setColour(13);
	std::cout << "Current  Day &  Date";
	setColour(3);
	std::cout << ": ";
	setColour(15);
	std::cout << now.date().day_of_week().as_long_string() << " " << now.date().year_month_day().month.as_long_string() << " " << now.date().year_month_day().day << ", " << now.date().year_month_day().year << endl;

	setColour(13);
	std::cout << "Current Time (HH:MM)";
	setColour(3);
	std::cout << ": ";
	setColour(15);
	std::cout << to_simple_string(now).substr(12, 5) << endl << endl;

	setColour(3);
	std::cout << "=====================================================================================================================================" << endl;
	setColour(15);
	std::cout << "These are the tasks for today." << endl;
	setColour(3);
	std::cout << "=====================================================================================================================================" << endl;
	setColour(13);
	cout << "   " << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << "Task" << endl;
	setColour(9);
	std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setColour(15);
	vector <tuple<int, string, ptime, ptime, string>>::iterator iter;
	
	bool noTaskDisplay = false;

	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{

		if (get<2>(*iter).date() == now.date())
		{
			//print out tasks for today
			
			if (to_simple_string(get<2>(*iter)).substr(12, 8) == "23:59:59" && get<4>(*iter) != "done") { //this is a deadline task
				std::cout << "   ";
				
				std::cout << setw(8) << "  " << setw(8) << left << "     --    ";//deadline tasks don't have time duration, end at 23:59
			}
			else if (to_simple_string(get<2>(*iter)).substr(18, 2) == "01" && get<4>(*iter) != "done"){ // TimeTask1
				std::cout << "   ";
				
				std::cout << setw(8) << "  " << setw(8) << left << "00:00-" + to_simple_string(get<2>(*iter)).substr(12, 5);
			}
			else { //TimeTask2
				if (get<4>(*iter) != "done") {
					std::cout << "   ";
					
					std::cout << setw(8) << " " << setw(8) << left << to_simple_string(get<2>(*iter)).substr(12, 5) + "-" + to_simple_string(get<3>(*iter)).substr(12, 5);
				}
			}
			if (get<4>(*iter) != "done") {
				std::cout << setw(10) << " " << setw(10) << left << get<1>(*iter) << endl;
				
				noTaskDisplay = true;
			}
		}

	}
	if (!noTaskDisplay)
	{
		setColour(10);
		cout << "There are no tasks for today." << endl;
	}
	setColour(3);
	std::cout << "=====================================================================================================================================" << endl << endl;

	setColour(15);

	displayLine(MESSAGE_COMMANDS_AVAIL);
	return;
}

void UI::displayUI(string status) { //status can be "done" or "low" by default
	vector <tuple <int, string, ptime, ptime, string>>::iterator iter, iter2;
	int lineNo = 1;
	int floating = 0;
	ptime nullDate(not_a_date_time);
	iter2 = UImemory.begin();
	ptime now = microsec_clock::local_time();
	bool overdue = false;
	
	if (status == "done") { //print out this header to differentiate, when display done is called.
		setColour(3);
		std::cout << "=====================================================================================================================================" << endl;
		setColour(14);
		std::cout << "\t These are the tasks that have been completed" << endl;
	}
	
	if (!noDateTasks(status)) {
		setColour(3);
		std::cout << "=====================================================================================================================================" << endl;
		setColour(15);
	}
	bool noTaskDisplay = false;

	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{
		if (to_simple_string(get<2>(*iter)).substr(0, 11) != to_simple_string(get<2>(*iter2)).substr(0, 11) && !noTasksToday((get<2>(*iter)).date(), status) && !noTasksToday((get<2>(*iter2)).date(), status) && get<2>(*iter2) != nullDate && get<2>(*iter) != nullDate) {
			setColour(3);
			std::cout << "=====================================================================================================================================" << endl; //different date
			setColour(15);
		}
		

		if (get<2>(*iter) == nullDate ) { //only print out header for first floating task
			if (floating == 0 && !noTasksToday((get<2>(*iter)).date(), status)) {
				
				setColour(3);
				if (!noDateTasks(status)) {
					std::cout << "=====================================================================================================================================\n\n\n" << endl;
				}
				std::cout << "=====================================================================================================================================" << endl;
				setColour(8);
				std::cout << setw(1) << "\t Do these tasks anytime!" << endl; 
				setColour(3);
				std::cout << "=====================================================================================================================================" << endl; //different date
				setColour(13);
				cout << "No." << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << "Task" << endl;
				setColour(9);
				std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
				setColour(15);
	
				}
				if (get<4>(*iter) == status)
				{
					std::cout << lineNo << ".";
					if (lineNo < 10) {
						std::cout << " "; //for alignment
						}
						std::cout << setw(8) << "  " << setw(8) << "     --    ";
						floating++;
				}
				
		}
		else { //not floating task
			if (iter == UImemory.begin() || to_simple_string(get<2>(*iter)).substr(0, 11) != to_simple_string(get<2>(*iter2)).substr(0, 11)) {
				//check if task is overdue
				if ((get<2>(*iter)).date() < now.date() && !noTasksToday((get<2>(*iter)).date(), status) && status == "low")  //only print overdue status for all display other than display done

				{
					date::ymd_type ymd1 = (get<2>(*iter).date()).year_month_day();
					greg_weekday wd1 = (get<2>(*iter).date()).day_of_week();
					overdue = true;
					setColour(12);
					std::cout << setw(1) << " Overdue warning! : [" << wd1.as_long_string() << " " << ymd1.month.as_long_string() << " " << ymd1.day << ", " << ymd1.year << "]" << endl; //print deadline if different date	
					std::cout << "=====================================================================================================================================" << endl; //different date
					cout << "No." << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << left << "Task" << endl;
					std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
				} else if (!noTasksToday((get<2>(*iter)).date(), status)) {
					date::ymd_type ymd2 = (get<2>(*iter).date()).year_month_day();
					greg_weekday wd2 = (get<2>(*iter).date()).day_of_week();

					std::cout << setw(1) << " Deadline: [" << wd2.as_long_string() << " " << ymd2.month.as_long_string() << " " << ymd2.day << ", " << ymd2.year << "]" << endl; //print deadline if different date	
					setColour(3);
					std::cout << "=====================================================================================================================================" << endl; //different date
					setColour(13);
					cout << "No." << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << left <<"Task" << endl;
					setColour(9);
					std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
					setColour(15);
				}
			}
		

			if (to_simple_string(get<2>(*iter)).substr(12, 8) == "23:59:59"  && get<4>(*iter) == status) { //this is a deadline task
					std::cout << lineNo << ".";
					if (lineNo < 10){
						std::cout << " "; //for alignment
					}
					std::cout << setw(8) << "  " << setw(8) << left << "     --    ";//deadline tasks don't have time duration, end at 23:59
				}
			else if (to_simple_string(get<2>(*iter)).substr(18, 2) == "01"  && get<4>(*iter) == status){ // TimeTask1
					std::cout << lineNo << ".";
					if (lineNo < 10){
						std::cout << " "; //for alignment
					}
					std::cout << setw(8) << "  " << setw(8) << left << "00:00-" + to_simple_string(get<2>(*iter)).substr(12, 5);
				}
				else { //TimeTask2
					if (get<4>(*iter) == status){
						std::cout << lineNo << ".";
						if (lineNo < 10){
							std::cout << " "; //for alignment
						}
						std::cout << setw(8) << " " << setw(8) << left << to_simple_string(get<2>(*iter)).substr(12, 5) + "-" + to_simple_string(get<3>(*iter)).substr(12, 5);
					}
				}

			}

		if (get<4>(*iter) == status) {
			std::cout << setw(10) << " " << setw(10) << left << get<1>(*iter) << endl; //print out Task
		}
		
		if (iter != UImemory.begin()) {
			iter2++;
		}
		overdue = false;
		if (get<4>(*iter) == status) {
			lineNo++;
			noTaskDisplay = true;
		}
	}
	if (!noTaskDisplay)
	{
		setColour(10);
		cout << "There are no tasks to display" << endl;
	}
	setColour(3);
	std::cout << "=====================================================================================================================================" << endl << endl;
	setColour(15);
}
	
bool UI::noDateTasks(string status) { //returns true if there are no Date Tasks in UImemory, done date tasks considered as "off" the list [status = done]	display done
	bool noDateTasks = true;		//returns true if there are no Date Tasks in UI mememory, done date tasks considered as "on" the list [status = low]	display --
	vector <tuple <int, string, ptime, ptime, string>>::iterator itr;
	ptime nullDate(not_a_date_time);
		for (itr = UImemory.begin(); itr != UImemory.end(); itr++) {
			if ((get<2>(*itr)).date() != nullDate.date() && get<4>(*itr) == status) {
				noDateTasks = false;
			}
		}

	return noDateTasks;
}

bool UI::noTasksToday(date today, string status) { //check if all the tasks for today are done , prints the opposite if status is done
	bool noTasks;
	int countTasks = 0;
	int countDone = 0;
	vector <tuple <int, string, ptime, ptime, string>>::iterator iter;
	for (iter = UImemory.begin(); iter != UImemory.end(); iter++) {
		if ((get<2>(*iter)).date() == today) {
			if (get<4>(*iter) == "done") {
				countDone++;
			}
			countTasks++;
		}
	}

	if (countDone == countTasks) {
		if (status == "low"){
			noTasks = true;
		} else {
			noTasks = false;
		}
	} else {
		if (status == "low"){
			noTasks = false;
		} else {
			noTasks = true;
		}

	}

	return noTasks;
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

bool UI::emptyFileFirstRun(string fullFilePath) {
	ifstream readfile(fullFilePath.c_str());
	return readfile.good();
}

void UI::printJarvis() {
	string getJarvis[16] ;
	
		getJarvis[0] = "          JJJJJJJJJJJ          AAA               RRRRRRRRRRRRRRRRR   VVVVVVVV           VVVVVVVVIIIIIIIIII   SSSSSSSSSSSSSSS ";
		getJarvis[1] = "          J:::::::::J         A:::A              R::::::::::::::::R  V::::::V           V::::::VI::::::::I SS:::::::::::::::S";
		getJarvis[2] = "          J:::::::::J        A:::::A             R::::::RRRRRR:::::R V::::::V           V::::::VI::::::::IS:::::SSSSSS::::::S";
		getJarvis[3] = "          JJ:::::::JJ       A:::::::A            RR:::::R     R:::::RV::::::V           V::::::VII::::::IIS:::::S     SSSSSSS";
		getJarvis[4] = "            J:::::J        A:::::::::A             R::::R     R:::::R V:::::V           V:::::V   I::::I  S:::::S            ";
		getJarvis[5] = "            J:::::J       A:::::A:::::A            R::::R     R:::::R  V:::::V         V:::::V    I::::I  S:::::S            ";
		getJarvis[6] = "            J:::::J      A:::::A A:::::A           R::::RRRRRR:::::R    V:::::V       V:::::V     I::::I   S::::SSSS         ";
		getJarvis[7] = "            J:::::j     A:::::A   A:::::A          R:::::::::::::RR      V:::::V     V:::::V      I::::I    SS::::::SSSSS    ";
		getJarvis[8] = "            J:::::J    A:::::A     A:::::A         R::::RRRRRR:::::R      V:::::V   V:::::V       I::::I      SSS::::::::SS  ";
		getJarvis[9] = "JJJJJJJ     J:::::J   A:::::AAAAAAAAA:::::A        R::::R     R:::::R      V:::::V V:::::V        I::::I         SSSSSS::::S ";
		getJarvis[10] = "J:::::J     J:::::J  A:::::::::::::::::::::A       R::::R     R:::::R       V:::::V:::::V         I::::I              S:::::S";
		getJarvis[11] = "J::::::J   J::::::J A:::::AAAAAAAAAAAAA:::::A      R::::R     R:::::R        V:::::::::V          I::::I              S:::::S";
		getJarvis[12] = "J:::::::JJJ:::::::JA:::::A             A:::::A   RR:::::R     R:::::R         V:::::::V         II::::::IISSSSSSS     S:::::S";
		getJarvis[13] = " JJ:::::::::::::JJA:::::A               A:::::A  R::::::R     R:::::R          V:::::V          I::::::::IS::::::SSSSSS:::::S";
		getJarvis[14] = "   JJ:::::::::JJ A:::::A                 A:::::A R::::::R     R:::::R           V:::V           I::::::::IS:::::::::::::::SS ";
		getJarvis[15] = "     JJJJJJJJJ  AAAAAAA                   AAAAAAARRRRRRRR     RRRRRRR            VVV            IIIIIIIIII SSSSSSSSSSSSSSS   ";

		for (int i = 0; i < 16; i++) {
		cout << getJarvis[i] << endl;
	}

}
/*
void UI::displayDone() {
	vector <tuple <int, string, ptime, ptime, string>>::iterator iter, iter2;
	int lineNo = 1;
	int floating = 0;
	ptime nullDate(not_a_date_time);
	iter2 = UImemory.begin();

	bool overdue = false;

	setColour(3);
	std::cout << "=====================================================================================================================================" << endl;
	setColour(14);
	std::cout << "\t These are the tasks that have been completed"<< endl;
	setColour(3);
	std::cout << "=====================================================================================================================================" << endl;
	setColour(15);
	
	
	bool noTaskDisplay = false;

	for (iter = UImemory.begin(); iter != UImemory.end(); iter++)
	{

		if (to_simple_string(get<2>(*iter)).substr(0, 11) != to_simple_string(get<2>(*iter2)).substr(0, 11) && get<2>(*iter2) != nullDate && get<2>(*iter) != nullDate) {
			setColour(3);
			std::cout << "=====================================================================================================================================" << endl; //different date
			setColour(15);
		}


		if (get<2>(*iter) == nullDate) { //only print out header for first floating task
			if (floating == 0) {

				setColour(3);
				if (!noDateTasks()) {
					std::cout << "=====================================================================================================================================\n\n\n" << endl;
				}
				std::cout << "=====================================================================================================================================" << endl;
				setColour(8);
				std::cout << setw(1) << "\t The tasks below had no deadline but are completed" << endl;
				setColour(3);
				std::cout << "=====================================================================================================================================" << endl; //different date
				setColour(13);
				std:: cout << "No." << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << "Task" << endl;
				setColour(9);
				std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
				setColour(15);

			}
			if (get<4>(*iter) == "done")
			{
				std::cout << lineNo << ".";
				if (lineNo < 10) {
					std::cout << " "; //for alignment
				}
				std::cout << setw(8) << "  " << setw(8) << "     --    ";
				floating++;
			}

		}
		else { //not floating task
			if (iter == UImemory.begin() || to_simple_string(get<2>(*iter)).substr(0, 11) != to_simple_string(get<2>(*iter2)).substr(0, 11)) {
				
					date::ymd_type ymd2 = (get<2>(*iter).date()).year_month_day();
					greg_weekday wd2 = (get<2>(*iter).date()).day_of_week();

					std::cout << setw(1) << " Deadline: [" << wd2.as_long_string() << " " << ymd2.month.as_long_string() << " " << ymd2.day << ", " << ymd2.year << "]" << endl; //print deadline if different date	
					setColour(3);
					std::cout << "=====================================================================================================================================" << endl; //different date
					setColour(13);
					std::cout << "No." << setw(8) << " " << setw(8) << "Time duration" << setw(8) << " " << setw(8) << left << "Task" << endl;
					setColour(9);
					std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
					setColour(15);
				
			}


			if (to_simple_string(get<2>(*iter)).substr(12, 8) == "23:59:59"  && get<4>(*iter) == "done") { //this is a deadline task
				std::cout << lineNo << ".";
				if (lineNo < 10){
					std::cout << " "; //for alignment
				}
				std::cout << setw(8) << "  " << setw(8) << left << "     --    ";//deadline tasks don't have time duration, end at 23:59
			}
			else if (to_simple_string(get<2>(*iter)).substr(18, 2) == "01"  && get<4>(*iter) == "done"){ // TimeTask1
				std::cout << lineNo << ".";
				if (lineNo < 10){
					std::cout << " "; //for alignment
				}
				std::cout << setw(8) << "  " << setw(8) << left << "00:00-" + to_simple_string(get<2>(*iter)).substr(12, 5);
			}
			else { //TimeTask2
				if (get<4>(*iter) == "done"){
					std::cout << lineNo << ".";
					if (lineNo < 10){
						std::cout << " "; //for alignment
					}
					std::cout << setw(8) << " " << setw(8) << left << to_simple_string(get<2>(*iter)).substr(12, 5) + "-" + to_simple_string(get<3>(*iter)).substr(12, 5);
				}
			}

		}

		if (get<4>(*iter) == "done") {
			std::cout << setw(10) << " " << setw(10) << left << get<1>(*iter) << endl; //print out Task
		}

		if (iter != UImemory.begin()) {
			iter2++;
		}
		overdue = false;
		if (get<4>(*iter) == "done") {
			lineNo++;
			noTaskDisplay = true;
		}
	}
	if (!noTaskDisplay)
	{
		setColour(10);
		std::cout << "There are no tasks to display" << endl;
	}
	setColour(3);
	std::cout << "=====================================================================================================================================" << endl << endl;
	setColour(15);
}
*/