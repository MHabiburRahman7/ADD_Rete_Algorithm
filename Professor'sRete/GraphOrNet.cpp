#include "GraphOrNet.h"

GraphOrNet::GraphOrNet()
{
}

vector<int> GraphOrNet::findMatch(WMSet temp_wm)
{
	vector<int> possible_match;
	vector<pair<int, int>> temp_result;
	
	//check alpha nodes
	for (int i = 0; i < temp_wm.data_content.size(); i++) {
		for (int j = 0; j < alphaList.size(); j++) {
			//test on alpha
			if (temp_wm.data_content[i].first == alphaList[j].thisDataType) {
				alphaList[j].testAlphaAndSaveHere(temp_wm.data_content[i].second);
				//activate the beta
				//searching all pair and activate it
				for (int k = 0; k < alphaList[j].listOfBetaPairs.size(); k++) {
					if (alphaList[j].listOfBetaPairs[k]->leftSourceBool == false)
						alphaList[j].listOfBetaPairs[k]->leftSourceBool = true;
					else
						alphaList[j].listOfBetaPairs[k]->rightSourceBool = true;

					if (alphaList[j].listOfBetaPairs[k]->leftSourceBool
						&& alphaList[j].listOfBetaPairs[k]->rightSourceBool) {
						int lAlpha = -1, rAlpha = -1;
						//find left alpha
						lAlpha = findAlpha(alphaList[j].listOfBetaPairs[k]->leftSource);
						//find right alpha
						rAlpha = findAlpha(alphaList[j].listOfBetaPairs[k]->rightSource);
						//test beta Node
						alphaList[j].listOfBetaPairs[k]->testBetaNode(alphaList[lAlpha].testRes, alphaList[rAlpha].testRes);
					}
				}

				//if (alphaList[j].betaPair->leftSourceBool == false)
				//	alphaList[j].betaPair->leftSourceBool = true;
				//else
				//	alphaList[j].betaPair->rightSourceBool = true;
				//if (alphaList[j].betaPair->leftSourceBool && alphaList[j].betaPair->rightSourceBool) {
				//	int lAlpha = -1, rAlpha = -1;
				//	//find left alpha
				//	lAlpha = findAlpha(alphaList[j].betaPair->leftSource);
				//	//find right alpha
				//	rAlpha = findAlpha(alphaList[j].betaPair->rightSource);
				//	//test beta Node
				//	alphaList[j].betaPair->testBetaNode(alphaList[lAlpha].testRes, alphaList[rAlpha].testRes);
				//}

				/*
				for (int k = 0; k < adjAlphaBeta.size(); k++) {
					if (adjAlphaBeta[k].first->id == alphaList[i].id) {

						if (adjAlphaBeta[k].second->leftSourceBool == false)
							adjAlphaBeta[k].second->leftSourceBool = true;
						else
							adjAlphaBeta[k].second->rightSourceBool = true;

						//if it is ready to test then go
						if (adjAlphaBeta[k].second->leftSourceBool && adjAlphaBeta[k].second->rightSourceBool) {
							int lAlpha =-1, rAlpha = -1;
							//find left alpha
							lAlpha = findAlpha(adjAlphaBeta[k].second->leftSource);
							//find right alpha
							rAlpha = findAlpha(adjAlphaBeta[k].second->rightSource);
							//test beta Node
							adjAlphaBeta[k].second->testBetaNode(alphaList[lAlpha].testRes, alphaList[rAlpha].testRes);
						}

						break;
						//if (betaList[adjAlphaBeta[k].second->id].leftSourceBool == false)
						//	betaList[adjAlphaBeta[k].second->id].leftSourceBool = true;
						//else
						//	betaList[adjAlphaBeta[k].second->id].rightSourceBool = true;
						//break;
					}
				}*/
				break;
			}
		}
	}

	//check beta nodes
	//not the final one, i am thinking about building stack or queue to do traversing
	// due to time, i just make for loop
	for (int i = 0; i < betaList.size(); i++) {

		for (int j = 0; j < betaList[i].listOfBetaPair.size(); j++) {
			if (betaList[i].listOfBetaPair[j]->leftSourceBool == false)
				betaList[i].listOfBetaPair[j]->leftSourceBool = true;
			else
				betaList[i].listOfBetaPair[j]->rightSourceBool = true;

			if (betaList[i].listOfBetaPair[j]->leftSourceBool
				&& betaList[i].listOfBetaPair[j]->rightSourceBool
				&& betaList[i].listOfBetaPair[j]->testRes.empty()) {

				int lAlpha = -1;
				int lBeta = -1, rBeta = -1;
				//if alpha is on left or right
				lAlpha = findAlpha(betaList[i].listOfBetaPair[j]->leftSource);
				if (lAlpha == -1)
					lAlpha = findAlpha(betaList[i].listOfBetaPair[j]->rightSource);
				//find right or right beta
				lBeta = findBetaBasedOnProduct(betaList[i].listOfBetaPair[j]->leftSource);
				rBeta = findBetaBasedOnProduct(betaList[i].listOfBetaPair[j]->rightSource);

				//test beta Node
				//if left or right node is from alpha
				if (lAlpha != -1 && lBeta != -1)
					betaList[i].listOfBetaPair[j]->testBetaNode(betaList[lBeta].testRes, alphaList[lAlpha].testRes);
				else if (lAlpha != -1 && rBeta != -1)
					betaList[i].listOfBetaPair[j]->testBetaNode(betaList[rBeta].testRes, alphaList[lAlpha].testRes);
				//if both from beta node
				if (lBeta != -1 && rBeta != -1)
					betaList[i].listOfBetaPair[j]->testBetaNode(betaList[rBeta].testRes, betaList[lBeta].testRes);
			}
		}
		/*if (betaList[i].betaPair->leftSourceBool == false)
			betaList[i].betaPair->leftSourceBool = true;
		else
			betaList[i].betaPair->rightSourceBool = true;*/

		//if (betaList[i].betaPair->leftSourceBool && betaList[i].betaPair->rightSourceBool
		//	&& betaList[i].betaPair->testRes.empty()) {
		//	int lAlpha = -1;
		//	int lBeta = -1, rBeta = -1;
		//	//if alpha is on left or right
		//	lAlpha = findAlpha(betaList[i].betaPair->leftSource);
		//	if (lAlpha == -1)
		//		lAlpha = findAlpha(betaList[i].betaPair->rightSource);
		//	//find right or right beta
		//	lBeta = findBetaBasedOnProduct(betaList[i].betaPair->leftSource);
		//	rBeta = findBetaBasedOnProduct(betaList[i].betaPair->rightSource);

		//	//test beta Node
		//	//if left or right node is from alpha
		//	if (lAlpha != -1 && lBeta != -1)
		//		betaList[i].betaPair->testBetaNode(betaList[lBeta].testRes, alphaList[lAlpha].testRes);
		//	else if (lAlpha != -1 && rBeta != -1)
		//		betaList[i].betaPair->testBetaNode(betaList[rBeta].testRes, alphaList[lAlpha].testRes);
		//	//if both from beta node
		//	if (lBeta != -1 && rBeta != -1)
		//		betaList[i].betaPair->testBetaNode(betaList[rBeta].testRes, betaList[lBeta].testRes);
		//}
		break;

		//for (int j = 0; j < adjBetaBeta.size(); j++) {
		//	if (adjBetaBeta[j].first->leftSourceBool && adjBetaBeta[j].first->rightSourceBool) {
		//		if (!adjBetaBeta[j].second->leftSourceBool)
		//			adjBetaBeta[j].second->leftSourceBool = true;
		//		else
		//			adjBetaBeta[j].second->rightSourceBool = true;
		//		//if it is ready to test then go
		//		if (adjBetaBeta[j].second->leftSourceBool && adjBetaBeta[j].second->rightSourceBool 
		//			&& adjBetaBeta[j].second->testRes.empty()) {
		//			int lAlpha = -1;
		//			int lBeta = -1, rBeta = -1;
		//			//if alpha is on left or right
		//			lAlpha = findAlpha(adjBetaBeta[j].second->leftSource);
		//			if(lAlpha == -1)
		//				lAlpha = findAlpha(adjBetaBeta[j].second->rightSource);
		//			//find right or right beta
		//			lBeta = findBetaBasedOnProduct(adjBetaBeta[j].second->leftSource);
		//			rBeta = findBetaBasedOnProduct(adjBetaBeta[j].second->rightSource);

		//			//test beta Node
		//			//if left or right node is from alpha
		//			if(lAlpha != -1 && lBeta != -1)
		//				adjBetaBeta[j].second->testBetaNode(betaList[lBeta].testRes, alphaList[lAlpha].testRes);
		//			else if(lAlpha != -1 && rBeta != -1)
		//				adjBetaBeta[j].second->testBetaNode(betaList[rBeta].testRes, alphaList[lAlpha].testRes);
		//			//if both from beta node
		//			if(lBeta != -1 && rBeta != -1)
		//				adjBetaBeta[j].second->testBetaNode(betaList[rBeta].testRes, betaList[lBeta].testRes);
		//		}
		//		break;
		//	}
		//}
	}

	//check possible terminal node
	for (int i = 0; i < betaList.size(); i++) {
		if (betaList[i].leftSourceBool && betaList[i].rightSourceBool
			&& betaList[i].terminalPair != NULL)
			possible_match.push_back(i);
	}
/*	for (int i = 0; i < adjBetaTerminal.size(); i++) {
		if (adjBetaTerminal[i].first->leftSourceBool && adjBetaTerminal[i].first->rightSourceBool)
			possible_match.push_back(i);
	}*/

	return possible_match;
}

