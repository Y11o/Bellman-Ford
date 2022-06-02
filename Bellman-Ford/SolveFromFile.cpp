#pragma once
#include <fstream>
#include "Bellman-Ford.h"
#include "Map.h"

void solveFromFile() {

    string input;
    ifstream ifs;

	string fileName;
	cout << "Input the name of file with list of flights" << endl;
	cin >> fileName;
    ifs.open(fileName);
	if (ifs.bad() == true)
	{
		cout << "Error! Incorrect file name" << endl;
	}
    getline(ifs, input, '\0');
    ifs.close();

    struct Flight {
        Flight* next = nullptr;
        string departure;
        string destination;
        size_t currToNext = ULLONG_MAX;
        size_t back = ULLONG_MAX;
    };

    Map <string, size_t>* cities = new Map<string, size_t>;
    Flight* route = new Flight;
    Flight* currRoute = route;
    string currWord = "";
    int declarationPart = 0;
    for (int curr = 0; curr < input.length(); curr++) {
		if (input[curr] == ';' || input[curr] == '\n') {
			switch (declarationPart % 4)
			{
			case 0: 
				currRoute->departure = currWord;
				try {
					cities->insert(currWord, cities->getSize());
				}
				catch (runtime_error e) {
					
				}
				break;
			case 1: 
				currRoute->destination = currWord;
				try {
					cities->insert(currWord, cities->getSize());
				}
				catch (runtime_error e) {
				}
				break;
			case 2: 
				if (currWord == "N/A") currRoute->currToNext = ULLONG_MAX;
				else currRoute->currToNext = stoull(currWord);
				break;
			case 3: 
				if (currWord == "N/A") currRoute->back = ULLONG_MAX;
				else currRoute->back = stoull(currWord);
				currRoute->next = new Flight;
				currRoute = currRoute->next;
				break;
			}
			if (declarationPart % 4 == 3) {
				break;
			}
			currWord = "";
			declarationPart++;
		}
		else currWord += input[curr];
    }

	BellmanFord* graph = new BellmanFord(cities->getSize());
	currRoute = route;
	do {
		graph->edge(cities->find(currRoute->departure), cities->find(currRoute->destination), currRoute->currToNext, currRoute->back);
		currRoute = currRoute->next;
	} while (currRoute != nullptr);

	string fromCity;
	string toCity;

	cout << "Input departure city.." << endl;
	getline(cin, fromCity);
	cout << "Input destination city.." << endl;
	getline(cin, toCity);

	cout << "The cheapest way is" << endl;

	BellmanFord::Path* path = graph->solveBF(cities->find(fromCity), cities->find(toCity));
	BellmanFord::Vertex* cheapest = path->start;
	do
	{
		cout << cities->find(cheapest->node) << endl;
		cheapest = cheapest->pNext;
	} while (cheapest != nullptr);
	cout << "Route's length is " << path->pathLenght << endl;
}