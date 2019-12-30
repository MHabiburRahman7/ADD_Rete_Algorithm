#pragma once
#include "AlphaNode.h"
#include "BetaNode.h"
#include "TerminalNode.h"
#include "WMSet.h"

using namespace std;

class GraphOrNet
{
public:
	GraphOrNet();

	//Where we store the nodes
	vector<AlphaNode> alphaList;
	vector<BetaNode> betaList;
	vector<TerminalNode> termList;

	//looks like we dont need this ._.
	vector<pair<AlphaNode*, BetaNode*>> adjAlphaBeta;
	vector<pair<BetaNode *, BetaNode *>> adjBetaBeta;
	vector<pair<BetaNode *, TerminalNode *>> adjBetaTerminal;

	//vector<pair<AlphaNode, BetaNode>> adjList;

	//FindMatch
	vector<int> findMatch(WMSet temp_wm);

	//Fire
	int tempFireWME(WMSet temp_wm);
	
	//Add Alpha or Beta
	int addCondition(string condition);
	int addAlpha(string condition);
	int addBeta(string condition);
	int addTerminal(string terminalName);

	//Delete Alpha or Beta
	int deleteBeta(BetaNode);
	int deleteAlpha(AlphaNode);

	//Building network
	int buildCurrentAlphaBeta();
	//int connectOneToOneNode(Node n1, Node n2);
	//int connectAlphatoBeta(AlphaNode a1, AlphaNode a2, BetaNode b1);
	//int connectNodeAlphaToBeta(Node n1, Node n2, Node n3);

	int connectTwoInputNode(AlphaNode &a1, AlphaNode &a2, BetaNode &b1);
	int connectTwoInputNode(BetaNode &b1, AlphaNode &a2, BetaNode &b2);
	int connectTwoInputNode(BetaNode &b1, BetaNode &b2, BetaNode &b3);
	int connectBetaToTerminal(BetaNode &b1, TerminalNode &t1);

	//miscellaneous, maybe we need it later
	void showAlpha();
	void showBeta();
	void showAll();
	void showAdjList();

	//find function
	int findAlpha(string dataType);
	int findBeta(string BCode);
	int findBetaBasedOnProduct(string product);
};

