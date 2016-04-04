#include<bits/stdc++.h>

using namespace std;

int pos[400000];
int A[400000];


int main() {
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
	
	int n, x;
	cin >> n;
	
	for(int i=1; i<=n; i++) {
		scanf("%d", &x); 
		pos[x] = i;
		A[i] = x;
	}
	
	pos[0] = n + 1;
	pos[n + 1] = 0;
	x = n;
	//A 1 2 4 6 3 5 
	//pos 1 2       4
	while(x>0 && (pos[x]==n+1-x)) x--;
	
	bool cor = true;
	for(int i=1; i<=n-1; i++) {
		int u = A[i];
		int v = A[i+1];
		if (A[i+1] != x && pos[u+1]>pos[v+1]) cor = false;
	}
	
	if (cor) {
		for(int i=1; i<=n; i++) {
			if (pos[i]<pos[x]) printf("0");
			else printf("1");
		}
		cout << endl;
	} else cout << "Error" << endl;
}