#include <fstream>
#include "BFList.h"
#include  <limits>
#include <string>

using namespace std;

class BelmanFord
{
private:
	size_t cities; 
	BFList<string> listOfCities; 
	int* matrix; 
	string* pathsMatrix; 

public:
	BelmanFord()
	{
		cities = 0;
	}
	BelmanFord(size_t size)
	{
		matrix = new int[size];
		pathsMatrix = new string[size];
		cities = size;
	}

	~BelmanFord() 
	{
		delete[] pathsMatrix;
		delete[] matrix;
		cities = 0;
		listOfCities.~BFList();
	}

	void readFromFile() 
	{
		setlocale(LC_ALL, "Russian");
		string temp = "";
		char currChar;
		int declarationPart = 0;
		int matrixSize = 0;
		int prev;
		int curr;

		string fromCity = "";
		string toCity = "";
		ifstream readCities("input.txt");
		if (!readCities.is_open()) cout << "Incorrect file name" << endl;
		else if (readCities.peek() != EOF)
		{
			readCities.get(currChar);
			while (!readCities.eof())
			{
				if (currChar == '\n')
				{
					declarationPart = 0;
					temp = "";
				}
				if (currChar == ';')
				{
					if (declarationPart == 0 || declarationPart == 1)
					{
						if (listOfCities.isInList(temp) == INT_MAX)
						{
							listOfCities.push_back(temp);
						}
					}
					if (declarationPart == 2 || declarationPart == 3)
					{

					}
					temp = "";
					declarationPart++;
				}
				if ((currChar != ';') && (currChar != '\n'))
				{
					temp += currChar;
				}
				readCities.get(currChar);
			}
			readCities.close();
			cities = listOfCities.get_size();
			matrixSize = cities;
			matrix = new int[(matrixSize) * (matrixSize)];  
			pathsMatrix = new string[(matrixSize) * (matrixSize)];

			for (int i = 0; i < matrixSize; i++) 
			{
				for (int j = 0; j < matrixSize; j++)
				{
					if (i == j)
					{
						matrix[i * (matrixSize)+j] = 0;
						pathsMatrix[i * (matrixSize)+j] = "";
					}
					else
					{
						matrix[i * (matrixSize)+j] = INT_MAX;
						pathsMatrix[i * (matrixSize)+j] = "";
					}
				}
			}
			declarationPart = 0;
			temp = "";
			ifstream readPaths("input.txt"); readCities.get(currChar);
			if (!readPaths.is_open()) cout << "File Not open" << endl;
			else if (readPaths.peek() != EOF)
			{
				readPaths.get(currChar);
				while (!readPaths.eof())
				{
					if (currChar == '\n')
					{
						if (temp != "N/A")
						{
							matrix[curr * (matrixSize)+prev] = stoi(temp);
							pathsMatrix[curr * (matrixSize)+prev] = " to " + fromCity;
						}
						prev = 0;
						curr = 0;
						fromCity = "";
						toCity = "";

						declarationPart = 0;
						temp = "";
					}
					if (currChar == ';')
					{
						if (declarationPart == 0 || declarationPart == 1)
						{
							if (declarationPart == 0)
							{
								prev = listOfCities.isInList(temp);
								fromCity = temp;
							}
							if (declarationPart == 1)
							{
								curr = listOfCities.isInList(temp);
								toCity = temp;
							}
						}
						if (declarationPart == 2)
						{
							if (temp != "N/A")
							{
								matrix[prev * (matrixSize)+curr] = stoi(temp);
								pathsMatrix[prev * (matrixSize)+curr] = " to " + toCity;
							}
						}
						declarationPart++;
						temp = "";
					}
					if ((currChar != ';') && (currChar != '\n'))
					{
						temp += currChar;
					}
					readPaths.get(currChar);
				}
			}
			readPaths.close();
		}
	}

	void bfAlgorithm()
	{
		for (int k = 0; k < cities; k++)
		{
			for (int i = 0; i < cities; i++)
			{
				for (int j = 0; j < cities; j++)
				{
					if (matrix[i * (cities)+k] != INT_MAX && matrix[k * (cities)+j] != INT_MAX)
					{
						if (matrix[i * (cities)+j] <= matrix[i * (cities)+k] + matrix[k * (cities)+j])
						{
							matrix[i * (cities)+j] = matrix[i * (cities)+j];
							pathsMatrix[i * (cities)+j] = pathsMatrix[i * (cities)+j];
						}

					}
					if (matrix[i * (cities)+k] != INT_MAX && matrix[k * (cities)+j] != INT_MAX)
					{
						if (matrix[i * (cities)+j] > matrix[i * (cities)+k] + matrix[k * (cities)+j])
						{
							matrix[i * (cities)+j] = matrix[i * (cities)+k] + matrix[k * (cities)+j];
							pathsMatrix[i * (cities)+j] = pathsMatrix[i * (cities)+k] + pathsMatrix[k * (cities)+j];
						}

					}

				}

			}
		}

	}
	string getCost(string fromCity, string toCity)
	{
		if (matrix[listOfCities.isInList(fromCity) * (listOfCities.get_size()) + listOfCities.isInList(toCity)] == INT_MAX)
		{
			return "There is no such route";
		}
		else
		{
			return to_string(matrix[listOfCities.isInList(fromCity) * (listOfCities.get_size()) + listOfCities.isInList(toCity)]);

		}
	}

	string getPath(string fromCity, string toCity)
	{
		if (matrix[listOfCities.isInList(fromCity) * (listOfCities.get_size()) + listOfCities.isInList(toCity)] == INT_MAX)
		{
			return "There is no such route";
		}
		else
		{
			return fromCity + pathsMatrix[listOfCities.isInList(fromCity) * (listOfCities.get_size()) + listOfCities.isInList(toCity)];

		}
	}

};
