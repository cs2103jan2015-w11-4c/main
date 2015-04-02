#include "Search.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

const string IDENTIFIERS = ".,!? ";

Search::Search() {

}

Search::Search(Task taskObject) {
	T1 = taskObject;
}

Search::~Search() {

}

string Search::execute(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	string linesWithWords="" ;
	string keywordsToSearch = T1.getKeywords();
	string line,token;
	vector <string> tokens;
	string delimiter = "/ ";
	bool isFound;
	istringstream in(fileData);
	while(getline(in, line)) {
		istringstream word(keywordsToSearch);
		while (word>>token) {
			boost::trim(token);
			tokens = extractWord(line,delimiter);
			while(!tokens.empty()) {
				boost::trim(tokens.back());
				if(changeToLowerCase(tokens.back())==changeToLowerCase(token)) {
					linesWithWords = linesWithWords + line + "\n";
					isFound=true;
					break;
				}
				else {
					isFound=false;
				}
				tokens.pop_back();
			
			}
			if(isFound==true)
				break;
		}
    }

	if(linesWithWords=="") {
		return  "Error: The words * " + keywordsToSearch + " * do not exist in file"  + "\n"; 
	}
	else
	   return linesWithWords;
	

}

vector <string> Search::extractWord(string input,string delimiter) {
	vector<string> tokens;
	boost::split(tokens,input, boost::is_any_of(delimiter));
	return tokens;
}


string Search::executeSearch(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	string linesWithWords="" ;
	string keywordsToSearch = T1.getKeywords();
	string line,token;
	vector <string> tokens;
	string delimiter = "/";
	bool isFound;
	int count=0;
	istringstream in(fileData);
	while(getline(in, line)) {
		istringstream word(keywordsToSearch);
		while (word>>token) {
			tokens = extractWord(line,delimiter);
			while(!tokens.empty()) {
				if(changeToLowerCase(tokens.back())==changeToLowerCase(token)) {
					isFound=true;
					count++;
					break;
				}
				else {
					isFound=false;
				}
				tokens.pop_back();
			}
			if(isFound==false)
				break;
		}
			if(isFound)
				linesWithWords = linesWithWords + line + "\n";
    }

	   return linesWithWords;
	

}

string Search::changeToLowerCase(string input) {
	string lowerCase="";
	for(int i=0;i<input.size();i++) {
		if(input[i]>='A' && input[i]<='Z') {
			input[i] = tolower(input[i]);
			lowerCase = lowerCase + input[i];
		}
		else {
			lowerCase = lowerCase + input[i];
		}
	}
	return lowerCase;
}