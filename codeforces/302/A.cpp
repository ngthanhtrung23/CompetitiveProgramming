#include <iostream>
#include <cstdio>
using namespace std;

int n, q, a[200111];

int main() {
	int cnt1 = 0, cnt2 = 0;
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] < 0) ++cnt1; else ++cnt2;
	}
	while (q--) {
		int u, v; scanf("%d%d", &u, &v);
		int len = (v - u + 1);
		if (len % 2) puts("0");
		else if (cnt1 >= len/2 && cnt2 >= len/2) puts("1");
		else puts("0");
	}
	return 0;
}
