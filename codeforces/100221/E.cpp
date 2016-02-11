#include<bits/stdc++.h>

using namespace std;

int f[1005], g[1005], cnt[1005], n;

int cmp(int i, int j) {
	if (cnt[i] == cnt[j]) return (i < j);
	return cnt[i] < cnt[j];	
}

int main() {
	string s[1005];
	vector<int> v;
	
	freopen("relations.in", "r", stdin);
	freopen("relations.out", "w", stdout);
	
	cin >> n;
	
	for(int i=0; i<n; i++) {
		cin >> s[i];
		v.push_back(i);
		cnt[i] = 0;

		for(int j=0; j<n; j++) {
			if (s[i][j] == '1') {
				cnt[i]++;
			}
		}
	}
	
	sort(v.begin(), v.end(), cmp);
	bool correct = true;
	
	for(int i=0; i<n-1; i++) {
		int x = v[i];
		int y = v[i+1];
		
		for(int j=0; j<n; j++) 
		if (s[x][j] > s[y][j]) {
			correct = false;
			break;		
		}
		
		if(!correct) break;	
	}
	
	for(int i=0; i<n; i++) f[i] = n - cnt[i];
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if (s[i][j] == '1') g[j] = max(g[j], f[i]);
		}
	}
	
	if (correct) {
		cout << "YES" << endl;
		for(int i=0; i<n; i++) cout << f[i] << " ";
		cout << endl;
		for(int i=0; i<n; i++) cout << g[i] << " ";
		cout << endl;	
	} else {
		cout << "NO" << endl;
	}
	
	
}