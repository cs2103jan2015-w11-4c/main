#include "Clear.h"


using namespace std;

Clear::Clear() {

}

Clear::~Clear() {

}

string Clear::execute(string fileName) {

	string blankFile="";
	S1.replaceFileData(blankFile,fileName);
	return "The file has been cleared\n";

}