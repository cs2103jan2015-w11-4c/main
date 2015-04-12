#include "Clear.h"
#include <boost/algorithm/string.hpp>

using namespace std;

string Clear::originalData;
const string ERROR_CLEAR_KEYWORDS = "Error: Please enter *CLEAR* to clear your task list";

Clear::Clear(Task taskObject) {
	T1 = taskObject;
}

Clear::~Clear() {

}

string Clear::execute(string fileName,string filePath) {
	if(T1.getKeywords()!="") {
		return ERROR_CLEAR_KEYWORDS;
	}
	string blankFile="";
	setData(S1.readFile(fileName,filePath));
	S1.clearFile(fileName,filePath);
	return "The file has been cleared\n";

}

void Clear::setData(string data) {
	originalData = data;
}

string Clear::getData() {
	return originalData;
}