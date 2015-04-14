//@author A0118904E
#include "CommandType.h"

using namespace std;

CommandType::CommandType(Command* commandObject) {
	C1 = commandObject;
}

CommandType::CommandType() {

}

CommandType::~CommandType() {

}

string CommandType::run(string fileName,string filePath) {
	return C1->execute(fileName,filePath);
}