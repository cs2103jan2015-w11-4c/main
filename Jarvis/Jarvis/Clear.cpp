#include "Clear.h"


using namespace std;

string Clear::originalData;

Clear::Clear() {

}

Clear::~Clear() {

}

string Clear::execute(string fileName,string filePath) {

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