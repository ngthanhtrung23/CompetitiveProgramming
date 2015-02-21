#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;
const int base = int(1e9 + 9);

int n, h, f[1010][33][33][33][2];

int next(int x)
{
	return x && x < h ? x + 1 : x;
}

int ok(int z, int x)
{
	if (!x) return z < h;
	return x < h;
}

void addMod(int &x, int y)
{
	x += y;
	if (x >= base) x -= base;
}

int main()
{
	cin >> n >> h;
	f[1][0][0][0][0] = 4;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= h; j++)
			for (int p = 0; p <= h; p++)
				for (int q = 0; q <= h; q++)
					for (int z = 0; z < 2; z++)
						if (!z || (j && j < h) || (p && p < h) || (q && q < h))
						{			
							int cur = f[i][j][p][q][z];
							if (i == n)
							{
								addMod(ans, cur);
								continue;
							}
							
							int jj = next(j), pp = next(p), qq = next(q);
							
							addMod(f[i + 1][jj][pp][qq][z], cur);
							
							if (ok(i, j)) addMod(f[i + 1][z ? h : 1][pp][qq][0], cur);
							else addMod(f[i + 1][z ? h : 1][pp][qq][1], cur);
							
							if (ok(i, p)) addMod(f[i + 1][z ? h : 1][jj][qq][0], cur);
							else addMod(f[i + 1][z ? h : 1][jj][qq][1], cur);
							
							if (ok(i, q)) addMod(f[i + 1][z ? h : 1][jj][pp][0], cur);
							else addMod(f[i + 1][z ? h : 1][jj][pp][1], cur);
						}
				
	cout << ans << endl;
}