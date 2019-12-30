#pragma once
#include "Node.h"
#include "BetaNode.h"
#include <string>
#include <cstdlib>

class AlphaNode :
	public Node
{
public:
	//Test Result
	vector<pair<int, int>> testRes;

	//connect to beta what
	BetaNode* betaPair;

	//Starter kit
	int id;
	int getID();
	string getType();
	AlphaNode();
	AlphaNode(int id, string condition);
	string getAlphaDataType();

	//Condition
	string thisDataType;
	string thisCondition;
	string thisVarLimit;

	//Test
	vector<pair<int, int>> testAlphaNode(vector<pair<int, int>> test_cases);
	void testAlphaAndSaveHere(vector<pair<int, int>> test_cases);
	int testSingleInAlpha(pair<int, int> test_case);
	bool testDataType(string condition);
};
