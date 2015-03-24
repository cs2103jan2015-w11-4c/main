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
	string lowerCaseLine;
	string data="";
	istringstream word(keywordsToSearch);
	istringstream in(fileData);
	while (word>>token) {
		while(getline(in, line)) {
			lowerCaseLine = changeToLowerCase(line);
			if (lowerCaseLine.find(changeToLowerCase(token)) != string::npos) {
				linesWithWords = linesWithWords + line.substr(2) + "\n";
			}
		}
    }
	

   if(fileData=="") {
		return  "The words * " + keywordsToSearch + " * do not exist in file"  + "\n"; 
	}
	else {
		int i=1;
		istringstream in(linesWithWords);
		while(getline(in, line)) {
			data = data + to_string(i) + ". " + line + "\n";
			i++;
		}
		return data;
	}
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
	istringstream word(keywordsToSearch);
	bool isFound;
	istringstream in(fileData);
	while(getline(in, line)) {
		isFound=true;
		while (word>>token && isFound) {
			tokens = extractWord(line,delimiter);
			while(!tokens.empty()) {
				if(changeToLowerCase(tokens.back())==changeToLowerCase(token)) {
					isFound=true;
					break;
				}
				else {
					isFound=false;
				}
				tokens.pop_back();
				
			}
		}
		if(isFound)
			linesWithWords = linesWithWords + line + "\n";
    }
	

	if(linesWithWords=="") {
		return  "The words * " + keywordsToSearch + " * do not exist in file"  + "\n"; 
	}
	else
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