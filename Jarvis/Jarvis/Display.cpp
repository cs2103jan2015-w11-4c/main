#include "Display.h"


using namespace std;

Display::Display() {

}

Display::~Display() {

}

string Display::execute(string fileName) {

	return S1.readFile(fileName);
}