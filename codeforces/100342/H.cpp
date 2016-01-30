#include<bits/stdc++.h>

using namespace std;

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	
	int cur = 1;
	int n, m;
	
	int A[2000];
	
	for(int i=1; i<=1000; i++) A[i] = 999000 + i;
	
	cin >> n >> m;
	
	for(int i=1; i<n; i++) {
		printf("%d %d %d\n", i, i+1, 1);
	}
	
	m -= (n - 1);
	
	while (m > 0) {
		int k = n;
		if (m < k - cur - 1) k = (m + 1 + cur);
		for(int i = cur + 2; i <= k; i++) {
			A[i] -= 1000;
			printf("%d %d %d\n", cur, i, A[i]);
		}
		
		m -= (k - cur - 1);
		cur++;
	}
}