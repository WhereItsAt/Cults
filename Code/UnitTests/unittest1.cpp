#include "stdafx.h"
#include "CppUnitTest.h"
#include <assert.h>
#include <sstream>
#include "..\Cults-VS2017\GameMap.h"
#include "..\Cults-VS2017\GameMap.cpp"
#include "..\Cults-VS2017\MapTile.h"
#include "..\Cults-VS2017\MapTile.cpp"
#include "..\Cults-VS2017\TileType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			GameMap map;
			int rand = map.getRandomNumber(0, 1);
			Assert::IsTrue(rand >= 0 && rand <= 1);
		}

		TEST_METHOD(TestMethod2)
		{
			// TODO: Your test code here
			GameMap map;
			MapTile* start = new MapTile("city", true, 12, 50);
			MapTile* end = new MapTile("city", true, 49, 27);
			double got = map.getEuclideanDistance(start, end);
			double expected = 43.566;
			std::ostringstream strs;
			strs << "result: " << got << ". expected: " << expected;
			Logger::WriteMessage(strs.str().c_str());
			//Assert::IsTrue(got == expected);
			Assert::AreEqual(got, expected, 0.05);
		}
	};
}