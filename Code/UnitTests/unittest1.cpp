#include "stdafx.h"
#include "CppUnitTest.h"
#include <assert.h>
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

	};
}