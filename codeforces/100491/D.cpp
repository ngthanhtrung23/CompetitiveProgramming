#include<bits/stdc++.h>

using namespace std;

vector<long long> v;
long long s[200];
long long cal[200];
int n;


int main() {
	freopen("diamonds.in", "r", stdin);
	freopen("diamonds.out", "w", stdout);
	cin >> n; 
	long long a;
	
	for(int i=0; i<n; i++) {
		cin >> a;
		v.push_back(a);
	}

	s[n] = 0ll;
	sort(v.begin(), v.end());
	for(int i=n-1; i>=0; i--) s[i] = s[i+1] + v[i]; 
	
	cal[n] = 0ll;
	cal[n-1] = v[n-1];
	
	for(int i=n-2; i>=0; i--) {
		cal[i] = v[i] + cal[i+1] - (long long) 4;
		if (cal[i] < v[i] + s[i+1] - cal[i+1]) cal[i] = v[i] + s[i+1] - cal[i+1];
	}
	
	long long val[2];
	int turn, x;
	x = 0;
	turn = 1;
	
	val[0] = val[1] = 0ll;
	
	while(v[x]==3 && x < n) {
		val[turn] += 3;
		x++;
		turn = 1 - turn;
	}
	
	val[turn] = val[turn] + cal[x];
	val[1 - turn] = s[0] - val[turn];
	
	cout << val[0] << " " << val[1] << endl;
}