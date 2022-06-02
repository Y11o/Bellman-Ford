#include "pch.h"
#include "CppUnitTest.h"
#include "..\Bellman-Ford\Bellman-Ford.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BFTest
{
	TEST_CLASS(BFTest)
	{
	public:
		
		TEST_METHOD(BellmanFordTest)
		{
			BelmanFord flight;
			flight.readFromFile();
			flight.bfAlgorithm();
			string fromCity = "Khabarovsk";
			string toCity = "Saint-Petersburg";
			string bestCost = to_string(55);
			string algCost = flight.getCost(fromCity, toCity);
			Assert::AreEqual(bestCost, algCost);
			string str = "Khabarovsk to Moscow to Saint-Petersburg";
			Assert::AreEqual(str, flight.getPath(fromCity, toCity));
		}
	};
}
