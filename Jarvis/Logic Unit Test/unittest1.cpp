#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicUnitTest
{		
	TEST_CLASS(LOGIC_TEST)
	{
	public:
		
		TEST_METHOD(EXECUTE_COMMAND_TEST)
		{
			Logic L1;
			stack <string> userStack;
			userStack.push("trial 1");
			userStack.push("trial 2");
			L1.setStack(userStack);
			string expectedDisplay = "trial 2\ntrial 1\n";
			string actualDisplay;
			stack <string> logicStack = L1.getStack();
			while(!logicStack.empty()) {
				actualDisplay = actualDisplay + logicStack.top() + "\n";
				logicStack.pop();
			}
			
			Assert::AreEqual <string> (expectedDisplay,actualDisplay);
		}

	};
}