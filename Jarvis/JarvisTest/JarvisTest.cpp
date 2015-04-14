#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//@author A0118904E
namespace JarvisTest //integration test
{		
	TEST_CLASS(JarvisTest)
	{
	public:
		
		TEST_METHOD(AddTestJarvis)
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

		TEST_METHOD(ClearTestJarvis)
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
//@author A0111136Y
namespace UItest 
{
	TEST_CLASS(UItest)
	{
	public:

		TEST_METHOD(noDateTasksTest) //noDateTasks returns true if there are no deadline or time tasks
		{
			UI ui;
			vector <tuple <int, string, ptime, ptime, string>> testVector;
			ptime d1(from_iso_string("20150809T235959"));
			ptime d2(not_a_date_time);
			UI::UImemory.clear();
			UI::UImemory.push_back(make_tuple(1, "buy apples", d1, d2, "incomplete")); //deadline tasks added, considered as date task
			bool noDateTasksPresent = ui.noDateTasks("incomplete"); //should return false since there is a date tasks in UImemory
			Assert::IsFalse(noDateTasksPresent);
		}

		TEST_METHOD(noTasksTodayTest) //noTasksToday returns true if all the tasks for the day are completed - if status is incomplete
		{
			UI ui;
			vector <tuple <int, string, ptime, ptime, string>> testVector;
			ptime d1(from_iso_string("20150809T235959"));
			ptime d2(not_a_date_time);
			UI::UImemory.clear();
			UI::UImemory.push_back(make_tuple(1, "buy apples", d1, d2, "done")); //deadline tasks added, considered as date task
			UI::UImemory.push_back(make_tuple(2, "buy pears", d1, d2, "incomplete"));
			bool AllTasksForTodayAreCompleted = ui.noTasksToday(d1.date(), "incomplete"); //should be false because for the same day with 2 tasks, 1 task left uncompleted
			Assert::IsFalse(AllTasksForTodayAreCompleted); 

		}
		
		TEST_METHOD(isFloatingTaskTest) //returns true if the taks is a floating task
		{
			UI ui;
			const string IDENTIFIERS = "/";
			vector <string> tempTokens;
			string line = "buy apples ///2015///////incomplete";
			boost::split(tempTokens, line, boost::is_any_of(IDENTIFIERS));
			bool isFloatingTask = ui.isFloating(tempTokens); 
			Assert::IsTrue(isFloatingTask);
		}

		TEST_METHOD(isDeadlineTaskTest) //returns true if the taks is a deadline task
		{
			UI ui;
			const string IDENTIFIERS = "/";
			vector <string> tempTokens;
			string line = "cs2013 v0.5 /13/apr/2015///////incomplete";
			boost::split(tempTokens, line, boost::is_any_of(IDENTIFIERS));
			bool isDeadlineTask = ui.isDeadline(tempTokens);
			Assert::IsTrue(isDeadlineTask);
		}

		TEST_METHOD(isTimeTask1Test) //returns true if the taks is time task 1, e.g. by 10:00
		{
			UI ui;
			const string IDENTIFIERS = "/";
			vector <string> tempTokens;
			string line = "buy fruits /9/aug/2015/10/00/////incomplete";
			boost::split(tempTokens, line, boost::is_any_of(IDENTIFIERS));
			bool isTimeTask1 = ui.isTimeTask1(tempTokens);
			Assert::IsTrue(isTimeTask1);
		}

		TEST_METHOD(isTimeTask2Test) //returns true if the taks is time task 2, e.g. from 11:00 to 11:30
		{
			UI ui;
			const string IDENTIFIERS = "/";
			vector <string> tempTokens;
			string line = "buy pears /9/aug/2015///09/00/10/00/incomplete";
			boost::split(tempTokens, line, boost::is_any_of(IDENTIFIERS));
			bool isTimeTask2 = ui.isTimeTask2(tempTokens);
			Assert::IsTrue(isTimeTask2);
		}
		
		TEST_METHOD(lowerCaseTest)
		{
			UI ui;
			string expected = "apple";
			string actual = "aPPlE";
			Assert::AreEqual<string>(expected, ui.lowerCase(actual));
		}
	};
}

namespace LogicTest
{
	TEST_CLASS(LogicTest)
	{
	public:

		TEST_METHOD(extractUserCommandTest)
		{
			Logic logic;
			string expected = "add";
			string actual = logic.extractUserCommand("add buy apples on 9 august");
			Assert::AreEqual<string>(expected, actual);
		}

		TEST_METHOD(clearTest)
		{
			Task t1;
			Clear clear(t1);
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "test.txt";
			clear.execute(fileName, filePath);
			ifstream readfile(filePath + fileName);
			Assert::IsTrue(readfile.peek() == std::ifstream::traits_type::eof());
		}

		TEST_METHOD(searchTest)
		{
			Task t1;
			t1.setKeywords("pears");
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "test.txt";
			string outputfile = filePath + fileName;
			ifstream readfile(filePath + fileName);
			string targetLine = "buy pears / 9 / aug / 2015///09/00/10/00/incomplete\n";
			string expected = targetLine;
			string extraLine = "buy fruits /9/aug/2015/10/00/////incomplete\n";
			
			ofstream myfile;
			myfile.open(outputfile.c_str(), ios::app);
			myfile << extraLine <<  targetLine;

			Search search(t1);
			string actual = search.execute(fileName,filePath);
			Assert::AreEqual<string>(expected, actual);

		}
	};
}


//@author A0116114X
namespace Storagetest
{
	TEST_CLASS(Storagetest)
	{
	public:

		TEST_METHOD(WriteFloatingTaskTest)
		{
			bool statusofadd;
			Storage s1;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\"; //change this to the user's desktop filepath
			string fileName = "test.txt";
			Task t1;
			t1.setDescription("eat dinner");
			statusofadd = s1.writeFile(t1, fileName, filePath);
			Assert::IsTrue(statusofadd);

		}

		TEST_METHOD(WriteDeadlineTaskTest) 
		{
			bool statusofadd;
			Storage s1;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "text.txt";
			Task t1;
			t1.setDescription("eat dinner");
			t1.setDate("18");
			t1.setMonth("December");
			t1.setYear("2016");
			statusofadd = s1.writeFile(t1, fileName, filePath);
			Assert::IsTrue(statusofadd);
			
		}

		TEST_METHOD(WriteTimedTaskTest)
		{
			bool statusofadd;
			Storage s1;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "text.txt";
			Task t1;
			t1.setDescription("eat dinner");
			t1.setDate("1");
			t1.setMonth("September");
			t1.setYear("2015");
			t1.setHour("10");
			t1.setMinute("32");
			statusofadd = s1.writeFile(t1, fileName, filePath);
			Assert::IsTrue(statusofadd);
		}

		TEST_METHOD(WritePeriodTimedTaskTest)
		{
			bool statusofadd;
			Storage s1;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "text.txt";
			Task t1;
			t1.setDescription("study for exam");
			t1.setDate("15");
			t1.setMonth("May");
			t1.setYear("2015");
			t1.setStartHour("10");
			t1.setStartMinute("32");
			t1.setEndHour("23");
			t1.setEndMinute("15");
			statusofadd = s1.writeFile(t1, fileName, filePath);
			Assert::IsTrue(statusofadd);
		}
		
		TEST_METHOD(ClearFileTest)
		{
			Storage s1;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "text.txt";
			ifstream readfile(filePath + fileName);
			Task t1;
			t1.setDescription("eat dinner");
			s1.writeFile(t1, fileName, filePath);
			s1.clearFile(fileName, filePath);
			Assert::IsTrue(readfile.peek() == std::ifstream::traits_type::eof());
		}
		
		//display all, update 1 tend flowers
		TEST_METHOD(UpdateFileTest1)
		{
			Storage s1;
			bool statusofadd;
			string filePath = "C:\\Users\\Gabriel\\Desktop\\";
			string fileName = "text.txt";
			ifstream readfile(filePath + fileName);
			Task t1;
			t1.setDescription("eat dinner");

			//t1.setNumber("1");			
			s1.writeFile(t1, fileName, filePath);
			statusofadd = s1.replaceFileData("eat dinner ///2015///////incomplete", fileName, filePath);
			Assert::IsTrue(statusofadd);
		} 

		//replaceFileData(string deletedData, string outputFile, string filePath)
	};
}
