#include <iostream>
#include <cstdio>
#define REP(i,a) for(int i=0; i < a; ++i)
using namespace std;

int t, sx, sy, tx, ty;
char a[100111];

int main() {
	while (scanf("%d%d%d%d%d\n", &t, &sx, &sy, &tx, &ty) == 5) {
		gets(a);
		bool good = false;
		REP(i,t) {
			char c = a[i];
			if (c == 'S' && sy > ty) --sy;
			if (c == 'E' && sx < tx) ++sx;
			if (c == 'W' && sx > tx) --sx;
			if (c == 'N' && sy < ty) ++sy;

			if (sx == tx && sy == ty) {
				good = true;
				cout << i+1 << endl;
				break;
			}
		}
		if (!good) puts("-1");
	}
	return 0;
}