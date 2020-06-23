#include<iostream>
#include"DijkstraAlgorithm.h"
#include <fstream>
#include"input_data_function.h"
using namespace std;



int main() {
	try {
		setlocale(LC_ALL, "RUS");
		ifstream vvod("input.txt");
		int* path = NULL;//пути
		int* d = NULL;//расстояния от стартовой вершины
		List<string>* list_fly = new List<string>();
		string city_Start;
		string city_End;
		InputInFile(list_fly, vvod);
		cout << "Рейсы: " << endl;
		for (int i = 0; i < list_fly->get_size(); i++)
			cout << list_fly->at(i) << endl;
		cout << "Введите город отправления" << endl;
		getline(cin, city_Start);
		cout << "Введите город прибытия" << endl;
		getline(cin, city_End);
		AdjList* adj = new AdjList(list_fly);
		/////////////////////////////////////////////////////////////списки смежгости
		cout << adj->DijkstraAlgo(city_Start, city_End);
		///////////////////////////////////////////////////////
	}
	catch (exception & ex) {
		cout << ex.what() << endl;
	}
	system("pause");
}