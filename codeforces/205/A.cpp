#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define F first
#define S second

int n;
pair<int,int> a[100111];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i].F);
		a[i].S = i;
	}
	sort(a+1, a+n+1);
	if (a[1].F == a[2].F) puts("Still Rozdil");
	else cout << a[1].S << endl;
	return 0;
}