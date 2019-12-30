#include <iostream>
#include <string>
#include "WMSet.h"
#include "GraphOrNet.h"

using namespace std;


int main() {

	int select;
	WMSet now_wm;
	GraphOrNet now_graph;

	cout << "select what you want " << endl;
	cin >> select;
	while (select <= 10) {
		switch (select){
			//input WME
			case 1: {
				cout << "input with format <data type> <id> <value> " ;
				string type;
				int id = 0, value = 0;
				cin >> type;
				cin >> id;
				cin >> value;

				now_wm.addMemory(type, id, value);
				break;
			}
			case 2 : {
				cout << "Inside WM"<<endl;
				now_wm.showSet();
				break;
			}
			case 3: {
				cout << "input condition for alpha Node"<<endl;
				string con;
				cin.ignore();
				//getchar();
				getline(cin, con);
				now_graph.addAlpha(con);
				break;
			}
			case 4: {
				cout << "input condition for beta Node" << endl;
				string con;
				cin.ignore();
				//getchar();
				getline(cin, con);
				now_graph.addBeta(con);
				break;
			}
			case 5: {
				cout << "this is the nodes created " << endl;
				now_graph.showAll();
				break;
			}
			case 6: {
				cout << "build graph: " << endl;
				now_graph.buildCurrentAlphaBeta();
				cout << "build complete!!!" << endl;
				break;
			}
			case 7: {
				vector<int> match_found;
				cout << "test possible match :" << endl;
				match_found = now_graph.findMatch(now_wm);
				if (match_found.size() != 0)
					cout << match_found.size() << " matches found" << endl;
				else
					cout << "no possible match" << endl;
				break;
			}
			case 8: {
				cout << "add new term: " << endl;
				string term;
				cin.ignore();
				//getchar();
				getline(cin, term);
				now_graph.addTerminal(term);
				break;
			}
			case 9: {
				cout << "Fire the Working Memory " << endl;
				now_graph.tempFireWME(now_wm);
				break;
			}
			default: {
				break;
			}
		}
		cout << "select what you want " << endl;
		cin >> select;
	}
	

	return 0;
}