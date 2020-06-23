#include "pch.h"
#include "CppUnitTest.h"
#include"../DijkstraAlgorithm/DijkstraAlgorithm.h"
#include <fstream>
#include"../DijkstraAlgorithm/input_data_function.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDijkstra
{
	TEST_CLASS(UnitTestDijkstra)
	{
	public:
		
		TEST_METHOD(TestAvailablePath)
		{
			ifstream vvod("C:\\Users\\sveta\\Desktop\\lab3\\DijkstraAlgorithm\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Moscow";
			string city_End = "Saint-Peterburg";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "Route:\nMoscow ->Saint-Peterburg \nThe best route for the price:20\n";
			Assert::AreEqual(adj->DijkstraAlgo(city_Start, city_End), cur);
		}
		TEST_METHOD(TestUnavailablePath)
		{
			ifstream vvod("C:\\Users\\sveta\\Desktop\\lab3\\DijkstraAlgorithm\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Vladivostok";
			string city_End = "Moscow";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "This route can't be built, try waiting for the flight schedule for tomorrow!";
			Assert::AreEqual(adj->DijkstraAlgo(city_Start, city_End), cur);
		}
		TEST_METHOD(TestPathExeption)
		{
			try {
				ifstream vvod("C:\\Users\\sveta\\Desktop\\lab3\\DijkstraAlgorithm\\input.txt");
				List<string>* list_fly = new List<string>();
				string city_Start = "Vladivostok";
				string city_End = "Vladivostok";
				InputInFile(list_fly, vvod);
				AdjList* adj = new AdjList(list_fly);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(), "End city can't be equal to start city");
			}
		}
		TEST_METHOD(TestePath)
		{
			ifstream vvod("C:\\Users\\sveta\\Desktop\\lab3\\DijkstraAlgorithm\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Moscow";
			string city_End = "Khabarovsk";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "Route:\nMoscow ->Saint-Peterburg ->Khabarovsk \nThe best route for the price:34\n";
			Assert::AreEqual(adj->DijkstraAlgo(city_Start, city_End), cur);
		}
	};
}
