#include "Bellman-Ford.h"

using namespace std;

int main()
{
	BelmanFord flight;

	flight.readFromFile();
	flight.bfAlgorithm();

	cout << "Enter the departure city: " << endl;
	string fromCity;
	getline(cin, fromCity);
	cout << "Enter the destination city: " << endl;
	string toCity;
	getline(cin, toCity);


	cout << "The best cost: " << flight.getCost(fromCity, toCity) << endl;
	cout << "Shortest path: " << flight.getPath(fromCity, toCity) << endl;

	return 0;
}