#pragma once
#include<iostream>
#include <vector>

#include "AlphaNode.h"
#include "BetaNode.h"
#include "GraphOrNet.h"

using namespace std;

class Utilities
{
public:
	vector<AlphaNode> testAlpha;
	vector<BetaNode> testBeta;

	Utilities();
	
	//tokenizing
	vector<pair<string, string>> tokenize(string temp);

	string ToUpper(string ori);
	string ToLower(string ori);
};

