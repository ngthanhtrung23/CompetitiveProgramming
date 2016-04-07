#include<bits/stdc++.h>

using namespace std;

int main() {
	freopen("princess.in", "r", stdin);
	freopen("princess.out", "w", stdout);
	long long L;
	cin >> L;
	cout << (fixed) << setprecision(9);
	double n = double (L); 
	double m;
	int i = 1;
	while (log(n)/i + log(i*1.0)>log(n)/(i+1) + log(i+1.0)) i++;
	double res = i * exp(log(n)/i);
	cout << res << endl;
}
