#include<bits/stdc++.h>

using namespace std;

int main() {
	string s;
	freopen("prefixes.in", "r", stdin);
	freopen("prefixes.out", "w", stdout);
	cin >> s;
	if (s.length()==1) {
		cout << s << endl;
	} else {
		vector<char> head;
		vector<char> tail;
		char m, M;
		int l = s.length();
		m = min(s[0], s[1]);
		M = max(s[0], s[1]);
		head.push_back(m);
		tail.push_back(M);
		
		for(int i=2; i<l; i++) {
			if(m>=s[i]) {
				head.push_back(s[i]);
				m = s[i];
			} else {
				tail.push_back(s[i]);
			}
		}
		
		for(int i=head.size()-1; i>=0; i--) {
			printf("%c", head[i]);
		}
		
		for(int i=0; i<tail.size(); i++) {
			printf("%c", tail[i]);
		}
		
		cout << endl;	
	}
}