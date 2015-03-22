#include "CommandType.h"

using namespace std;

CommandType::CommandType(Command* commandObject) {

	C1 = commandObject;

}

CommandType::~CommandType() {

}

string CommandType::run(string fileName) {

	return C1->execute(fileName);

}