#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JarvisTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AddTest)
		{
			string userInput = "add complete 2103 hw by 23:59";
			Logic L1;
			string fileName = "test.txt";
			stack <string> commandStack;
			commandStack.push(userInput);
			string filepath = "";
			string actualOutput = L1.executeCommand(userInput,commandStack,fileName,filepath);
			string expectedOutout = "Added successfully\n";
			Assert::AreEqual<string>(expectedOutout,actualOutput);
		}

		TEST_METHOD(ClearTest)
		{

			string fileName = "test2.txt";
			string filePath="";
			string userInput = "clear";
			stack <string> commandStack;
			commandStack.push(userInput);
			Logic L1;
			Storage S1;
			string actualOutput = L1.executeCommand(userInput,commandStack,fileName,filePath);
			string expectedOutout = "The file has been cleared\n";
			Assert::AreEqual<string>(expectedOutout,actualOutput);
		
		}


	};
}