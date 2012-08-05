#include <cstdio>
#include <iostream>
using namespace std;

const int GH = 60;
long long f[GH + 10];

int main() {
	f[0] = 0; f[1] = 1;
	for(int i = 2; i <= GH; i++) {
		f[i] = f[i-1] + f[i-2];
	}
	long long n;
	cin >> n;
	for(int a = 0; a <= GH; a++)
	for(int b = a; b <= GH; b++)
	for(int c = b; c <= GH; c++)
		if (f[a] + f[b] + f[c] == n) {
			cout << f[a] << ' ' << f[b] << ' ' << f[c] << endl;
			return 0;
		}
	puts("I'm too stupid to solve this problem");
	return 0;
}