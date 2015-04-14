//@author A0118904E
#include "WrongFormatCommand.h"

using namespace std;
const string WRONG = "Error: Incorrect format of command. Type in help to view all commands supported";

WrongFormat::WrongFormat() {

}

string WrongFormat::execute(string fileName,string fileData) {
	return WRONG;
}