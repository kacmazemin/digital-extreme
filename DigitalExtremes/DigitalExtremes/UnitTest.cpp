#include "UnitTest.h"
#include "PathNode.h"

#include <string>


UnitTest::UnitTest()
{
	
}

UnitTest::~UnitTest()
{
}

void UnitTest::executeTest(const PathNodes& path, const int testNo)
{
	std::vector<std::string> pathNames;

	switch (testNo)
	{
		case 1 : 
			pathNames = {"Node4", "Node7"};
			break;
		case 2 :
			pathNames = { "Node6", "Node0", "Node4", "Node7"};
			break;
		case 3:
			pathNames = { "Node0", "Node4", "Node7", "Node5" };
			break;
		case 4:
			pathNames = { "Node3", "Node5", "Node7", "Node4", "Node1" };
			break;
		case 5:
			pathNames = {};
			break;
		default:
			break;
	}

	if (path.empty() && pathNames.empty())
	{
		printf("Test %d Successfull \n", testNo);
		return;
	}

	for (int i = 0; i < path.size(); i++)
	{
		if (path[i]->GetName() != pathNames[i])
		{
			printf("Test %d Fail!!\n", testNo);
			return;
		}
	}
	printf("Test %d Successfull \n", testNo);

}
