#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "PathNode.h"

class PathNode;

class UnitTest
{
public:
	UnitTest();
	~UnitTest();

	void executeTest(const PathNodes& path, const int testNo = 0);
};


#endif //UNIT_TEST_H
