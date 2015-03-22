#include "Display.h"


using namespace std;

Display::Display() {

}

Display::Display(Task taskObject) {
	T1 = taskObject;
}

Display::~Display() {

}

string Display::execute(string fileName,string filePath) {
	
	if(T1.getKeywords()=="") {
		return S1.readFile(fileName,filePath);
	}

	else {
		Search S2(T1);
		return S2.executeSearch(fileName,filePath);
	}

}