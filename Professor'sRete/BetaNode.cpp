#include "BetaNode.h"

BetaNode::BetaNode()
{
}

BetaNode::BetaNode(int id_given, string condition)
{
	int itt = 0;

	id = id_given;

	char* str = (char*)malloc(100);
	strcpy(str, condition.c_str());
	// Returns first token  
	char* token = strtok(str, " ");

	// Keep printing tokens while one of the 
	// delimiters present in str[].
	leftSource = token;
	while (token != NULL)
	{
		//printf("%s\n", token);
		token = strtok(NULL, " ");
		if (itt == 0)
			thisCondition = token;
		else if (itt == 1)
			rightSource = token;
		else if (itt == 3)
			thisProduct = token;
		itt++;
	}
}

string BetaNode::getType()
{
	return "Beta";
}

int BetaNode::getID()
{
	return id;
}

int BetaNode::testBetaNode(vector<pair<int, int>> WME, vector<pair<int, int>> WME1)
{
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}
	return 0;
}

int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, int>> WME1)
{
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}
	return 0;
}

int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, string>> WME1)
{
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}
	return 0;
}

int BetaNode::addBetaPair(BetaNode* pair)
{
	int isExist = checkBeta(pair);
	if (isExist == 1)
		return 1;
	else {
		listOfBetaPair.push_back(pair);
		return 1;
	}

	return -1;
}

int BetaNode::checkBeta(BetaNode* pair)
{
	for (int i = 0; i < listOfBetaPair.size(); i++) {
		if (listOfBetaPair[i] == pair)
			return 1;
	}
	return 0;
}

int BetaNode::ClearConnection()
{
	betaPair = NULL;
	terminalPair = NULL;
	return 1;
}

int BetaNode::ResetNode()
{
	ClearConnection();
	testRes = {};
	listOfBetaPair = {};
	return 0;
}
