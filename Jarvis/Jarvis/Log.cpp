//@author A0111136Y-reused
#include "Log.h"
using namespace std;

void Log::clear() {
	ofstream file;
	file.open("log.txt", ios::trunc);
	file << "Log sequence: \n";
	file.close();
}

void Log::log(string input) {
	file.open("log.txt", ios::app);

	file << input << "\n";

	file.close();
}

void Log::endLog() {
	file.open("log.txt", ios::app);

	file << "\n";

	file.close();
}