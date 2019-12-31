#pragma once
#include "Node.h"
#include "TerminalNode.h"
#include <string>

class BetaNode :
	public Node
{
public:
	vector<pair<int, string>> testRes;

	int id;
	BetaNode();
	BetaNode(int id, string condition);
	string thisCondition; //AND OR

	string leftSource;
	string rightSource;
	string thisProduct;
	string getType();

	//Connected to beta and terminal what
	BetaNode* betaPair;
	TerminalNode* terminalPair;
	vector<BetaNode *> listOfBetaPair;

	bool leftSourceBool = false, rightSourceBool= false;

	int getID();
	int testToken();
	//If both are alpha nodes
	int testBetaNode(vector<pair<int, int>> WME, vector<pair<int, int>> WME1);
	//If one of them is beta
	int testBetaNode(vector<pair<int, string>> WME, vector<pair<int, int>> WME1);
	//if both are beta nodes
	int testBetaNode(vector<pair<int, string>> WME, vector<pair<int, string>> WME1);

	//connecting beta & terminal
	int addBetaPair(BetaNode* pair);
	int checkBeta(BetaNode* pair);

	//Init function
	int ClearConnection();
	int ResetNode();
};