void GraphOrNet::testBFS(WMSet temp_wm)
{
	vector<pair<BetaNode*, int>> visitedMark;
	vector<AlphaNode*> pushedAlpha;
	vector<BetaNode*> pushedBeta;

	bool isDone = false;

	for (int i = 0; i < temp_wm.data_content.size(); i++) {
		for (int j = 0; j < alphaList.size(); j++) {
			//test on alpha
			if (temp_wm.data_content[i].first == alphaList[j].thisDataType) {
				alphaList[j].testAlphaAndSaveHere(temp_wm.data_content[i].second);
				//activate the beta
				//searching all pair and activate it
				for (int k = 0; k < alphaList[j].listOfBetaPairs.size(); k++) {
					if (alphaList[j].listOfBetaPairs[k]->leftSourceBool == false)
						alphaList[j].listOfBetaPairs[k]->leftSourceBool = true;
					else
						alphaList[j].listOfBetaPairs[k]->rightSourceBool = true;

					//check for duplicate
					bool isADuplicate = false;
					for (int l = 0; l < pushedBeta.size(); l++) {
						if (pushedBeta[l] == alphaList[j].listOfBetaPairs[k]) {
							isADuplicate = true;
							break;
						}
					}
					if (!isADuplicate) {
						pushedBeta.push_back(alphaList[j].listOfBetaPairs[k]);
						visitedMark.push_back({ alphaList[j].listOfBetaPairs[k], 0 });
					}
					//pushedBeta.push_back(alphaList[j].listOfBetaPairs[k]);
				}

				break;
			}
		}
	}
	
	while (!pushedBeta.empty()) {
		
		//for (int i = 0; i < pushedBeta.size(); i++) {
		////for (auto i = pushedBeta.begin(); i != pushedBeta.end(); ++i) {
		//	pushedBeta.erase(pushedBeta);
		//	if (pushedBeta[i]->leftSourceBool && pushedBeta[i]->rightSourceBool) {
		//		
		//	}
		//}

		if (pushedBeta[0]->leftSourceBool && pushedBeta[0]->rightSourceBool) {

			AlphaNode* leftA, * rightA;
			BetaNode* leftB, * rightB;

			//Decide the incoming left and right
			if (pushedBeta[0]->leftSourceType == "Alpha" && pushedBeta[0]->rightSourceType == "Alpha") {
				leftA = findAlphaAndReturnNode(pushedBeta[0]->leftSource);
				rightA = findAlphaAndReturnNode(pushedBeta[0]->rightSource);

				if(pushedBeta[0]->testRes.size() == 0)
					pushedBeta[0]->testBetaNode(leftA->testRes, rightA->testRes);
			}
			else if (pushedBeta[0]->leftSourceType == "Beta" && pushedBeta[0]->rightSourceType == "Alpha") {
				leftB = findBetaBasedOnProductAndReturnNode(pushedBeta[0]->leftSource);
				rightA = findAlphaAndReturnNode(pushedBeta[0]->rightSource);
				
				if (pushedBeta[0]->testRes.size() == 0)
					pushedBeta[0]->testBetaNode(leftB->testRes, rightA->testRes);
			}
			else if (pushedBeta[0]->leftSourceType == "Beta" && pushedBeta[0]->rightSourceType == "Beta") {
				leftB = findBetaBasedOnProductAndReturnNode(pushedBeta[0]->leftSource);
				rightB = findBetaBasedOnProductAndReturnNode(pushedBeta[0]->rightSource);

				if (pushedBeta[0]->testRes.size() == 0)
					pushedBeta[0]->testBetaNode(leftB->testRes, rightB->testRes);
			}

			//Activate successor node
			for (int i = 0; i < pushedBeta[0]->listOfBetaPair.size(); i++) {
				if (pushedBeta[0]->betaPair[i].leftSourceBool == false)
					pushedBeta[0]->betaPair[i].leftSourceBool = true;
				else
					pushedBeta[0]->betaPair[i].rightSourceBool = true;

				pushedBeta.push_back(&pushedBeta[0]->betaPair[i]);
			}

			//Mark the current node in visited mark
			for (int i = 0; i < visitedMark.size(); i++) {
				if (visitedMark[i].first == pushedBeta[0]) {
					visitedMark[i].second++;

					if (visitedMark[i].second >= 3)
						isDone = true;
					break;
				}
			}
		}

		pushedBeta.erase(pushedBeta.begin());

		if (isDone)
			break;
		//evaluate visited mark
		//for (int i = 0; i < visitedMark.size(); i++) {
		//	if (visitedMark[i].second >= 3)
		//		break;
		//}
	}

	int b;

}

