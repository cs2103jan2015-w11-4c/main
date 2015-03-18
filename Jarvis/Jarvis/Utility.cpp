#include "Utility.h"
#include "assert.h"

const int Utility::SAME = 0;


bool Utility::stringToBool(string s) {
	if (s.compare("true") == 0 || s.compare("True") == 0) {
		return true;
	}
	return false;
}


string Utility::boolToString(bool b) {
	return b ? "true" : "false";
}

bool Utility::isValidCommand(Command::COMMAND_TYPE cmd) {
	return (cmd >= Command::COMMAND_TYPE::EXIT && cmd <= Command::COMMAND_TYPE::TASKADD);
}



Command::COMMAND_TYPE Utility::stringToCOMMAND_TYPE(string command) {
	if (isExit(command)) {
		return Command::COMMAND_TYPE::EXIT;
	}
	if (isAdd(command)) {
		return Command::COMMAND_TYPE::TASKADD;
	}
	if (isDelete(command)) {
		return Command::COMMAND_TYPE::TASKDELETE;
	}
	if (isUpdate(command)) {
		return Command::COMMAND_TYPE::TASKUPDATE;
	}
	if (isDisplay(command)) {
		return Command::COMMAND_TYPE::TASKDISPLAY;
	}
}

string COMMAND_TYPEToString(Command::COMMAND_TYPE cmd) {
	switch (cmd) {
	case Command::COMMAND_TYPE::EXIT:
		return Command::COMMAND_EXIT;
	case Command::COMMAND_TYPE::TASKADD:
		return Command::COMMAND_ADD;
	case Command::COMMAND_TYPE::TASKDELETE:
		return Command::COMMAND_DELETE;
	case Command::COMMAND_TYPE::TASKUPDATE:
		return Command::COMMAND_UPDATE;

	default:
		return Command::COMMAND_INVALID;
	}
}

bool Utility::isExit(string command) {
	return (command.compare(Command::COMMAND_EXIT) == SAME);
}
bool Utility::isAdd(string command) {
	return (command.compare(Command::COMMAND_ADD) == SAME);
}
bool Utility::isDelete(string command) {
	return (command.compare(Command::COMMAND_DELETE) == SAME);
}
bool Utility::isUpdate(string command) {
	return (command.compare(Command::COMMAND_UPDATE) == SAME);
}
bool Utility::isDisplay(string command) {
	return (command.compare(Command::COMMAND_DISPLAY) == SAME);
}

