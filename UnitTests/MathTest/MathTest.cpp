#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DubEngine::DEMath;

namespace MathTest
{
	TEST_CLASS(MathTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			Vector3 v;
			Assert::AreEqual(v.x, 0.0f);
			Assert::AreEqual(v.y, 0.0f);
			Assert::AreEqual(v.z, 0.0f);
		}
	};
}