int GraphOrNet::tempFireWME(WMSet temp_wm)
{
	//This is not the final version
	int key = 1;

	temp_wm.showSet();

	cout << "Result : " << endl;
	for (int i = 0; i < betaList[key].testRes.size(); i++) {
		cout << betaList[key].testRes[i].first << " - " << betaList[key].testRes[i].second << endl;
	}

	return 0;
}

int GraphOrNet::addCondition(string condition)
{
	char *str = (char*)malloc(100);
	strcpy(str, condition.c_str());
	// Returns first token  
	char* token = strtok(str, " ");

	// Keep printing tokens while one of the 
	// delimiters present in str[]. 
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, "-");
	}

	return 0;
}

int GraphOrNet::addAlpha(string condition)
{
	int id = alphaList.size();

	AlphaNode alp(id, condition);
	alphaList.push_back(alp);

	return 0;
}

int GraphOrNet::addBeta(string condition)
{
	int id = betaList.size();

	BetaNode btn(id, condition);
	betaList.push_back(btn);

	return 0;
}

int GraphOrNet::addTerminal(string terminalName)
{
	int id = termList.size();

	TerminalNode ter(id, terminalName);
	termList.push_back(ter);

	return 0;
}

AlphaNode GraphOrNet::addAlphaAndReturn(string condition)
{
	int id = alphaList.size();

	AlphaNode alp(id, condition);
	alphaList.push_back(alp);
	
	return alp;
}

