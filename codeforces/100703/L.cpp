#include<bits/stdc++.h>

using namespace std;

int main() {
	int n, p[1003], k[1003], r[1003];
	cin >> n;
	for(int i=0; i<n; i++) cin >> p[i];
	for(int i=0; i<n; i++) cin >> k[i];
	for(int i=0; i<n; i++) {
		cin >> r[i];
		p[i] = (p[i] - r[i]) * (p[i] - r[i]);
		k[i] = (k[i] - r[i]) * (k[i] - r[i]); 
	}
	
	int x, y;
	x = y = 0;
	for(int i=0; i<n; i++) {
		if (p[i] > k[i]) x++;
		else if (k[i] > p[i]) y++;
	}
	printf("%d %d", y, x);
}