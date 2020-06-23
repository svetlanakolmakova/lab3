#pragma once
#include<string>
#include "list.h"
#include "map.h"
class AdjList {
	class Vertex {
	public:
		Vertex(int index_City = 0, double price = 0) :index_City(index_City), price(price) {}
		int index_City;
		double price;
	};
public:
	AdjList(List<string>* data) {
		graph = new List<Vertex>();
		map_index_to_name_City = new Map<int, string>();
		map_City_name_to_index = new Map<string, int>();
		int N = data->get_size();
		int index_city = 0;
		for (int i = 0; i < N; i++) {//заполнили  все индексы разных городов и считаем их кол-во
			string CurrentString = data->at(i);
			int current = CurrentString.find(';');//первое вхождение ;
			int current1 = CurrentString.find(';', current + 1);//второ вхождение ;
			string str_name_city1 = CurrentString.substr(0, current);//получаем первый город
			string str_name_city2 = CurrentString.substr(current + 1, current1 - current - 1);//получаем второй город
			str_name_city2.erase(0, 1);//удаляем пробел
			if (!map_City_name_to_index->is_in_map(str_name_city1)) {
				map_City_name_to_index->insert(str_name_city1, index_city);
				map_index_to_name_City->insert(index_city, str_name_city1);
				index_city++;
			}
			if (!map_City_name_to_index->is_in_map(str_name_city2)) {
				map_City_name_to_index->insert(str_name_city2, index_city);
				map_index_to_name_City->insert(index_city, str_name_city2);
				index_city++;
			}
		}
		/////////////////////////////////////////////////////////////////////////////
		size = index_city;//длина основного списка
		graph = new List<Vertex>[size];
		//////////////////////////////////////////////////////////////////////////////заполняем список цен(смежности)
		for (int i = 0; i < N; i++) {
			int price_1_to_2 = INF;
			int price_2_to_1 = INF;
			string CurrentString = data->at(i);
			int current = CurrentString.find(';');//первое вхождение ;
			int current1 = CurrentString.find(';', current + 1);//второе вхождение ;
			int current2 = CurrentString.find(';', current1 + 1);//3 вхождение ;
			int current3 = CurrentString.find(';', current2 + 1);//4 вхождение ;
			string str_name_city1 = CurrentString.substr(0, current);//получаем первый город
			string str_name_city2 = CurrentString.substr(current + 1, current1 - current - 1);//получаем второй город
			str_name_city2.erase(0, 1);//удаляем пробел
			//cout << stof(CurrentString.substr(current1 + 2, current2 - 2 - current1)) << 'f';
			if (CurrentString.substr(current1 + 2, current2 - 2 - current1) != "N/A")
				price_1_to_2 = stof(CurrentString.substr(current1 + 2, current2 - 2 - current1));
			if (CurrentString.substr(current2 + 2, current3 - 1) != "N/A")
				price_2_to_1 = stoi(CurrentString.substr(current2 + 2, current3 - 2 - current2));
			if (price_1_to_2 != INF) {
				Vertex v1(map_City_name_to_index->find(str_name_city2), price_1_to_2);//вркменная вершина для добавления
				graph[map_City_name_to_index->find(str_name_city1)].push_back(v1);
			}
			if (price_2_to_1 != INF) {
				Vertex v2(map_City_name_to_index->find(str_name_city1), price_2_to_1);//вркменная вершина для добавления
				graph[map_City_name_to_index->find(str_name_city2)].push_back(v2);
			}
		}
	}
	string DijkstraAlgo(string city_Start, string city_End) {
		if (city_Start != city_End) {
			string answer;
			while (!map_City_name_to_index->is_in_map(city_Start)) {
				cout << "The departure city is missing, enter it again" << endl;
				cin >> city_Start;
			}
			while (!map_City_name_to_index->is_in_map(city_End)) {
				cout << "The arrival city is missing, enter it again" << endl;
				cin >> city_End;
			}
			int index_city = 0;
			int index_start_vertex = map_City_name_to_index->find(city_Start);//находим индекс города отправления
			bool* visited = new bool[size];//заполнить все false
			int* distance = new int[size];//расстояния от стартовой вершины
			for (int i = 0; i < size; i++) {//заполняем бесконечно большими числами(пока несуществкюшие расстояния) и метки посещения обнуляем
				distance[i] = INF;
				visited[i] = false;
			}
			distance[index_start_vertex] = 0;//вершина начала пути всегда ноль(откуда отсчитываем)
			int* path = new int[size];//предки (последовательность краткого пути)
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < size; ++i) {
				int vertex = -1;
				for (int j = 0; j < size; ++j)
					if (!visited[j] && (vertex == -1 || distance[j] < distance[vertex]))
						vertex = j;
				if (distance[vertex] == INF)
					break;
				visited[vertex] = true;
				for (size_t j = 0; j < graph[vertex].get_size(); ++j) {
					int to = graph[vertex].at(j).index_City,
						len = graph[vertex].at(j).price;
					if (distance[vertex] + len < distance[to]) {
						distance[to] = distance[vertex] + len;
						path[to] = vertex;
					}
				}
			}
			int End_index = map_City_name_to_index->find(city_End);//поиск индекса города прибытия
			int Start_index = map_City_name_to_index->find(city_Start);
			if (distance[End_index] != INF) {
				List<int>* path_current = new List<int>();
				for (int v = End_index; v != Start_index; v = path[v])
					path_current->push_back(v);
				path_current->push_back(Start_index);
				path_current->reverse();
				answer += "Route:\n";
				string cur;
				for (int i = 0; i < path_current->get_size(); i++) {
					cur += "->";
					cur += map_index_to_name_City->find(path_current->at(i)) + ' ';
				}
				cur.erase(0, 2);
				answer += cur + "\nThe best route for the price:" + to_string(distance[End_index]) + '\n';
			}
			else {
				answer = "This route can't be built, try waiting for the flight schedule for tomorrow!";
			}
			return answer;
		}
		else throw exception("End city can't be equal to start city");
	}
private:
	List<Vertex>* graph;
	Map<string, int>* map_City_name_to_index;
	Map<int, string>* map_index_to_name_City;
	int size;
	const int INF = INT_MAX;
};