BetaNode GraphOrNet::addBetaAndReturn(string condition)
{
	int id = betaList.size();

	BetaNode bet(id, condition);
	betaList.push_back(bet);
	return bet;
}

//int GraphOrNet::connectOneToOneNode(Node n1, Node n2)
//{
//	adjListGeneral.push_back({ n1, n2 });
//	return 1;
//}

//int GraphOrNet::connectAlphatoBeta(AlphaNode a1, AlphaNode a2, BetaNode b1)
//{
//	adjList.push_back({ a1, b1 });
//	adjList.push_back({ a2, b1 });
//
//	return 1;
//}

//int GraphOrNet::connectNodeAlphaToBeta(Node n1, Node n2, Node n3)
//{
//	//cout << typeid(n1).name() <<endl;
//	adjListGeneral.push_back({ n1, n3 });
//	adjListGeneral.push_back({ n2, n3 });
//	return 1;
//}

int GraphOrNet::connectTwoInputNode(AlphaNode &a1, AlphaNode &a2, BetaNode &b1)
{
	//adjAlphaBeta.push_back({ &a1, &b1 });
	//adjAlphaBeta.push_back({ &a2, &b1 });

	if (b1.leftSourceType != "" || b1.rightSourceType != "") {
		cout << "ALERT :" << b1.thisProduct << " IS ALREADY OCCUPIED SOURCE" << endl;
		return -1;
	}

	a1.addBetaPair(&b1);
	a2.addBetaPair(&b1);
	b1.leftSourceType = "Alpha";
	b1.rightSourceType = "Alpha";


	a1.betaPair = &b1;
	a2.betaPair = &b1;

	return 1;
}

