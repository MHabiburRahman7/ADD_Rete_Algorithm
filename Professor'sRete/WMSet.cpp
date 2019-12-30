#include "WMSet.h"

void WMSet::showSet()
{
	for (int i = 0; i < data_content.size(); i++) {
		cout << data_content[i].first << " : " <<endl;
		for (int j = 0; j < data_content[i].second.size(); j++) {
			cout << data_content[i].second[j].first << " - " << data_content[i].second[j].second << endl;
		}
		cout << endl;
	}
}

int WMSet::checkAvailability(string check)
{
	int res = -1;
	for (int i = 0; i < data_content.size(); i++) {
		if (strcmp(data_content[i].first.c_str(), check.c_str()) == 0)
			return i;
	}
	return res;
}

int WMSet::addMemory(string dataType, int id, int value)
{
	int wm_typeId = checkAvailability(dataType);
	if (wm_typeId != -1) {
		data_content[wm_typeId].second.push_back({ id, value });
		return 1;
	}
	else {
		vector<pair<int, int>> temp;
		temp.push_back({ id, value });

		data_content.push_back({ dataType, temp});
		return 1;
	}
	return 0;
}
