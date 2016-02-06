#include<bits/stdc++.h>

using namespace std;

int main() {
	
	freopen("dkl.in", "r", stdin);
	freopen("dkl.out", "w", stdout);

	int delta, kappa, lambda;
	cin >> delta >> kappa >> lambda;
	if (delta < lambda || lambda < kappa) {
		printf("0 0\n");
	} else {
		int p = delta + 1;
		int n = 2 * p;
		int m = p * (p - 1) + lambda;
		printf("%d %d\n", n, m);
		for(int i=1; i<p; i++) 
		for(int j=i+1; j<p+1; j++) {
			printf("%d %d\n", i, j);
			printf("%d %d\n", i + p, j + p);
		}	

		for(int i=1; i<=kappa; i++) printf("%d %d\n", i, i+p);
		for(int i=kappa+1; i<=lambda; i++) printf("1 %d\n", i+p);		
	}
}