int GraphOrNet::connectTwoInputNode(BetaNode &b1, AlphaNode &a2, BetaNode &b2)
{
	//adjAlphaBeta.push_back({ &a2, &b2 });
	//adjBetaBeta.push_back({ &b1, &b2 });

	if (b2.leftSourceType != "" || b2.rightSourceType != "") {
		cout << "ALERT :" << b2.thisProduct << " IS ALREADY OCCUPIED SOURCE" << endl;
		return -1;
	}

	b1.addBetaPair(&b2);
	a2.addBetaPair(&b2);
	b2.leftSourceType = "Beta";
	b2.rightSourceType = "Alpha";

	//Back to linked list
	a2.betaPair = &b2;
	b1.betaPair = &b2;

	return 1;
}

int GraphOrNet::connectTwoInputNode(BetaNode &b1, BetaNode &b2, BetaNode &b3)
{
	//adjBetaBeta.push_back({ &b1, &b3 });
	//adjBetaBeta.push_back({ &b2, &b3 });

	if (b3.leftSourceType != "" || b3.rightSourceType != "") {
		cout << "ALERT :" << b3.thisProduct << " IS ALREADY OCCUPIED SOURCE" << endl;
		return -1;
	}

	b1.addBetaPair(&b3);
	b2.addBetaPair(&b3);
	b3.leftSourceType = "Beta";
	b3.rightSourceType = "Beta";


	b1.betaPair = &b3;
	b2.betaPair = &b3;

	return 1;
}

int GraphOrNet::connectBetaToTerminal(BetaNode &b1, TerminalNode &t1)
{
	adjBetaTerminal.push_back({ &b1, &t1 });

	b1.terminalPair = &t1;

	return 0;
}

int GraphOrNet::buildCurrentAlphaBeta()
{
	//alpha to beta & beta to beta
	for (int i = 0; i < betaList.size(); i++) {
		//Will be depreciated soon
		int alpha1 = -1, alpha2 = -1;
		int beta1 = -1, beta2 = -1;
		alpha1 = findAlpha(betaList[i].leftSource);
		alpha2 = findAlpha(betaList[i].rightSource);

		//Banyak kemungkinan beta nih. Ya bikin aja satu2
		if (alpha1 == -1 || alpha2 == -1) { // pasti salah satunya beta
			beta1 = findBetaBasedOnProduct(betaList[i].leftSource);
			if (beta1 == -1)
				beta1 = findBetaBasedOnProduct(betaList[i].rightSource);
		}
		else if (alpha1 == -1 && alpha2 == -1) { // keduanya beta
			beta1 = findBetaBasedOnProduct(betaList[i].leftSource);
			beta2 = findBetaBasedOnProduct(betaList[i].rightSource);
		}

		if (alpha1 != -1 && alpha2 != -1) // alpha 1 and 2 is alpha node
			//connectNodeAlphaToBeta(alphaList[alpha1], alphaList[alpha2], betaList[i]);
			connectTwoInputNode(alphaList[alpha1], alphaList[alpha2], betaList[i]);
		else if(alpha1 == -1 && alpha2 != -1) // alpha 1 is beta
			//connectNodeAlphaToBeta(betaList[beta1], alphaList[alpha2], betaList[i]);
			connectTwoInputNode(betaList[beta1], alphaList[alpha2], betaList[i]);
		else if (alpha1 != -1 && alpha2 == -1) // alpha 2 is beta
			//connectNodeAlphaToBeta(alphaList[alpha1], betaList[beta1], betaList[i]);
			connectTwoInputNode(betaList[beta1], alphaList[alpha2], betaList[i]);
		else
			continue;
	}
	
	
	//bikin saingannya
	/*
	for (int i = 0; i < betaList.size(); i++) {
		//Lets work on this
		AlphaNode* alpha1A, * alpha2A;
		BetaNode* beta1B, * beta2B;
		alpha1A = findAlphaAndReturnNode(betaList[i].leftSource);
		alpha2A = findAlphaAndReturnNode(betaList[i].rightSource);

		//Banyak kemungkinan beta nih. Ya bikin aja satu2
		if (alpha1A == nullptr|| alpha2A == nullptr) { // pasti salah satunya beta
			beta1B = findBetaBasedOnProductAndReturnNode(betaList[i].leftSource);
			if (beta1B == nullptr)
				beta2B = findBetaBasedOnProductAndReturnNode(betaList[i].rightSource);
		}
		else if (alpha1A == nullptr && alpha2A == nullptr) { // keduanya beta
			beta1B = findBetaBasedOnProductAndReturnNode(betaList[i].leftSource);
			beta2B = findBetaBasedOnProductAndReturnNode(betaList[i].rightSource);
		}

		if (alpha1A != nullptr && alpha2A != nullptr) // left and right is alpha node
			connectTwoInputNode(*alpha1A, *alpha2A, betaList[i]);
		else if (alpha1A == nullptr && alpha2A != nullptr) { // left is beta right is alpha
			//if(beta1B == nullptr)
				connectTwoInputNode(*beta1B, *alpha1A, betaList[i]);
			//else
			//	connectTwoInputNode(*beta2B, *alpha1A, betaList[i]);
		}
		else if (alpha1A != nullptr && alpha2A == nullptr) // alpha 2 is beta
			//connectNodeAlphaToBeta(alphaList[alpha1], betaList[beta1], betaList[i]);
			connectTwoInputNode(*beta2B, *alpha1A, betaList[i]);
		else if(alpha1A == nullptr && alpha2A == nullptr) // both beta
			connectTwoInputNode(*beta1B, *beta2B, betaList[i]);
		else
			continue;
	}
	*/

	//beta to terminal
	for (int i = 0; i < termList.size(); i++) {
		int betaId = -1;
		
		betaId	= findBetaBasedOnProduct(termList[i].prevBetaProduct);
		if (betaId != -1)
			connectBetaToTerminal(betaList[betaId], termList[i]);
	}

	return 0;
}

