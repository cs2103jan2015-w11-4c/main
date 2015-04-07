#include "WrongFormatCommand.h"

using namespace std;

WrongFormat::WrongFormat() {

}

string WrongFormat::execute(string fileName,string fileData) {
	return "Error: Incorrect format of command. Type in *?* to view all commands supported";
}