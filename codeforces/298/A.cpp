#include <iostream>
#include <cstdio>
using namespace std;

char a[1011];

int main() {
	int n;
	while (scanf("%d\n", &n) == 1) {
		gets(a);
		bool allL = true, allR = true;
		int firstL = -1, lastL = -1, firstR = -1, lastR = -1;

		for(int i = 0; i < n; ++i) {
			if (a[i] == 'L') {
				allR = false;
				if (firstL < 0) firstL = i+1;
				lastL = i+1;
			}
			if (a[i] == 'R') {
				allL = false;
				if (firstR < 0) firstR = i+1;
				lastR = i+1;
			}
		}

		if (allL) {
			cout << lastL << ' ' << firstL-1 << endl;
		}
		else if (allR) {
			cout << firstR << ' ' << lastR + 1 << endl;
		}
		else {
			cout << firstR << ' ' << firstL - 1 << endl;
		}
	}
}