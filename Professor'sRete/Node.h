#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
	int SuperNodeID;
	Node();
	virtual int getID() = 0;
	virtual string getType() = 0;
};

