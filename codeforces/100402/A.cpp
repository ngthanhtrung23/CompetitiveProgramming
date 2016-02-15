#include<bits/stdc++.h>

using namespace std;

int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	int r, d;
	cin >> d >> r;
	
	if (r*2>=d) {
		cout << "YES" << endl;
		if(r==1) {
			if (d==1) {
				cout << 2 << " " << 1 << endl;
				cout << 1 << " " << 2 << endl;
			} else if (d==2) {
				cout << 3 << " " << 2 << endl;
				cout << 1 << " " << 2 << endl;
				cout << 2 << " " << 3 << endl;
			}
		} else {
			int m, n;
			n = m = r + d;
			cout << m << " " << n << endl;
			for(int i=1; i<=2*r-1; i++) cout << i << " " << i + 1 << endl;
			cout << 2*r << " " << 1 << endl;
			for(int i=2*r+1; i<=n; i++) cout << i - 1 << " " << i << endl; 
		}
	} else {
		cout << "NO" << endl;
	}
}