void GraphOrNet::showAlpha()
{
	for (int i = 0; i < alphaList.size(); i++) {
		cout << "ID = "<<alphaList[i].id << endl;
		cout << alphaList[i].thisDataType << " -- " << alphaList[i].thisCondition << " -- "
			<< alphaList[i].thisVarLimit << endl;
	}
}

void GraphOrNet::showBeta()
{
	for (int i = 0; i < betaList.size(); i++) {
		cout << "ID = " << betaList[i].id << endl;
		cout << betaList[i].leftSource << " -- " << betaList[i].rightSource << " -- "
			<< betaList[i].thisProduct << endl;
	}
}

void GraphOrNet::showAll()
{
	cout << "Alpha Node : " << endl;
	showAlpha();

	cout << endl << "Beta Node : " << endl;
	showBeta();

	cout << endl << "Adj List: " << endl;
	showAdjList();
}

void GraphOrNet::showAdjList()
{
	;//for (int i = 0; i < adjListGeneral.size(); i++) {

	//}
}

int GraphOrNet::findAlpha(string dataType)
{
	for (int i = 0; i < alphaList.size(); i++) {
		if (strcmp(alphaList[i].thisDataType.c_str(), dataType.c_str()) == 0)
			return i;
	}
	return -1;
}

AlphaNode * GraphOrNet::findAlphaAndReturnNode(string dataType)
{
	for (int i = 0; i < alphaList.size(); i++) {
		if (strcmp(alphaList[i].thisDataType.c_str(), dataType.c_str()) == 0)
			return &alphaList[i];
	}
	return nullptr;
}

BetaNode * GraphOrNet::findBetaBasedOnProductAndReturnNode(string product)
{
	for (int i = 0; i < betaList.size(); i++) {
		if (strcmp(betaList[i].thisProduct.c_str(), product.c_str()) == 0)
			return &betaList[i];
	}
	return nullptr;
}

int GraphOrNet::findBeta(string BCode)
{
	int num = -1;
	
	int len = BCode.length();
	num = atoi(BCode.substr(1, len).c_str());

	return num;
}

int GraphOrNet::findBetaBasedOnProduct(string product)
{
	for (int i = 0; i < betaList.size(); i++) {
		if (betaList[i].thisProduct == product)
			return i;
	}

	return -1;
}
