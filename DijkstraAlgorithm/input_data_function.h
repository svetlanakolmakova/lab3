#pragma once
#include<fstream>
#include"list.h"
#include<string>
void InputInFile(List<string>* data, ifstream& file) {//ввод из файла в список
	while (!file.eof()) {
		string s1;
		getline(file, s1);
		data->push_back(s1);
	}
}