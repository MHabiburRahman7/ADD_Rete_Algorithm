#include "Utilities.h"

Utilities::Utilities()
{
}

vector<pair<string, string>> Utilities::tokenize(string temp)
{
	//example
	//If distance < 10000 and elevation > 12000 then danger_obj
	//if danger_obj and speed > 100 then just_danger

	vector<string> tempor;
	//int to determine the order
	//vector<pair<int, pair<string, string>>> conditionMade;
	vector<pair<string, string>> conditionMade;

	//Maybe we need it later
	AlphaNode tempAlpha;
	BetaNode tempBeta;

	tempor = {};
	conditionMade = {};

	char* str = (char*)malloc(500);
	strcpy(str, temp.c_str());
	// Returns first token  
	char* token = strtok(str, " ");
	int itt = 0;
	int ittMade = 0;

	if (itt == 0 && strcmp(ToUpper(token).c_str(), "IF") == 0) {
		itt++;
	}
	else if (itt == 0 && strcmp(ToUpper(token).c_str(), "IF") != 0) {
		return conditionMade;
	}

	// Keep printing tokens while one of the 
	// delimiters present in str[].
	while (token != NULL)
	{
		//printf("%s\n", token);
		token = strtok(NULL, " ");
		//strcpy(token, ToUpper(token).c_str());

		//considered alpha
		if (token == NULL) {
			string cond = {};
			//cout << "considered product " << tempor[0] << endl;
			conditionMade.push_back({ "Term", tempor[0]});
		}
		else if ((strcmp(ToUpper(token).c_str(), "AND") == 0 
			|| strcmp(ToUpper(token).c_str(), "THEN") == 0)
			&& tempor.size() > 1) {

			string cond = {};
			for (int i = 0; i < tempor.size(); i++) {
				cond += tempor[i];
				cond += " ";
			}
			//cout << "considered alpha " << cond << endl;

			conditionMade.push_back({ "Alpha", cond });

			tempor = {};
		}
		else if ((strcmp(ToUpper(token).c_str(), "AND") == 0 
			|| strcmp(ToUpper(token).c_str(), "THEN") == 0)
			&& tempor.size() == 1) {
			string cond = {};
			cond = tempor[0];
			//cout << "considered beta " << cond << endl;

			conditionMade.push_back({ "Beta", cond });

			tempor = {};
		}
		else if (itt > 0 && (strcmp(ToUpper(token).c_str(), "AND") != 0 
			|| (strcmp(ToUpper(token).c_str(), "THEN") != 0))) {
			tempor.push_back(token);
		}

		//token = strtok(NULL, " ");
		itt++;
	}

	return conditionMade;
}

string Utilities::ToUpper(string ori)
{
	for (int i = 0; i < ori.size(); i++) {
		ori[i] = toupper(ori[i]);
	}
	return ori;
}

string Utilities::ToLower(string ori)
{
	for (int i = 0; i < ori.size(); i++) {
		ori[i] = tolower(ori[i]);
	}
	return ori;
}
