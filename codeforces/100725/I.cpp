#include<bits/stdc++.h>

using namespace std;

int main() {
	freopen("invar.in", "r", stdin);
    freopen("invar.out", "w", stdout);
	int n, d;
	cin >> n >> d;
	int res = 1 + n/2;
	if (d == 1) {
		res = (n + 1) * (n + 2) / 2;
	} else {
		for (int i=1; i<=n/d; i++) {
		res += 2*(1+(n-i*d)/2); 
		}
	}
	cout << res;
}
