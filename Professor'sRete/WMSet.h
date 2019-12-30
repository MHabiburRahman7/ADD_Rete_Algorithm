#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class WMSet
{
private:
	int matchWM = -1;

public:
	vector<pair<string, vector<pair<int, int>>>> data_content = {};
	//it should be --> speed <id = 1 val = 3| id = 2 val = ? | . . .>
	// --> elev <id = i val = ? | . . >

	void showSet();
	int checkAvailability(string check);

	int findMatch() {

	}

	int fireWM() {

	}

	int deleteMemory() {

	}

	int addMemory(string dataType, int id, int value);

	//vector<int>;
};

