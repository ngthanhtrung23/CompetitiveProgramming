#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

string s, res;

bool palin(string s) {
	for(int i = 0; i < s.length(); i++)
		if (s[i] != s[s.length()-i-1]) return false;
	return true;
}

void update(string cur) {
	if (!palin(cur)) return ;
	if (cur > res) res = cur;
}

int main() {
	cin >> s;
	int n = s.length();
	for(int mask = 0; mask < TWO(n); ++mask) {
		string cur = "";
		for(int i = 0; i < n; i++)
		if (CONTAIN(mask,i)) cur = cur + s[i];
		update(cur);
	}
	cout << res << endl;
	return 0;
}
