#include<bits/stdc++.h>

using namespace std;

int n, q[20], c[20], p[20], minB[20];

int main() {
	scanf("%d", &n);
	int res = 0;
	
	for(int i=0; i<n; i++) scanf("%d", &q[i]);
	
	for(int i=0; i<n; i++) {
		scanf("%d", &c[i]);
		minB[i] = (q[i]	- 1) / c[i] + 1;	
	}
	
	int m = 0;
	for(int i=0; i<n; i++) m = max(m, minB[i]);
	
	for(int i=0; i<n; i++) {
		scanf("%d", &p[i]);
		res += p[i] * (m * c[i] - q[i]);	
	}
	
	printf("%d\n", res);
		
}