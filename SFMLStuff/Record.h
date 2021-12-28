#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Record{
private:
	int _nTurns;
	std::vector <std::string> history;
public:

	Record(){
		_nTurns = 0;
		history.clear();
	}

	Record(std::string filePath){
		loadFromFile(filePath);
	}

	void addMove(std::string str){
		history.push_back(str);
	}

	void saveToFile(std::string filePath){
		std::ofstream f(filePath);
		f << _nTurns << '\n';
		for (int i = 0; i < _nTurns; i++)
			f << history[i] << '\n';
		f.close();
	}

	void loadFromFile(std::string filePath){
		history.clear();
		std::ifstream f(filePath);
		f >> _nTurns;
		history.resize(_nTurns);
		for (int i = 0; i < _nTurns; i++)
			f >> history[i];
		f.close();
	}

	void alo(){
		std::cout << "alo\n";
	}

};
