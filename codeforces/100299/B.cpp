#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

int main()
{
	string s, t, animal, voice;
	int test;
	
	cin >> test;
	getline(cin, s);
	while (test--)
	{
		set <string> voices;
		getline(cin, s);
		while (getline(cin, t))
		{
			if (t == "what does the fox say?") break;
			stringstream ss;
			ss << t;
			ss >> animal >> t >> voice;
			voices.insert(voice);
		}
		
		stringstream ss;
		ss << s;
		int started = 0;
		while (ss >> s)
			if (!voices.count(s))
			{
				if (started) cout << ' ';
				cout << s;
				started = 1;
			}
		
		cout << endl;
	}
}
